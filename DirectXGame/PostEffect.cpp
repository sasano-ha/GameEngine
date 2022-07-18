#include "PostEffect.h"
#include "WinApp.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <cassert>

using namespace DirectX;

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

	// テクスチャバッファの生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
			D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clearColor),
		IID_PPV_ARGS(&texBuff_));
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
	for (int i = 0; i < pixelCount; i++) { img[i] = 0xff0000ff; }

	// テクスチャバッファにデータを転送
	result = texBuff_->WriteToSubresource(0, nullptr,
		img, rowPitch, depthPich);
	assert(SUCCEEDED(result));
	delete[] img;



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
	spriteCommon->GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_.Get(),	// ビューと関連付けるバッファ
		&srvDesc,
		descHeapSRV_->GetCPUDescriptorHandleForHeapStart()
	);

	// RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	// RTV用デスクリプタヒープを生成
	result = spriteCommon->GetInstance()->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV_));
	assert(SUCCEEDED(result));

	// デスクリプタヒープにRTV作成
	spriteCommon->GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_.Get(),
		nullptr,
		descHeapRTV_->GetCPUDescriptorHandleForHeapStart()
	);

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

	//// 頂点バッファ生成
	//result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) *
	//		vertNum),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&vertBuff_));
	//assert(SUCCEEDED(result));

	//// 頂点データ
	//VertexPosUv vertices_[vertNum] = {
	//	//     u     v
	//	{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}}, // 左下
	//	{{-0.5f, +0.5f, 0.0f}, {0.0f, 0.0f}}, // 左上
	//	{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}}, // 右下
	//	{{+0.5f, +0.5f, 0.0f}, {1.0f, 0.0f}}, // 右上
	//};

	//// 左下、左上、右下、右上
	//enum { LB, LT, RB, RT };

	//float left = (0.0f - anchorpoint_.x) * size_.x;
	//float right = (1.0f - anchorpoint_.x) * size_.x;
	//float top = (0.0f - anchorpoint_.y) * size_.y;
	//float bottom = (1.0f - anchorpoint_.y) * size_.y;

	//if (isFlipX_)
	//{// 左右入れ替え
	//	left = -left;
	//	right = -right;
	//}

	//if (isFlipY_)
	//{// 左右入れ替え
	//	top = -top;
	//	bottom = -bottom;
	//}

	//vertices_[LB].pos = { left, bottom,  0.0f }; // 左下
	//vertices_[LT].pos = { left, top,     0.0f }; // 左上
	//vertices_[RB].pos = { right, bottom, 0.0f }; // 右下
	//vertices_[RT].pos = { right, top,    0.0f }; // 右上

	//// 指定番号の画像が読み込み済みなら
	//if (spriteCommon->GetTexBuff(texNumber_)) {
	//	// テクスチャ情報取得
	//	D3D12_RESOURCE_DESC resDesc = spriteCommon->GetTexBuff(texNumber_)->GetDesc();

	//	float tex_left = texLeftTop_.x / resDesc.Width;
	//	float tex_right = (texLeftTop_.x + texSize_.x) / resDesc.Width;
	//	float tex_top = texLeftTop_.y / resDesc.Height;
	//	float tex_bottom = (texLeftTop_.y + texSize_.y) / resDesc.Height;

	//	vertices_[LB].uv = { tex_left,   tex_bottom }; // 左下
	//	vertices_[LT].uv = { tex_left,   tex_top }; // 左上
	//	vertices_[RB].uv = { tex_right,  tex_bottom }; // 右下
	//	vertices_[RT].uv = { tex_right,  tex_top }; // 右上
	//}

	//// 頂点バッファへのデータ転送
	//VertexPosUv* vertMap = nullptr;
	//result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	//memcpy(vertMap, vertices_, sizeof(vertices_));
	//vertBuff_->Unmap(0, nullptr);

	//// 頂点バッファビューの作成
	//vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress(); 
	//vbView_.SizeInBytes = sizeof(VertexPosUv) * 4;
	//vbView_.StrideInBytes = sizeof(VertexPosUv);

	//// 定数バッファの生成
	//result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&constBuff_));
	//assert(SUCCEEDED(result));

	//// 定数バッファの転送
	//ConstBufferData* constMap = nullptr;
	//result = constBuff_->Map(0, nullptr, (void**)&constMap);
	//if (SUCCEEDED(result)) {
	//	constMap->mat = XMMatrixIdentity();
	//	constMap->color = color_;
	//	constBuff_->Unmap(0, nullptr);
	//}
	
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
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

	// リソースバリアを変更（シェーダーリソース→描画可能）
	commandList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET));
	// レンダーターゲットビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV_->GetCPUDescriptorHandleForHeapStart();
	// 深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV_->GetCPUDescriptorHandleForHeapStart();
	// レンダーターゲットをセット
	commandList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
	// ビューポートの設定
	commandList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f,
		WinApp::windows_width, WinApp::windows_height));
	// シザリング矩形の設定
	commandList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, WinApp::windows_width,
		WinApp::windows_height));

	// 全画面クリア
	commandList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	// 深度バッファのクリア
	commandList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0,
		nullptr);
}

void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	// リソースバリアを変更（描画可能→リソースバリア）
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
}
