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
protected:	// �G�C���A�X
	// Microosoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	// �ÓI�����o�֐�
	// setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device_ = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera_ = camera; }

	/// <summary>
	///�O���t�B�b�N�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();

private:	// �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device_;
	// �J����
	static Camera* camera_;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature_;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate_;

public:	// �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\���́i���W�ϊ��s��j
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	// �r���[�v���W�F�N�V�����s��
		XMMATRIX world;		// ���[���h�s��
		XMFLOAT3 cameraPos;	// �J�����s��i���[���h���W�j
	};

public:	// �����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[��
	/// </summary>
	void Updata();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	/// <param name="model">���f��</param>
	void SetModel(FbxModel* fbxmodel) { this->fbxmodel_ = fbxmodel; }

protected:	// �����o�ϐ�
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform_;
	// ���[�J���X�P�[��
	XMFLOAT3 scale_ = { 1, 1, 1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation_ = { 0, 0, 0 };
	// ���[�J�����W
	XMFLOAT3 position_ = { 0, 0, 0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld_;
	// ���f��
	FbxModel* fbxmodel_ = nullptr;
	// �萔�o�b�t�@�i�X�L���j
	ComPtr<ID3D12Resource> constBuffSkin_;

public:	// �萔
	// �{�[���̍ő吔
	static const int MAX_BONES = 32;

	// �萔�o�b�t�@�p�f�[�^�\���́i�X�L�j���O�j
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
};

