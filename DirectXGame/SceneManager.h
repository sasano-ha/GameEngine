#pragma once

#include "BaseScene.h"
#include "AbstractSceneFactory.h"
#include "PostEffect.h"
#include "DebugText.h"
#include "SpriteCommon.h"
#include "WinApp.h"
#include "DirectXCommon.h"

/// <summary>
/// シーン管理
/// </summary>
class SceneManager
{
public:
	static SceneManager* GetInstance();


	void Initialze(DirectXCommon* dxCommon, WinApp* winApp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dxCommon);
	// 次シーンの予約
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory) { sceneFactory_ = sceneFactory; }
private:
	// 今のシーン
	BaseScene* scene_ = nullptr;
	// 次のシーン
	BaseScene* nextScene_ = nullptr;
	// シーンファクトリ
	AbstractSceneFactory* sceneFactory_ = nullptr;

	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	void operator = (const SceneManager&) = delete;
	PostEffect* posteffect_ = nullptr;
	DebugText* debugText = nullptr;
	SpriteCommon* spritecommon = nullptr;
};

