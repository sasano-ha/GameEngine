#include "Sprite.h"

#include <d3dx12.h>
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>

using namespace Microsoft::WRL;
using namespace DirectX;

Sprite* Sprite::Create(UINT texNumber, DirectX::XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	//メモリ確保
	Sprite* instance = new Sprite();
	//インスタンス初期化
	instance->Initialize(texNumber, anchorpoint, isFlipX, isFlipY);

	return instance;
}

void Sprite::Initialize(UINT texNumber, DirectX::XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	HRESULT result = S_FALSE;

	// パイプラインを生成
	CreateGraphicsPipeline();

	// テクスチャ番号をコピー
	texNumber_ = texNumber;

	// アンカーポイントをコピー
	anchorpoint_ = anchorpoint;

	// 反転フラグをコピー
	isFlipX_ = isFlipX;
	isFlipY_ = isFlipY;

	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();

	// 頂点データ
	VertexPosUv vertices_[4];

	// 指定番号の画像が読み込み済みなら
	if (spriteCommon->GetTexBuff(texNumber_)) {
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = spriteCommon->GetTexBuff(texNumber_)->GetDesc();

		// スプライトの大きさを画像の解像度に合わせる
		size_ = { (float)resDesc.Width, (float)resDesc.Height };
		texSize_ = { (float)resDesc.Width, (float)resDesc.Height };
	}

	// 頂点バッファ生成
	result = spriteCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices_)),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff_));

	// 頂点バッファデータ転送
	TransferVertexBuffer();

	// 頂点バッファビューの作成
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = sizeof(vertices_);
	vbView_.StrideInBytes = sizeof(vertices_[0]);

	// 定数バッファの生成
	result = spriteCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));

	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);
	constMap->color = XMFLOAT4(1, 1, 1, 1); // 色指定（RGBA）
	constMap->mat = XMMatrixIdentity();
	constBuff_->Unmap(0, nullptr);
}

void Sprite::SizeInitialize(UINT texNumber, DirectX::XMFLOAT2 size, DirectX::XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{

	HRESULT result = S_FALSE;

	// パイプラインを生成
	CreateGraphicsPipeline();

	// テクスチャ番号をコピー
	texNumber_ = texNumber;

	// アンカーポイントをコピー
	anchorpoint_ = anchorpoint;

	// 反転フラグをコピー
	isFlipX_ = isFlipX;
	isFlipY_ = isFlipY;

	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();

	// 頂点データ
	VertexPosUv vertices_[4];

	// スプライトの大きさを画像の解像度に合わせる
	size_ = size;
	texSize_ = size;

	// 頂点バッファ生成
	result = spriteCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices_)),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff_));

	// 頂点バッファデータ転送
	TransferVertexBuffer();

	// 頂点バッファビューの作成
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = sizeof(vertices_);
	vbView_.StrideInBytes = sizeof(vertices_[0]);

	// 定数バッファの生成
	result = spriteCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));

	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);
	constMap->color = XMFLOAT4(1, 1, 1, 1); // 色指定（RGBA）
	constMap->mat = spriteCommon->GetMatProjection();
	constBuff_->Unmap(0, nullptr);

}

void Sprite::TransferVertexBuffer()
{
	HRESULT result = S_FALSE;

	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();

	// 頂点データ
	VertexPosUv vertices_[] = {
		//     u     v
		{{}, {0.0f, 1.0f}}, // 左下
		{{}, {0.0f, 0.0f}}, // 左上
		{{}, {1.0f, 1.0f}}, // 右下
		{{}, {1.0f, 0.0f}}, // 右上
	};

	// 左下、左上、右下、右上
	enum { LB, LT, RB, RT };

	float left = (0.0f - anchorpoint_.x) * size_.x;
	float right = (1.0f - anchorpoint_.x) * size_.x;
	float top = (0.0f - anchorpoint_.y) * size_.y;
	float bottom = (1.0f - anchorpoint_.y) * size_.y;

	if (isFlipX_)
	{// 左右入れ替え
		left = -left;
		right = -right;
	}

	if (isFlipY_)
	{// 左右入れ替え
		top = -top;
		bottom = -bottom;
	}

	vertices_[LB].pos = { left, bottom,  0.0f }; // 左下
	vertices_[LT].pos = { left, top,     0.0f }; // 左上
	vertices_[RB].pos = { right, bottom, 0.0f }; // 右下
	vertices_[RT].pos = { right, top,    0.0f }; // 右上

	// 指定番号の画像が読み込み済みなら
	if (spriteCommon->GetTexBuff(texNumber_)) {
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = spriteCommon->GetTexBuff(texNumber_)->GetDesc();

		float tex_left = texLeftTop_.x / resDesc.Width;
		float tex_right = (texLeftTop_.x + texSize_.x) / resDesc.Width;
		float tex_top = texLeftTop_.y / resDesc.Height;
		float tex_bottom = (texLeftTop_.y + texSize_.y) / resDesc.Height;

		vertices_[LB].uv = { tex_left,   tex_bottom }; // 左下
		vertices_[LT].uv = { tex_left,   tex_top }; // 左上
		vertices_[RB].uv = { tex_right,  tex_bottom }; // 右下
		vertices_[RT].uv = { tex_right,  tex_top }; // 右上
	}

	// 頂点バッファへのデータ転送
	VertexPosUv* vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	memcpy(vertMap, vertices_, sizeof(vertices_));
	vertBuff_->Unmap(0, nullptr);
}

void Sprite::Update()
{
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();

	// ワールド行列の更新
	matWorld_ = XMMatrixIdentity();
	// スケール
	//matWorld_ *= XMMatrixScaling(size_.x, size_.y, 1);
	// Z軸回転
	matWorld_ *= XMMatrixRotationZ(XMConvertToRadians(rotation_));
	// 平行移動
	matWorld_ *= XMMatrixTranslation(position_.x, position_.y, position_.z);

	// 定数バッファの転送
	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap);
	constMap->mat = matWorld_ * spriteCommon->GetMatProjection();
	constMap->color = color_;
	constBuff_->Unmap(0, nullptr);
}

void Sprite::Draw()
{
	if (isInvisible_) {
		return;
	}

	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	// パイプラインステートの設定
	commandList->SetPipelineState(pipelineset_.pipelinestate.Get());
	// ルートシグネチャの設定
	commandList->SetGraphicsRootSignature(pipelineset_.rootsignature.Get());

	// 頂点バッファをセット
	commandList->IASetVertexBuffers(0, 1, &vbView_);

	// ルートパラメーター0番に定数バッファをセット
	commandList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

	// ルートパラメーター1番にシェーダリソースビューをセット
	spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);

	// ポリゴンの描画（4頂点で四角形）
	commandList->DrawInstanced(4, 1, 0, 0);
}

void Sprite::CreateGraphicsPipeline()
{

	HRESULT result;

	ComPtr<ID3DBlob> vsBlob = nullptr; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob = nullptr; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/SpriteVS.hlsl",  // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/SpritePS.hlsl",   // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,      0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};

	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;              // 背面カリングをしない

	// レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = gpipeline.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // 標準設定
	blenddesc.BlendEnable = true;                   // ブレンドを有効にする
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;    // 加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;      // ソースの値を100% 使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;    // デストの値を   0% 使う
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;             // 加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;         // ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;    // 1.0f-ソースのアルファ値

	// デプスステンシルステートの設定
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthEnable = false;    // 深度テストをしない
	//gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;       // 常に上書きルール
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット

	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1; // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0～255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// デスクリプタテーブルの設定
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

	// ルートパラメータの設定
	CD3DX12_ROOT_PARAMETER rootparams[2];
	rootparams[0].InitAsConstantBufferView(0); // 定数バッファビューとして初期化(b0レジスタ)
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV);

	// スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);


	ID3D12Device* device = SpriteCommon::GetInstance()->GetDevice();


	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定でのシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ルートシグネチャの生成
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&pipelineset_.rootsignature));

	// パイプラインにルートシグネチャをセット
	gpipeline.pRootSignature = pipelineset_.rootsignature.Get();

	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineset_.pipelinestate));

}
