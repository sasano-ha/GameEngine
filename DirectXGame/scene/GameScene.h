#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "PostEffect.h"

#include <DirectXMath.h>

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene : public BaseScene
{
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

private:
	Sprite* sprite_1 = nullptr;
	Sprite* sprite_2 = nullptr;
	Model* model_1 = nullptr;
	Model* model_2 = nullptr;

	Object3d* player = nullptr;
	Object3d* enemy[3] = { nullptr };
	Object3d* bullet = nullptr;

	FbxModel* fbxmodel_1 = nullptr;
	FbxObject3d* fbxobject_1 = nullptr;

	// �X�s�[�h
	float speed = 1.0f;

	// bullet�̃t���O
	bool bulletFlag = false;

	// enemy�̃t���O
	bool enemyFlag[3] = { true, true, true };

	float bulletRadius = 5.0f;
	float enemuyRadius[3] = { 5.0f };
};

