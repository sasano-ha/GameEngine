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
#include "SceneManager.h"
#include "AbstractSceneFactory.h"
#include "FbxLoader.h"
#include "Camera.h"


/// <summary>
/// フレームワーク
/// </summary>

class GameBase
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	bool IsGetEndRequst() { return endRequst_; }

protected:
	bool endRequst_ = false;
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	DebugText* debugText = nullptr;
	Sound* audio = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	AbstractSceneFactory* sceneFactory_ = nullptr;
	Camera* camera_ = nullptr;
};

