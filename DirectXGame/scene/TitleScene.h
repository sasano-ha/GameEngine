#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DirectXCommon.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public BaseScene
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
	void Draw(DirectXCommon* dxCommon) override;

private:
	Sprite* sprite = nullptr;
};

