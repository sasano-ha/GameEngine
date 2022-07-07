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
	// ���O
	std::string name;
	// ���[�J���X�P�[��
	DirectX::XMVECTOR scaling_ = { 1, 1, 1, 0 };
	// ���[�J����]�p
	DirectX::XMVECTOR rotation_ = { 0, 0, 0, 0 };
	// ���[�J���ړ�
	DirectX::XMVECTOR translation_ = { 0, 0, 0, 1 };
	// ���[�J���ό`�s��
	DirectX::XMMATRIX transform_;
	// �O���[�o���ό`�s��
	DirectX::XMMATRIX globalTransform_;
	// �e�m�[�h
	Node* parent_ = nullptr;
};

class FbxModel
{
private:	// �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImge = DirectX::ScratchImage;
	// std::���ȗ�
	using string = std::string;
	template <class T> using vector = std::vector<T>;

	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff_;
	// �C���b�f�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff_;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff_;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView_ = {};
	// �C���b�f�N�X�o�b�t�@�r���[ 
	D3D12_INDEX_BUFFER_VIEW ibView_ = {};
	// SRV�p�ŃX�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV_;

public:
	// �t�����h�N���X
	friend class FbxLoader;
	// �o�b�t�@����
	void CreateBuffers(ID3D12Device* device);
	// �`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	// ���f���̕ό`�s��擾
	const XMMATRIX& GetModelTransform() { return meshNode_->globalTransform_; }


private:
	// ���f����
	std::string name_;
	// �m�[�h�z��
	std::vector<Node> nodes_;
	// �A���r�G���g�W��
	DirectX::XMFLOAT3 ambient_ = { 1, 1, 1 };
	// �f�B�t���[�Y�W��
	DirectX::XMFLOAT3 diffuse_ = { 1, 1, 1 };
	// �e�N�X�`���f�[�^
	DirectX::TexMetadata metadata_ = {};
	// �X�N���b�`�C���[�W
	DirectX::ScratchImage scratchImg_ = {};

public:	// �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUvSkin
	{
		DirectX::XMFLOAT3 pos;				//xyz���W
		DirectX::XMFLOAT3 normal;			//�@���x�N�g��
		DirectX::XMFLOAT2 uv;				//uv���W
	};

	// ���b�V�������m�[�h
	Node* meshNode_ = nullptr;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUvSkin> vertices_;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices_;
};