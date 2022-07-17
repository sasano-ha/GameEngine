#include "PostEffect.h"
#include "WinApp.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <cassert>

using namespace DirectX;

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

	// ���N���X�Ƃ��Ă̏�����
	Sprite::SizeInitialize(100, { 500, 500 }, { 0, 0 }, false, false);

	// �e�N�X�`�����\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		WinApp::windows_width,
		(UINT)WinApp::windows_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	// �e�N�X�`���o�b�t�@�̐���
	result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
			D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(&texBuff_));
	assert(SUCCEEDED(result));

	// �e�X�N�`����ԃN���A��
	// ��f���i1280 * 720 = 921600�s�N�Z���j
	const UINT pixelCount = WinApp::windows_width * WinApp::windows_height;
	// ��f��1�s���̃f�[�^�T�C�Y
	const UINT rowPitch = sizeof(UINT) * WinApp::windows_width;
	// ��f�S�̂̃f�[�^�T�C�Y
	const UINT depthPich = rowPitch * WinApp::windows_height;
	// �摜�C���[�W
	UINT* img = new UINT[pixelCount];
	for (int i = 0; i < pixelCount; i++) { img[i] = 0xff0000ff; }

	// �e�N�X�`���o�b�t�@�Ƀf�[�^��]��
	result = texBuff_->WriteToSubresource(0, nullptr,
		img, rowPitch, depthPich);
	assert(SUCCEEDED(result));
	delete[] img;



	// SRV�p�̃f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 1;
	// SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = spriteCommon->GetInstance()->GetDevice()->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV_));
	assert(SUCCEEDED(result));

	// SRV�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	// �ݒ�\����
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	// �f�X�N���v�^�q�[�v��SRV�쐬
	spriteCommon->GetInstance()->GetDevice()->CreateShaderResourceView(texBuff_.Get(),	// �r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc,
		descHeapSRV_->GetCPUDescriptorHandleForHeapStart()
	);
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
	if (isInvisible_) {
		return;
	}

	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();

	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	// �p�C�v���C���X�e�[�g�̐ݒ�
	commandList->SetPipelineState(pipelineset_.pipelinestate.Get());

	// ���[�g�V�O�l�`���̐ݒ�
	commandList->SetGraphicsRootSignature(pipelineset_.rootsignature.Get());

	// �v���~�e�B�u�`���ݒ�
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ���_�o�b�t�@���Z�b�g
	commandList->IASetVertexBuffers(0, 1, &vbView_);

	//// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐ݒ�
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV_.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);


	// ���[�g�p�����[�^�[0�Ԃɒ萔�o�b�t�@���Z�b�g
	commandList->SetGraphicsRootConstantBufferView(0, constBuff_->GetGPUVirtualAddress());

	// ���[�g�p�����[�^�[1�ԂɃV�F�[�_���\�[�X�r���[���Z�b�g
	spriteCommon->SetGraphicsRootDescriptorTable(1, texNumber_);

	commandList->SetGraphicsRootDescriptorTable(1, descHeapSRV_->GetGPUDescriptorHandleForHeapStart());

	// �|���S���̕`��i4���_�Ŏl�p�`�j
	commandList->DrawInstanced(4, 1, 0, 0);
}