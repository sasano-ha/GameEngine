#pragma once

#include "GameBase.h"

#include <vector>

class GameScene;

/// <summary>
/// �Q�[���ŗL�̃N���X
/// </summary>
class MyGameEngine : public GameBase
{
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	// �V�[��
	GameScene* scene_ = nullptr;
};

