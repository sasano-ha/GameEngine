#pragma once

#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800  //DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include "WinApp.h"


// ����
class Input
{
public:
	// namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	struct MouseMove {
		LONG lX;	// �}�E�X��X���̌X���̏��
		LONG lY;	// �}�E�X��Y���̌X���̏��
		LONG lZ;	// �}�E�X��Z���̌X���̏��
	};

public:// �����o�֐�

	static Input* GetInstance();

	// ������
	void Initialize(WinApp* winApp);

	// �X�V
	void Update();

	/// <summary>
	///	�L�[�����������`�F�b�N
	/// </summary>
	/// <paragm name = "keyNumber">�L�[�ԍ��iDIK_0 ���j</paragm>
	/// <returns>������Ă��邩</return>
	bool PushKey(BYTE keyNumber);

	/// <summary>
	///	�L�[�̃g���K�[���`�F�b�N
	/// </summary>
		/// <paragm name = "keyNumber">�L�[�ԍ��iDIK_0 ���j</paragm>
	/// <returns>�g���K�[��</return>
	bool TriggerKey(BYTE keyNumber);

	/// <summary>
	/// �L�[�̍��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool PushMouseLeft();

	/// <summary>
	/// �L�[�̍��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool PushMouseRight();

	/// <summary>
	/// �L�[�̒��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool PushMouseMiddle();

	/// <summary>
	/// �L�[�̍��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// �L�[�̒��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool TriggerMouseMiddle();

private:// �����o�֐�
	// DirectInput�̃C���X�^���X����
	ComPtr<IDirectInput8> dinput = nullptr;
	// �L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devkeyboard;
	// �}�E�X�̃f�o�C�X
	ComPtr<IDirectInputDevice8> devMouse;
	// �S�L�[�̏��
	BYTE key[256] = {};
	// �O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
	// WindowsAPI
	WinApp* winApp = nullptr;
	// �S�}�E�X�̏��
	DIMOUSESTATE2 mouseState = {};
	// �O��}�E�X�̏�ԁi�j
	DIMOUSESTATE2 mouseStatePre = {};
};
