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
/// ゲームシーン
/// </summary>
class GameScene : public BaseScene
{
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
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

	// スピード
	float speed = 1.0f;

	// bulletのフラグ
	//bool bulletFlag = false;

	// enemyのフラグ
	float bulletRadius = 5.0f;
};

