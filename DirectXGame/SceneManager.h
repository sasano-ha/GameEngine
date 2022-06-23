#pragma once

#include "BaseScene.h"

/// <summary>
/// シーン管理
/// </summary>
class SceneManager
{
public:
	static SceneManager* GetInstance();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	// 次シーンの予約
	void SetNextScene(BaseScene* nextScene) { nextScene_ = nextScene; }
private:
	// 今のシーン
	BaseScene* scene_ = nullptr;
	// 次のシーン
	BaseScene* nextScene_ = nullptr;

	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	void operator = (const SceneManager&) = delete;
};

