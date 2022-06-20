#include "input.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


void Input::Initialize(WinApp* winApp)
{
    HRESULT result;

    //�؂�Ă���WinApp�̃C���X�^���X���L�^
    this->winApp = winApp;

    // DirectInput�I�u�W�F�N�g�̐���
    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

    //�L�[�{�[�h�f�o�C�X����
    result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);

    //���̓f�[�^�`���Z�b�g
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��

    //�r���I���䃌�x���̃Z�b�g
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{
    HRESULT result;

    //�O��̃L�[���͂�ۑ�
    memcpy(keyPre, key, sizeof(key));

    //�L�[�{�[�h���̎擾�J�n
    result = devkeyboard->Acquire();

    //�S�L�[�̓��͏����擾����
    result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]) {
        return true;
    }
    //�����łȂ����false��Ԃ�
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    if (keyPre[keyNumber] && key[keyNumber]) {
        return true;
    }
    return false;
}