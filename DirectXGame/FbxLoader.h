#pragma once

#include "fbxsdk.h"
#include "FbxModel.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>

class FbxLoader
{
private:	//エイリアス
	// std::を省略
	using string = std::string;

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device">D3D12デバイス</param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// ファイルからFBXモデル読み込み
	/// </summary>
	/// <param name="modeName">モデル名</param>
	FbxModel* LoadModelFromFile(const string& modelName);


	/// <summary>
	/// 再帰的にノード構成を解析
	/// </summary>
	/// <param name="modle"></param>
	/// <param name="fbxNode">解析対象のノード</param>
	void ParseNodeRecursive(FbxModel* fbxmodel, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	/// <param name="model">読み込み先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	void ParseMesh(FbxModel* fbxmodel, FbxNode* fbxNode);

	/// <summary>
	/// FBXの行列をXMMatrixに変換
	/// </summary>
	/// <param name="dst">書き込み先</param>
	/// <param name="src">元となるFBX行列</param>
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);

	// 頂点座標読み取り
	void ParseMeshVertices(FbxModel* fbxmodel, FbxMesh* fbxMesh);
	// 面積情報読み取り
	void ParseMeshFaces(FbxModel* fbxmodel, FbxMesh* fbxMesh);
	// マテリアル読み取り
	void ParseMaterial(FbxModel* fbxmodel, FbxNode* fbxNode);
	// テクスチャ読み込み
	void LoadTexture(FbxModel* fbxmodel, const std::string& fullpath);
	// スキニング情報の読み取り
	void ParseSkin(FbxModel* fbxmodel, FbxMesh* fbxMesh);

	// ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);

	// 定数
	// モデル格納ルートパス
	static const string baseDirectory_;
	// テクスチャがない場合の標準テクスチャファイル名
	static const string defaultTextureFileName_;

private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	// D3D12デバイス
	ID3D12Device* device_ = nullptr;
	// FBXマネージャー
	FbxManager* fbxManager_ = nullptr;
	// FBXインポータ
	FbxImporter* fbxImporter_ = nullptr;
};