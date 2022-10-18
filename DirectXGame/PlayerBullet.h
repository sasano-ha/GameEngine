#pragma once
#include "Object3d.h"

class PlayerBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialze(const Vector3 &position, const Vector3& velocity);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update();


	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsDead() const { return isDead_; }

private:
	Model* model_3 = nullptr;
	Object3d* bullet = nullptr;

	// スピード
	Vector3 velocity_;

	// 寿命
	static const int32_t kLifeTime = 60 * 3;

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};

