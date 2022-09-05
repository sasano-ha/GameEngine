#pragma once
#include "Object3d.h"

class Player
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
	Model* model_1 = nullptr;
	Object3d* player = nullptr;

	// スピード
	float speed = 1.0f;
};

