#pragma once
#include "Object3d.h"

class Enemy
{
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialze();

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

private:
	Model* model_2 = nullptr;
	Object3d* enemy[3] = { nullptr };

	// enemy�̃t���O
	bool enemyFlag[3] = { true, true, true };

	// enemy�̔��a
	float enemuyRadius[3] = { 5.0f };
};

