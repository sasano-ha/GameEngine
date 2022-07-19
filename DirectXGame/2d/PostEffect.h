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

    void Update();

    /// <summary>
    /// �`��R�}���h���X�g
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �V�[���`��O����
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �V�[���`��㏈��
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    void CreateGrapicsPipelineState();

    // �e�N�X�`���o�b�t�@
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff_[2];
    // SRV�p�f�X�N���v�^�q�[�v
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV_;
    // �[�x�o�b�t�@
    Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff_;
    // RTV�p�f�X�N���v�^�q�[�v
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV_;
    // DSV�p�f�X�N���v�^�q�[�v
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV_;
    // �O���t�B�b�N�p�C�v���C��
    Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState_;
    // ���[�g�V�O�l�`��
    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_;

private:
    // ��ʃN���A�[
    static const float clearColor[4];
};
