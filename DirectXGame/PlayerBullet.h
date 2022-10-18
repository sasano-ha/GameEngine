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

	bool IsDead() const { return isDead_; }

private:
	Model* model_3 = nullptr;
	Object3d* bullet = nullptr;

	// �X�s�[�h
	Vector3 velocity_;

	// ����
	static const int32_t kLifeTime = 60 * 3;

	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};

