#include "PostEffect.h"
#include "WinApp.h"
#include "input.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <cassert>
#include <d3dcompiler.h>
#include <wrl.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

// 静的メンバ変数の実体
const float PostEffect::clearColor[4] = { 0.25f, 0.5f, 0.1f, 0.0f };	//緑っぽい色

PostEffect::PostEffect()
	:Sprite()
{
	texNumber_ = 100;
	Sprite::SetPosition(position_);
	Sprite::SetSize(size_);
	anchorpoint_ = { 0, 0 };
	isFlipX_ = false;
	isFlipY_ = false;
}

void PostEffect::Initialize()
{
	HRESULT result;
	

	// 基底クラスとしての初期化
	//Sprite::SizeInitialize(100, { 500, 500 }, { 0, 0 }, false, false);

	// テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		WinApp::windows_width,
		(UINT)WinApp::windows_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	for (int i = 0; i < 2; i++) {
		// テクスチャバッファの生成
		result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
				D3D12_MEMORY_POOL_L0),
			D3D12_HEAP_FLAG_NONE,
			&texresDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clearColor),
			IID_PPV_ARGS(&texBuff_[i]));
		assert(SUCCEEDED(result));

		// テスクチャを赤クリアに
		// 画素数（1280 * 720 = 921600ピクセル）
		const UINT pixelCount = WinApp::windows_width * WinApp::windows_height;
		// 画素数1行分のデータサイズ
		const UINT rowPitch = sizeof(UINT) * WinApp::windows_width;
		// 画素全体のデータサイズ
		const UINT depthPich = rowPitch * WinApp::windows_height;
		// 画像イメージ
		UINT* img = new UINT[pixelCount];
		for (int j = 0; j < pixelCount; j++) { img[j] = 0xff0000ff; }

		// テクスチャバッファにデータを転送
		result = texBuff_[i]->WriteToSubresource(0, nullptr,
			img, rowPitch, depthPich);
		assert(SUCCEEDED(result));
		delete[] img;
	}


	// SRV用のデスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 1;
	// SRV用デスクリプタヒープを生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV_));
	assert(SUCCEEDED(result));

	// SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	// 設定構造体
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	// デスクリプタヒープにSRV作成
	spriteCommon->GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_[0].Get(),	// ビューと関連付けるバッファ
		&srvDesc,
		descHeapSRV_->GetCPUDescriptorHandleForHeapStart()
	);

	// RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 2;
	// RTV用デスクリプタヒープを生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV_));
	assert(SUCCEEDED(result));


	for (int i = 0; i < 2; i++) {
		// デスクリプタヒープにRTV作成
		spriteCommon->GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_[i].Get(),
			nullptr,
			CD3DX12_CPU_DESCRIPTOR_HANDLE(
				descHeapRTV_->GetCPUDescriptorHandleForHeapStart(), i,
				spriteCommon->GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV))
		);
	}
	

	// 深度バッファリソース設定
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			WinApp::windows_width,
			WinApp::windows_height,
			1, 0,
			1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);
	// 深度バッファの生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
		IID_PPV_ARGS(&depthBuff_));
	assert(SUCCEEDED(result));

	// DSV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	// DSV用デスクリプタヒープを作成
	result = spriteCommon->GetInstance()->GetDevice()->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV_));
	assert(SUCCEEDED(result));

	// デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	// 深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	spriteCommon->GetInstance()->GetDevice()->CreateDepthStencilView(depthBuff_.Get(),
		&dsvDesc,
		descHeapDSV_->GetCPUDescriptorHandleForHeapStart());

	// 頂点バッファ生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) *
			vertNum),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff_));
	assert(SUCCEEDED(result));

	// 頂点データ
	VertexPosUv vertices_[vertNum] = {
		//     u     v
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}}, // 左下
		{{-0.5f, +0.5f, 0.0f}, {0.0f, 0.0f}}, // 左上
		{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}}, // 右下
		{{+0.5f, +0.5f, 0.0f}, {1.0f, 0.0f}}, // 右上
	};

	// 頂点バッファへのデータ転送
	VertexPosUv* vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	memcpy(vertMap, vertices_, sizeof(vertices_));
	vertBuff_->Unmap(0, nullptr);

	// 頂点バッファビューの作成
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress(); 
	vbView_.SizeInBytes = sizeof(VertexPosUv) * 4;
	vbView_.StrideInBytes = sizeof(VertexPosUv);

	// 定数バッファの生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));

	CreateGrapicsPipelineState();
}

void PostEffect::Update()
{
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
	constMap->mat = XMMatrixIdentity();
	constMap->color = color_;
	constBuff_->Unmap(0, nullptr);
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isInvisible_) {
		return;
	}

	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();

	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	if (Input::GetInstance()->TriggerKey(DIK_9)) {
		// デスクリプタヒープにSRV作成
		static int tex = 0;
		// テクスチャ番号を0と1までに切り替え
		tex = (tex + 1) % 2;

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	// 設定構造体
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2Dテクスチャ
		srvDesc.Texture2D.MipLevels = 1;
		spriteCommon->GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_[tex].Get(),	// ビューと関連付けるバッファ
			&srvDesc,
			descHeapSRV_->GetCPUDescriptorHandleForHeapStart()
		);
	}

	// パイプラインステートの設定
	commandList->SetPipelineState(pipelineset_.pipelinestate.Get());

	// ルートシグネチャの設定
	commandList->SetGraphicsRootSignature(pipelineset_.rootsignature.Get());

	// プリミティブ形状を設定
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 頂点バッファをセット
	commandList->IASetVertexBuffers(0, 1, &vbView_);

	// テクスチャ用デスクリプタヒープの設定
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV_.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);


	// ルートパラメーター0番に定数バッファをセット
	commandList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

	// ルートパラメーター1番にシェーダリソースビューをセット
	spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);

	commandList->SetGraphicsRootDescriptorTable(1, descHeapSRV_->GetGPUDescriptorHandleForHeapStart());

	// ポリゴンの描画（4頂点で四角形）
	commandList->DrawInstanced(4, 1, 0, 0);
}

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	for (int i = 0; i < 2; i++) {
		// リソースバリアを変更（シェーダーリソース→描画可能）
		commandList->ResourceBarrier(1,
			&CD3DX12_RESOURCE_BARRIER::Transition(texBuff_[i].Get(),
				D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				D3D12_RESOURCE_STATE_RENDER_TARGET));
	}
	
	// レンダーターゲットビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHs[2];

	for (int i = 0; i < 2; i++) {
		rtvHs[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(
			descHeapRTV_->GetCPUDescriptorHandleForHeapStart(), i,
			spriteCommon->GetInstance()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)
		);
	}
		
	// 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV_->GetCPUDescriptorHandleForHeapStart();
	// レンダーターゲットをセット
	commandList->OMSetRenderTargets(2, rtvHs, true, &dsvH);
	// ビューポートの設定
	CD3DX12_VIEWPORT viewports[2];
	CD3DX12_RECT scissorRects[2];
	for (int i = 0; i < 2; i++) {
		viewports[i] = CD3DX12_VIEWPORT(0.0f, 0.0f, WinApp::windows_width, WinApp::windows_height);
		scissorRects[i] = CD3DX12_RECT(0, 0, WinApp::windows_width, WinApp::windows_height);
	}
	commandList->RSSetViewports(2, viewports);
	// シザリング矩形の設定
	commandList->RSSetScissorRects(2, scissorRects);

	for (int i = 0; i < 2; i++) {
		// 全画面クリア
		commandList->ClearRenderTargetView(rtvHs[i], clearColor, 0, nullptr);
	}
	
	// 深度バッファのクリア
	commandList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0,
		nullptr);
}

void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	// リソースバリアを変更（描画可能→リソースバリア）
	for (int i = 0; i < 2; i++) {
		commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texBuff_[i].Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
	}
	
}

void PostEffect::CreateGrapicsPipelineState()
{
	HRESULT result;

	ComPtr<ID3DBlob> vsBlob = nullptr; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob = nullptr; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/PostEffectTestVS.hlsl",  // シェーダファイル名
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
		assert(0);
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/shaders/PostEffectTestPS.hlsl",   // シェーダファイル名
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
		assert(0);
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

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定でのシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	// ルートシグネチャの生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&pipelineset_.rootsignature));
	assert(SUCCEEDED(result));

	// パイプラインにルートシグネチャをセット
	gpipeline.pRootSignature = pipelineset_.rootsignature.Get();

	result = spriteCommon->GetInstance()->GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineset_.pipelinestate));
	assert(SUCCEEDED(result));
}
