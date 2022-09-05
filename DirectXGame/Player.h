#pragma once
#include "Object3d.h"

class Player
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
	Model* model_1 = nullptr;
	Object3d* player = nullptr;

	// �X�s�[�h
	float speed = 1.0f;
};

