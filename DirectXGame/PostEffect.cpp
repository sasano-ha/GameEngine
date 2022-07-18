#include "PostEffect.h"
#include "WinApp.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <cassert>

using namespace DirectX;

// �ÓI�����o�ϐ��̎���
const float PostEffect::clearColor[4] = { 0.25f, 0.5f, 0.1f, 0.0f };	//�΂��ۂ��F

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
	//Sprite::SizeInitialize(100, { 500, 500 }, { 0, 0 }, false, false);

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
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM, clearColor),
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

	// RTV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	// RTV�p�f�X�N���v�^�q�[�v�𐶐�
	result = spriteCommon->GetInstance()->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV_));
	assert(SUCCEEDED(result));

	// �f�X�N���v�^�q�[�v��RTV�쐬
	spriteCommon->GetInstance()->GetDevice()->CreateRenderTargetView(texBuff_.Get(),
		nullptr,
		descHeapRTV_->GetCPUDescriptorHandleForHeapStart()
	);

	// �[�x�o�b�t�@���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			WinApp::windows_width,
			WinApp::windows_height,
			1, 0,
			1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);
	// �[�x�o�b�t�@�̐���
	result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
		IID_PPV_ARGS(&depthBuff_));
	assert(SUCCEEDED(result));

	// DSV�p�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	// DSV�p�f�X�N���v�^�q�[�v���쐬
	result = spriteCommon->GetInstance()->GetDevice()->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV_));
	assert(SUCCEEDED(result));

	// �f�X�N���v�^�q�[�v��DSV�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	// �[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	spriteCommon->GetInstance()->GetDevice()->CreateDepthStencilView(depthBuff_.Get(),
		&dsvDesc,
		descHeapDSV_->GetCPUDescriptorHandleForHeapStart());

	//// ���_�o�b�t�@����
	//result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) *
	//		vertNum),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&vertBuff_));
	//assert(SUCCEEDED(result));

	//// ���_�f�[�^
	//VertexPosUv vertices_[vertNum] = {
	//	//     u     v
	//	{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f}}, // ����
	//	{{-0.5f, +0.5f, 0.0f}, {0.0f, 0.0f}}, // ����
	//	{{+0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}}, // �E��
	//	{{+0.5f, +0.5f, 0.0f}, {1.0f, 0.0f}}, // �E��
	//};

	//// �����A����A�E���A�E��
	//enum { LB, LT, RB, RT };

	//float left = (0.0f - anchorpoint_.x) * size_.x;
	//float right = (1.0f - anchorpoint_.x) * size_.x;
	//float top = (0.0f - anchorpoint_.y) * size_.y;
	//float bottom = (1.0f - anchorpoint_.y) * size_.y;

	//if (isFlipX_)
	//{// ���E����ւ�
	//	left = -left;
	//	right = -right;
	//}

	//if (isFlipY_)
	//{// ���E����ւ�
	//	top = -top;
	//	bottom = -bottom;
	//}

	//vertices_[LB].pos = { left, bottom,  0.0f }; // ����
	//vertices_[LT].pos = { left, top,     0.0f }; // ����
	//vertices_[RB].pos = { right, bottom, 0.0f }; // �E��
	//vertices_[RT].pos = { right, top,    0.0f }; // �E��

	//// �w��ԍ��̉摜���ǂݍ��ݍς݂Ȃ�
	//if (spriteCommon->GetTexBuff(texNumber_)) {
	//	// �e�N�X�`�����擾
	//	D3D12_RESOURCE_DESC resDesc = spriteCommon->GetTexBuff(texNumber_)->GetDesc();

	//	float tex_left = texLeftTop_.x / resDesc.Width;
	//	float tex_right = (texLeftTop_.x + texSize_.x) / resDesc.Width;
	//	float tex_top = texLeftTop_.y / resDesc.Height;
	//	float tex_bottom = (texLeftTop_.y + texSize_.y) / resDesc.Height;

	//	vertices_[LB].uv = { tex_left,   tex_bottom }; // ����
	//	vertices_[LT].uv = { tex_left,   tex_top }; // ����
	//	vertices_[RB].uv = { tex_right,  tex_bottom }; // �E��
	//	vertices_[RT].uv = { tex_right,  tex_top }; // �E��
	//}

	//// ���_�o�b�t�@�ւ̃f�[�^�]��
	//VertexPosUv* vertMap = nullptr;
	//result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	//memcpy(vertMap, vertices_, sizeof(vertices_));
	//vertBuff_->Unmap(0, nullptr);

	//// ���_�o�b�t�@�r���[�̍쐬
	//vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress(); 
	//vbView_.SizeInBytes = sizeof(VertexPosUv) * 4;
	//vbView_.StrideInBytes = sizeof(VertexPosUv);

	//// �萔�o�b�t�@�̐���
	//result = spriteCommon->GetInstance()->GetDevice()->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&constBuff_));
	//assert(SUCCEEDED(result));

	//// �萔�o�b�t�@�̓]��
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

	// �p�C�v���C���X�e�[�g�̐ݒ�
	commandList->SetPipelineState(pipelineset_.pipelinestate.Get());

	// ���[�g�V�O�l�`���̐ݒ�
	commandList->SetGraphicsRootSignature(pipelineset_.rootsignature.Get());

	// �v���~�e�B�u�`���ݒ�
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ���_�o�b�t�@���Z�b�g
	commandList->IASetVertexBuffers(0, 1, &vbView_);

	// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐ݒ�
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

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	// ���\�[�X�o���A��ύX�i�V�F�[�_�[���\�[�X���`��\�j
	commandList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(),
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			D3D12_RESOURCE_STATE_RENDER_TARGET));
	// �����_�[�^�[�Q�b�g�r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV_->GetCPUDescriptorHandleForHeapStart();
	// �[�x�X�e���V���r���[�p�f�X�N���v�^�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV_->GetCPUDescriptorHandleForHeapStart();
	// �����_�[�^�[�Q�b�g���Z�b�g
	commandList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
	// �r���[�|�[�g�̐ݒ�
	commandList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f,
		WinApp::windows_width, WinApp::windows_height));
	// �V�U�����O��`�̐ݒ�
	commandList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, WinApp::windows_width,
		WinApp::windows_height));

	// �S��ʃN���A
	commandList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	// �[�x�o�b�t�@�̃N���A
	commandList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0,
		nullptr);
}

void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = spriteCommon->GetCommandList();

	// ���\�[�X�o���A��ύX�i�`��\�����\�[�X�o���A�j
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texBuff_.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
}
