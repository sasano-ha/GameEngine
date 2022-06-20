#pragma once

#include "input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Sound.h"

#include <vector>

/// <summary>
/// ゲーム固有のクラス
/// </summary>
class MyGameEngine
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

	bool IsGetEndRequst() { return endRequst_; }

private:
	bool endRequst_ = false;
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	DebugText* debugText = nullptr;
	Sound* audio = nullptr;
	SpriteCommon* spriteCommon = nullptr;


	std::vector<Sprite*> sprites;
	Model* model_1 = nullptr;
	Model* model_2 = nullptr;

	Object3d* object3d_1 = nullptr;
	Object3d* object3d_2 = nullptr;
	Object3d* object3d_3 = nullptr;
};

