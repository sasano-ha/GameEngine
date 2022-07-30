#include "TitleScene.h"
#include "SceneManager.h"
#include "Sound.h"
#include "input.h"
#include "DebugText.h"

void TitleScene::Initialize()
{
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/title.png");

	// �X�v���C�g�̐���
	sprite = Sprite::Create(1, { 0,0 }, false, false);
}

void TitleScene::Finalize()
{
	// �X�v���C�g���
	delete sprite;
}

void TitleScene::Update()
{

	Input* input = Input::GetInstance();

	// ���W����
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

	}

	if (input->TriggerKey(DIK_1))
	{
		// �V�[���؂�ւ�
		SceneManager::GetInstance()->ChangeScene("GAME");
	}

	//�X�v���C�g�X�V
	sprite->Update();
}

void TitleScene::Draw(DirectXCommon* dxCommon)
{
	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDraw();

	// �X�v���C�g�`��
	sprite->Draw();

	// �X�v���C�g���ʃR�}���h
	SpriteCommon::GetInstance()->PreDraw();
}