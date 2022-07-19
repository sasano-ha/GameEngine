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
#include "PostEffect.h"


/// <summary>
/// �t���[�����[�N
/// </summary>

class GameBase
{
public:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	bool IsGetEndRequst() { return endRequst_; }

protected:
	bool endRequst_ = false;
	Input* input = nullptr;
	Sound* audio = nullptr;
	AbstractSceneFactory* sceneFactory_ = nullptr;
	Camera* camera_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	WinApp* winApp = nullptr;
};
