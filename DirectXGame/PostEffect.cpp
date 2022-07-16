#include "PostEffect.h"

#include <d3d12.h>

using namespace DirectX;

PostEffect::PostEffect()
{
	texNumber_  = 100;
	Sprite::SetPosition(position_);
	Sprite::SetSize(size_);
	anchorpoint_ = { 0, 0 };
	isFlipX_ = false;
	isFlipY_  = false;
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

	// ルートパラメーター0番に定数バッファをセット
	commandList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

	// ルートパラメーター1番にシェーダリソースビューをセット
	spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);

	// ポリゴンの描画（4頂点で四角形）
	commandList->DrawInstanced(4, 1, 0, 0);
}