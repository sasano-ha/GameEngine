#pragma once

#include "FbxModel.h"
#include "Camera.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class FbxObject3d
{
protected:	// エイリアス
	// Microosoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	// 静的メンバ関数
	// setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device_ = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera_ = camera; }

	/// <summary>
	///グラフィックパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

private:	// 静的メンバ変数
	// デバイス
	static ID3D12Device* device_;
	// カメラ
	static Camera* camera_;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature_;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate_;

public:	// サブクラス
	// 定数バッファ用データ構造体（座標変換行列）
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	// ビュープロジェクション行列
		XMMATRIX world;		// ワールド行列
		XMFLOAT3 cameraPos;	// カメラ行列（ワールド座標）
	};

public:	// メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム
	/// </summary>
	void Updata();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="model">モデル</param>
	void SetModel(FbxModel* fbxmodel) { this->fbxmodel_ = fbxmodel; }

	/// <summary>
	/// アニメーション
	/// </summary>
	void PlayAnimation();

protected:	// メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform_;
	// ローカルスケール
	XMFLOAT3 scale_ = { 1, 1, 1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation_ = { 0, 0, 0 };
	// ローカル座標
	XMFLOAT3 position_ = { 0, 0, 0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld_;
	// モデル
	FbxModel* fbxmodel_ = nullptr;
	// 定数バッファ（スキン）
	ComPtr<ID3D12Resource> constBuffSkin_;
	// 1フレーム
	FbxTime frameTime_;
	// アニメーション開始時間
	FbxTime startTime_;
	// アニメーション終了時間
	FbxTime endTime_;
	// 現在時間（アニメーション）
	FbxTime currentTime_;
	// アニメーション再生中
	bool isPlay_ = false;

public:	// 定数
	// ボーンの最大数
	static const int MAX_BONES = 32;

	// 定数バッファ用データ構造体（スキニング）
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
};

