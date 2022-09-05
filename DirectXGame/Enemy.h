#pragma once
#include "Object3d.h"

class Enemy
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
	Model* model_2 = nullptr;
	Object3d* enemy[3] = { nullptr };

	// enemyのフラグ
	bool enemyFlag[3] = { true, true, true };

	// enemyの半径
	float enemuyRadius[3] = { 5.0f };
};

