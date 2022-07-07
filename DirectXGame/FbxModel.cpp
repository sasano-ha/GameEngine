#include "FbxModel.h"

void FbxModel::CreateBuffers(ID3D12Device* device)
{ 
	HRESULT result;
	// ���_�f�[�^�S�̂̃T�C�Y
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUvSkin) * vertices_.size());
	// ���_�o�b�t�@����
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff_));

	//���_�o�b�t�@�ւ̃f�[�^�]��
	VertexPosNormalUvSkin* vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		std::copy(vertices_.begin(), vertices_.end(), vertMap);
		vertBuff_->Unmap(0, nullptr);

		// ���_�o�b�t�@�r���[�iVBV�j�̍쐬
		vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
		vbView_.SizeInBytes = sizeVB;
		vbView_.StrideInBytes = sizeof(vertices_[0]);

		// ���_�C���f�b�N�X�S�̂̃T�C�Y
		UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices_.size());
		// �C���f�b�N�X�o�b�t�@����
		result = device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&indexBuff_));

		// �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
		unsigned short* indexMap = nullptr;
		result = indexBuff_->Map(0, nullptr, (void**)&indexMap);
		if (SUCCEEDED(result)) {
			std::copy(indices_.begin(), indices_.end(), indexMap);
			indexBuff_->Unmap(0, nullptr);
		}

		// �C���f�b�N�X�o�b�t�@�iIBV�j�̍쐬
		ibView_.BufferLocation = indexBuff_->GetGPUVirtualAddress();
		ibView_.Format = DXGI_FORMAT_R16_UINT;
		ibView_.SizeInBytes = sizeIB;

		// �e�N�X�`���摜�f�[�^
		const DirectX::Image* img = scratchImg_.GetImage(0, 0, 0);	// ���f�[�^���o
		assert(img);

		// ���\�[�X�ݒ�
		CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			metadata_.format,
			metadata_.width,
			(UINT)metadata_.height,
			(UINT16)metadata_.arraySize,
			(UINT16)metadata_.mipLevels);

		// �e�N�X�`���p�o�b�t�@�̐���
		result = device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
			D3D12_HEAP_FLAG_NONE,
			&texresDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&texbuff_));

		// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texbuff_->WriteToSubresource(
			0,
			nullptr,				// �S�̈�R�s�[
			img->pixels,			// ���f�[�^�A�h���X
			(UINT)img->rowPitch,	// 1���C���T�C�Y
			(UINT)img->slicePitch	// 1���T�C�Y
		);

		// SRV�f�X�N���v�^�q�[�v�𐶐�
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// �V�F�[�_���猩����悤��
		descHeapDesc.NumDescriptors = 1;	// �e�N�X�`������
		result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeapSRV_));

		// �V�F�[�_���\�[�X(SRV)�쐬
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};	// �ݒ�\����
		D3D12_RESOURCE_DESC resDesc = texbuff_->GetDesc();

		srvDesc.Format = resDesc.Format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	// 2D�e�N�X�`��
		srvDesc.Texture2D.MipLevels = 1;

		device->CreateShaderResourceView(texbuff_.Get(),	// �r���[�Ɗ֘A�t����o�b�t�@
			&srvDesc,	//�e�N�X�`���ݒ���
			descHeapSRV_->GetCPUDescriptorHandleForHeapStart()	// �q�[�v�̐擪�A�h���X
		);
	}
}

void FbxModel::Draw(ID3D12GraphicsCommandList* cmdList)
{

}
