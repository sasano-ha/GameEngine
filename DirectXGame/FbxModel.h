#pragma once

#include <string>
#include <DirectXmath.h>
#include <vector>
#include <DirectXTex.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>

struct Node
{
	// 名前
	std::string name;
	// ローカルスケール
	DirectX::XMVECTOR scaling_ = { 1, 1, 1, 0 };
	// ローカル回転角
	DirectX::XMVECTOR rotation_ = { 0, 0, 0, 0 };
	// ローカル移動
	DirectX::XMVECTOR translation_ = { 0, 0, 0, 1 };
	// ローカル変形行列
	DirectX::XMMATRIX transform_;
	// グローバル変形行列
	DirectX::XMMATRIX globalTransform_;
	// 親ノード
	Node* parent_ = nullptr;
};

class FbxModel
{
private:	// エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImge = DirectX::ScratchImage;
	// std::を省力
	using string = std::string;
	template <class T> using vector = std::vector<T>;

	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff_;
	// インッデクスバッファ
	ComPtr<ID3D12Resource> indexBuff_;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff_;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView_ = {};
	// インッデクスバッファビュー 
	D3D12_INDEX_BUFFER_VIEW ibView_ = {};
	// SRV用でスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV_;

public:
	// フレンドクラス
	friend class FbxLoader;
	// バッファ生成
	void CreateBuffers(ID3D12Device* device);
	// 描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	// モデルの変形行列取得
	const XMMATRIX& GetModelTransform() { return meshNode_->globalTransform_; }


private:
	// モデル名
	std::string name_;
	// ノード配列
	std::vector<Node> nodes_;
	// アンビエント係数
	DirectX::XMFLOAT3 ambient_ = { 1, 1, 1 };
	// ディフューズ係数
	DirectX::XMFLOAT3 diffuse_ = { 1, 1, 1 };
	// テクスチャデータ
	DirectX::TexMetadata metadata_ = {};
	// スクラッチイメージ
	DirectX::ScratchImage scratchImg_ = {};

public:	// サブクラス
	// 頂点データ構造体
	struct VertexPosNormalUvSkin
	{
		DirectX::XMFLOAT3 pos;				//xyz座標
		DirectX::XMFLOAT3 normal;			//法線ベクトル
		DirectX::XMFLOAT2 uv;				//uv座標
	};

	// メッシュを持つノード
	Node* meshNode_ = nullptr;
	// 頂点データ配列
	std::vector<VertexPosNormalUvSkin> vertices_;
	// 頂点インデックス配列
	std::vector<unsigned short> indices_;
};