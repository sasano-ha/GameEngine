#pragma once
#include "Object3d.h"

class PlayerBullet
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialze(const Vector3 &position, const Vector3& velocity);

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
	bool bulletFlag = false;

	// bullet�̔��a
	float bulletRadius = 5.0f;

	// �X�s�[�h
	Vector3 velocity_;
};

