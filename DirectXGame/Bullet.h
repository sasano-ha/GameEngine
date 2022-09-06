#pragma once
#include "Object3d.h"

class Bullet
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
	Model* model_3 = nullptr;
	Object3d* bullet = nullptr;

	// bullet�̃t���O
	bool bulletFlag = false;

	// bullet�̔��a
	float bulletRadius = 5.0f;

	// �X�s�[�h
	float speed = 1.0f;
};

