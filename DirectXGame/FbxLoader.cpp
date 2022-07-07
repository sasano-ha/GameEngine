#include "FbxLoader.h"

#include <cassert>

using namespace DirectX;

/// <summary>
/// 静的メンバを変数の実体
/// </summary>
const std::string FbxLoader::baseDirectory_ = "Resources/";

FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device)
{
    // 再初期化チェック
    assert(fbxManager_ == nullptr);
    // 引数からメンバ変数に代入
    this->device_ = device;
    // FBXマネージャーの生成
    fbxManager_ = FbxManager::Create();
    // FBXマネージャーの入力設定
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager_, IOSROOT);
    fbxManager_->SetIOSettings(ios);
    // FBXインポータの生成
    fbxImporter_ = FbxImporter::Create(fbxManager_, "");
}

void FbxLoader::Finalize()
{
    // 各種FBXインスタンスの破棄
    fbxImporter_->Destroy();
    fbxManager_->Destroy();
}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
    // モデルと同じ名前のファイルから読み込む
    const string directoryPath = baseDirectory_ + modelName + "/";
    // 拡張子,FBXを付与
    const string fileName = modelName + ".fbx";
    // 連結してフルパスを得る
    const string fullpath = directoryPath + fileName;

    // ファイル名を指定してFBXファイルを読み込む
    if (!fbxImporter_->Initialize(fullpath.c_str(), -1, fbxManager_->GetIOSettings())) {
        assert(0);
    }

    // シーン生成
    FbxScene* fbxScene = FbxScene::Create(fbxManager_, "fbxScene");

    // ファイルからロードしたFBXに情報をシーンにインポート
    fbxImporter_->Import(fbxScene);


    // モデル生成
    FbxModel* fbxmodel = new FbxModel();
    fbxmodel->name = modelName;
    // FBXノードの数を取得
    int nodeCount = fbxScene->GetNodeCount();
    // あらかじめ必要数分のメモリを確保することで、アドレスがずれるのを予防
    fbxmodel->nodes.reserve(nodeCount);
    // ルートノードから順に解析してもでるに流し込む
    ParseNodeRecursive(fbxmodel, fbxScene->GetRootNode());
    // FBXシーン解放
    fbxScene->Destroy();
}

void FbxLoader::ParseNodeRecursive(FbxModel* fbxmodel, FbxNode* fbxNode, Node* parent)
{
    // ノード名を取得
    string name = fbxNode->GetName();
    // モデルにノードを追加（Todo）
    fbxmodel->nodes.emplace_back();
    Node& node = fbxmodel->nodes.back();
    // ノード名を取得
    node.name = fbxNode->GetName();


    // FBXノードのローカル移動情報
    FbxDouble3 rotation = fbxNode->LclRotation.Get();
    FbxDouble3 scaling = fbxNode->LclScaling.Get();
    FbxDouble3 translation = fbxNode->LclTranslation.Get();

    // 形式変換して代入
    node.rotation = { (float)rotation[0], (float)rotation[1], (float)rotation[2], 0.0f };
    node.scaling = { (float)scaling[0], (float)scaling[1], (float)scaling[2], 0.0f };
    node.translation = { (float)translation[0], (float)translation[1], (float)translation[2], 1.0f };

    // 回転角をDegree(度)からラジアンの計算
    node.rotation.m128_f32[0] = XMConvertToRadians(node.rotation.m128_f32[0]);
    node.rotation.m128_f32[1] = XMConvertToRadians(node.rotation.m128_f32[1]);
    node.rotation.m128_f32[2] = XMConvertToRadians(node.rotation.m128_f32[2]);

    // スケール、回転平行移動行列の計算
    XMMATRIX matScaling, matRotation, matTranslation;
    matScaling = XMMatrixScalingFromVector(node.scaling);
    matRotation = XMMatrixRotationRollPitchYawFromVector(node.rotation);
    matTranslation = XMMatrixTranslationFromVector(node.translation);

    // ローカル変形行列の計算
    node.transform = XMMatrixIdentity();
    node.transform *= matScaling;   // ワールド行列にスケーリングを反映
    node.transform *= matRotation;  // ワールド行列に回転を反映
    node.transform *= matTranslation;   // ワールド行列に平行移動を反映

    // グローバル変形行列の計算
    node.globalTransform = node.transform;
    if (parent) {
        node.parent = parent;
        // 親の変形を乗算
        node.globalTransform *= parent->globalTransform;
    }

    // FBXノードのメッシュ情報を解析（Todo）
    FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

    if (fbxNodeAttribute) {
        if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
            fbxmodel->meshNode = &node;
            ParseMesh(fbxmodel, fbxNode);
        }
    }

    // 子ノードに対して再帰呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++) {
        ParseNodeRecursive(fbxmodel, fbxNode->GetChild(i), &node);
    }

}

void FbxLoader::ParseMesh(FbxModel* fbxmodel, FbxNode* fbxNode)
{
    // ノードのメッシュを取得
    FbxMesh* fbxMesh = fbxNode->GetMesh();

    // 頂点座標読み取り
    ParseMeshVertices(fbxmodel, fbxMesh);
    // 面を構成するでーたの読み取り
    ParseMeshFaces(fbxmodel, fbxMesh);
    // マテリアルの読み取り
    ParseMaterial(fbxmodel, fbxNode);
}

void FbxLoader::ParseMeshVertices(FbxModel* fbxmodel, FbxMesh* fbxMesh)
{
    auto& vertices = fbxmodel->vertices;

    // 頂点座標データの数
    const int controlPointsCount = fbxMesh->GetControlPointsCount();
    // 必要数だけ頂点データ配列を確保
    FbxModel::VertexPosNormalUvSkin vert{};
    fbxmodel->vertices.resize(controlPointsCount, vert);

    // FBXノードのメッシュの頂点座標配列を取得
    FbxVector4* pCoord = fbxMesh->GetControlPoints();

    // FBXノードのメッシュメッシュの全頂点座標をモデルないの配列にコピーする。
    for (int i = 0; i < controlPointsCount; i++) {
        FbxModel::VertexPosNormalUvSkin& vertex = vertices[i];
        //座標のコピー
        vertex.pos.x = (float)pCoord[i][0];
        vertex.pos.y = (float)pCoord[i][1];
        vertex.pos.z = (float)pCoord[i][2];
    }
}

void FbxLoader::ParseMeshFaces(FbxModel* fbxmodel, FbxMesh* fbxMesh)
{
    auto& vertices = fbxmodel->vertices;
    auto& indices = fbxmodel->indices;

    // 1つファイルに複数メッシュのモデルは非対応
    assert(indices.size() == 0);
    // 面の数
    const int polygonCount = fbxMesh->GetPolygonCount();
    // UVデータの数
    const int textureUVCount = fbxMesh->GetTextureUVCount();
    // UV名リスト
    FbxStringList uvNames;
    fbxMesh->GetUVSetNames(uvNames);

    // 面ごとの情報読み取り
    for (int i = 0; i < polygonCount; i++) {
        // 面を構成する頂点の数を取得（3なら三角形ポリゴン）
        const int polygonSize = fbxMesh->GetPolygonSize(i);
        assert(polygonSize <= 4);

        // 1頂点ずつ処理
        for (int j = 0; j < polygonSize; j++) {
            // FBXノードのメッシュ頂点配列のインデックス
            int index = fbxMesh->GetPolygonVertex(i, j);
            assert(index >= 0);

            // 頂点法線読込
            FbxModel::VertexPosNormalUvSkin& vertex = vertices[index];
            FbxVector4 normal;
            if (fbxMesh->GetPolygonVertexNormal(i, j, normal)) {
                vertex.normal.x = (float)normal[0];
                vertex.normal.y = (float)normal[1];
                vertex.normal.z = (float)normal[2];
            }

            // テクスチャUV読込
            if (textureUVCount > 0) {
                FbxVector2 uvs;
                bool lUnmappedUV;
                // 0番決め打ちで読込
                if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
                    vertex.uv.x = (float)uvs[0];
                    vertex.uv.y = (float)uvs[1];
                }
            }

            // インデックス配列の頂点インデックス追加
            // 3項点目までなら
            if (j < 3) {
                //1点追加し、他の2点と三角形を構築する
                indices.push_back(index);
            }
            // 4項点目
            else {
                // 3点追加し、
                // 四角形の0,1,2,3の内　2,3,0で三角形を構築する
                int index2 = indices[indices.size() - 1];
                int index3 = index;
                int index0 = indices[indices.size() - 3];
                indices.push_back(index2);
                indices.push_back(index3);
                indices.push_back(index0);
            }
        }
    }
}
