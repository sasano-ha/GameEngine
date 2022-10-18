#pragma once
#include <memory>
#include <list>

#include "Object3d.h"
#include "PlayerBullet.h"

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

	/// <summary>
	/// �U������
	/// </summary>
	void Attack();

private:
	Model* model_1 = nullptr;
	Object3d* player = nullptr;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	// �X�s�[�h
	const float speed = 0.5f;

public:
	
};

