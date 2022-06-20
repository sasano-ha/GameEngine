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
/// �Q�[���ŗL�̃N���X
/// </summary>
class MyGameEngine
{
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
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

