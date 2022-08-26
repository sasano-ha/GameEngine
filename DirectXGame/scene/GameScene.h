#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "PostEffect.h"

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
	Model* model_1 = nullptr;
	Model* model_2 = nullptr;

	Object3d* player = nullptr;
	Object3d* enemy[3] = { nullptr };
	Object3d* bullet = nullptr;

	FbxModel* fbxmodel_1 = nullptr;
	FbxObject3d* fbxobject_1 = nullptr;

	// スピード
	float speed = 1.0f;

	// bulletのフラグ
	bool bulletFlag = false;

	// enemyのフラグ
	bool enemyFlag[3] = { true, true, true };

	float bulletRadius = 5.0f;
	float enemuyRadius[3] = { 5.0f };
};

