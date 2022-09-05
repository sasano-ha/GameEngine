#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "PostEffect.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

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

	
	Player* player_ = nullptr;
	Enemy* enemy_[3] = { nullptr };
	Bullet* bullet_ = nullptr;
	//Object3d* bullet = nullptr;

	FbxModel* fbxmodel_1 = nullptr;
	FbxObject3d* fbxobject_1 = nullptr;

	// �X�s�[�h
	float speed = 1.0f;

	// bullet�̃t���O
	//bool bulletFlag = false;

	// enemy�̃t���O
	float bulletRadius = 5.0f;
};

