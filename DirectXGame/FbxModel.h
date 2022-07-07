#pragma once

#include <string>
#include <DirectXmath.h>
#include <vector>

struct Node
{
	// ���O
	std::string name;
	// ���[�J���X�P�[��
	DirectX::XMVECTOR scaling = { 1, 1, 1, 0 };
	// ���[�J����]�p
	DirectX::XMVECTOR rotation = { 0, 0, 0, 0 };
	// ���[�J���ړ�
	DirectX::XMVECTOR translation = { 0, 0, 0, 1 };
	// ���[�J���ό`�s��
	DirectX::XMMATRIX transform;
	// �O���[�o���ό`�s��
	DirectX::XMMATRIX globalTransform;
	// �e�m�[�h
	Node* parent = nullptr;
};

class FbxModel
{
public:
	// �t�����h�N���X
	friend class FbxLoader;
private:
	// ���f����
	std::string name;
	// �m�[�h�z��
	std::vector<Node> nodes;

public:	// �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUvSkin
	{
		DirectX::XMFLOAT3 pos;				//xyz���W
		DirectX::XMFLOAT3 normal;			//�@���x�N�g��
		DirectX::XMFLOAT2 uv;				//uv���W
	};

	//���b�V�������m�[�h
	Node* meshNode = nullptr;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUvSkin> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
};