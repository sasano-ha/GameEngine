#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 描画コマンドリスト
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// シーン描画前処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// シーン描画後処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    // テクスチャバッファ
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff_;
    // SRV用デスクリプタヒープ
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV_;
    // 深度バッファ
    Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff_;
    // RTV用デスクリプタヒープ
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV_;
    // DSV用デスクリプタヒープ
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV_;

private:
    // 画面クリアー
    static const float clearColor[4];
};

