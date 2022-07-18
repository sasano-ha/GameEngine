#pragma once

#include "BaseScene.h"
#include "AbstractSceneFactory.h"
#include "PostEffect.h"
#include "DebugText.h"
#include "SpriteCommon.h"
#include "WinApp.h"
#include "DirectXCommon.h"

/// <summary>
/// �V�[���Ǘ�
/// </summary>
class SceneManager
{
public:
	static SceneManager* GetInstance();


	void Initialze(DirectXCommon* dxCommon, WinApp* winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon);
	// ���V�[���̗\��
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory) { sceneFactory_ = sceneFactory; }
private:
	// ���̃V�[��
	BaseScene* scene_ = nullptr;
	// ���̃V�[��
	BaseScene* nextScene_ = nullptr;
	// �V�[���t�@�N�g��
	AbstractSceneFactory* sceneFactory_ = nullptr;

	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	void operator = (const SceneManager&) = delete;
	PostEffect* posteffect_ = nullptr;
	DebugText* debugText = nullptr;
	SpriteCommon* spritecommon = nullptr;
};

