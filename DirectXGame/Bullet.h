#pragma once
#include "Object3d.h"

class Bullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialze();

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

	// bulletのフラグ
	bool bulletFlag = false;

	// bulletの半径
	float bulletRadius = 5.0f;

	// スピード
	float speed = 1.0f;
};

