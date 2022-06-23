#pragma once

#include "Sprite.h"
#include "Object3d.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

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
	Sprite* sprite = nullptr;
	Model* model_1 = nullptr;
	Model* model_2 = nullptr;

	Object3d* object3d_1 = nullptr;
	Object3d* object3d_2 = nullptr;
	Object3d* object3d_3 = nullptr;
};

