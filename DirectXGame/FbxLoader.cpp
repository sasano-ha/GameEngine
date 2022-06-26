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
    node.transform *= matScaling;   //ワールド行列にスケーリングを反映
    node.transform *= matRotation;  //ワールド行列に回転を反映
    node.transform *= matTranslation;   //ワールド行列に平行移動を反映

    //グローバル変形行列の計算
    node.globalTransform = node.transform;
    if (parent) {
        node.parent = parent;
        //親の変形を乗算
        node.globalTransform *= parent->globalTransform;
    }

    //子ノードに対して再帰呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++) {
        ParseNodeRecursive(fbxmodel, fbxNode->GetChild(i), &node);
    }
}
