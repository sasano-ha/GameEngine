#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PostEffect();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �`��R�}���h���X�g
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    // �e�N�X�`���o�b�t�@
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff_;
    // SRV�p�f�X�N���v�^�q�[�v
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV_;
};

