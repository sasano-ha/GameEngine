#pragma once

#include "GameBase.h"

#include <vector>



/// <summary>
/// ゲーム固有のクラス
/// </summary>
class MyGameEngine : public GameBase
{
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
	void Draw();

private:

	//GameScene* scene_ = nullptr;
};

