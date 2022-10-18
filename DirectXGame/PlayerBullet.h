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

private:
	Model* model_3 = nullptr;
	Object3d* bullet = nullptr;
	bool bulletFlag = false;

	// bulletの半径
	float bulletRadius = 5.0f;

	// スピード
	Vector3 velocity_;
};

