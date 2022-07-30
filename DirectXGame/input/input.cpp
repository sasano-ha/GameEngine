#include "input.h"
#include "Object3d.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


Input* Input::GetInstance()
{
    static Input instance;

    return &instance;
}

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

    // �}�E�X�f�o�C�X�̐���	
    result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);

    // ���̓f�[�^�`���Z�b�g
    result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��

    // �r���I���䃌�x���̃Z�b�g
    result = devkeyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

    // ���̓f�[�^�`���̃Z�b�g
    result = devMouse->SetDataFormat(&c_dfDIMouse2); // �W���`��

    // �r�����䃌�x���̃Z�b�g
    result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Input::Update()
{
    HRESULT result;

    // �O��̃L�[���͂�ۑ�
    memcpy(keyPre, key, sizeof(key));

    // �L�[�{�[�h���̎擾�J�n
    result = devkeyboard->Acquire();

    // �S�L�[�̓��͏����擾����
    result = devkeyboard->GetDeviceState(sizeof(key), key);

    // �}�E�X���̎擾�J�n
    result = devMouse->Acquire();

    // �O��̓��͂�ۑ�
    mouseStatePre = mouseState;

    // �}�E�X�̓���
    result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);

    MousePos();
}

POINT Input::MousePos()
{
    GetCursorPos(&mousePos_);
    // �擾�����X�N���[�����W���E�B���h�E���W�ɕϊ�����
    ScreenToClient(winApp->GetHwnd(), &mousePos_);

    return mousePos_;
}

bool Input::PushKey(BYTE keyNumber)
{
    // �w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]) {
        return true;
    }
    // �����łȂ����false��Ԃ�
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    if (!keyPre[keyNumber] && key[keyNumber]) {
        return true;
    }
    return false;
}

bool Input::PushMouseLeft()
{
    // ���N���b�N�������Ă���
    if (mouseState.rgbButtons[0]) {
        return true;
    }
    // �����Ă��Ȃ�
    return false;
}

bool Input::PushMouseRight()
{
    // �E�N���b�N�������Ă���
    if (mouseState.rgbButtons[1]) {
        return true;
    }
    // �����Ă��Ȃ�
    return false;
}

bool Input::PushMouseMiddle()
{
    // ���S�N���b�N�������Ă���
    if (mouseState.rgbButtons[2]) {
        return true;
    }
    // �����Ă��Ȃ�
    return false;
}

bool Input::TriggerMouseLeft()
{
    // �O��0�ŁA����0�łȂ���΃g���K�[
    if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
        return true;
    }

    // �g���K�[�łȂ�
    return false;
}

bool Input::TriggerMouseRight()
{
    // �O��0�ŁA����0�łȂ���΃g���K�[
    if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1]) {
        return true;
    }

    // �g���K�[�łȂ�
    return false;
}

bool Input::TriggerMouseMiddle()
{
    // �O��0�ŁA����0�łȂ���΃g���K�[
    if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
        return true;
    }

    // �g���K�[�łȂ�
    return false;
}
