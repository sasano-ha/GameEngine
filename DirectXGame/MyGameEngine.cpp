#include "MyGameEngine.h"

void MyGameEngine::Initialize()
{
	//���N���X�̏���������
	GameBase::Initialize();

#pragma region �`�揉��������

	//OBJ���烂�f���f�[�^��ǂݍ���
	model_1 = Model::LoadFromOBJ("ground");
	model_2 = Model::LoadFromOBJ("triangle_mat");
	//3D�I�u�W�F�N�g����
	object3d_1 = Object3d::Create();
	object3d_2 = Object3d::Create();
	object3d_3 = Object3d::Create();
	//3D�I�u�W�F�N�g��3D���f�����Ђ��Â�
	object3d_1->SetModel(model_1);
	object3d_2->SetModel(model_2);
	object3d_3->SetModel(model_2);

	object3d_2->SetScale({ 20.0f, 20.0f, 20.0f });
	object3d_3->SetScale({ 30.0f, 30.0f, 30.0f });


	object3d_2->SetPosition({ -5, 0, -5 });
	object3d_3->SetPosition({ +5, 0, +5 });

	//// �����ǂݍ���
	//audio->LoadWave("Alarm01.wav");
	//// �����Đ�
	//audio->PlayWave("Alarm01.wav");

	// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(1, L"Resources/texture.png");
	spriteCommon->LoadTexture(2, L"Resources/house.png");

	

	// �X�v���C�g�̐���
	for (int i = 0; i < 20; i++)
	{
		int texNumber = 1;
		Sprite* sprite = Sprite::Create(spriteCommon, texNumber, { 0,0 }, false, false);

		// �X�v���C�g�̍��W�ύX
		sprite->SetPosition({ (float)(rand() % 1280), (float)(rand() % 720), 0 });
		sprite->SetRotation((float)(rand() % 360));
		sprite->SetSize({ (float)(rand() % 400), (float)(rand() % 400) });
		//sprites[i].isInvisible = true;
		//sprites[i].size.x = 400.0f;
		//sprites[i].size.y = 100.0f;
		// ���_�o�b�t�@�ɔ��f
		sprite->TransferVertexBuffer();

		sprites.push_back(sprite);
	}
#pragma endregion �`�揉��������
}

void MyGameEngine::Finalize()
{
	

	// �X�v���C�g���
	for (auto& sprite : sprites) {
		delete sprite;
	}
	sprites.clear();


	// 3D�I�u�W�F�N�g���
	delete model_1;
	delete model_2;

	// 3D�I�u�W�F�N�g���
	delete object3d_1;
	delete object3d_2;
	delete object3d_3;

	//���N���X�̏���������
	GameBase::Finalize();
}

void MyGameEngine::Update()
{
	

#pragma region DirectX���t���[������
	// DirectX���t���[�������@��������

	

	float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ۂ��F

	if (input->PushKey(DIK_SPACE))     // �X�y�[�X�L�[��������Ă�����
	{
		// ��ʃN���A�J���[�̐��l������������
		clearColor[1] = 1.0f;
	}

	// ���W����
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{

	}

	if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{

	}

	debugText->Print("Hello,DirectX!!", 200, 100);
	debugText->Print("Nihon Kogakuin", 200, 200, 2.0f);

	//3D�I�u�W�F�N�g�X�V
	object3d_1->Update();
	object3d_2->Update();
	object3d_3->Update();

	//�X�v���C�g�X�V
	for (auto& sprite : sprites) {
		sprite->Update();
	}

	// DirectX���t���[�������@�����܂�
#pragma endregion DirectX���t���[������
}

void MyGameEngine::Draw()
{
	//�`��O����
	dxCommon->PreDraw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCmdList());

	//3D�I�u�W�F�N�g�̕`��
	object3d_1->Draw();
	object3d_2->Draw();
	object3d_3->Draw();

	//3D�I�u�W�F�N�g�̕`��㏈��
	Object3d::PostDraw();

	// �X�v���C�g���ʃR�}���h
	spriteCommon->PreDraw();

	for (auto& sprite : sprites) {
		sprite->Draw();
	}

	// �f�o�b�O�e�L�X�g�`��
	debugText->DrawAll();

	// �S�D�`��R�}���h�����܂�

	//�`��㏈��
	dxCommon->PostDraw();
}
