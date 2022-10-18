#pragma once
#include <memory>
#include <list>

#include "Object3d.h"
#include "PlayerBullet.h"

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

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();

private:
	Model* model_1 = nullptr;
	Object3d* player = nullptr;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	// スピード
	const float speed = 0.5f;

public:
	
};

