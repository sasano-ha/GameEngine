#pragma once

#include "BaseScene.h"

/// <summary>
/// �V�[���Ǘ�
/// </summary>
class SceneManager
{
public:
	~SceneManager();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	// ���V�[���̗\��
	void SetNextScene(BaseScene* nextScene) { nextScene_ = nextScene; }
private:
	// ���̃V�[��
	BaseScene* scene_ = nullptr;
	// ���̃V�[��
	BaseScene* nextScene_ = nullptr;
};

