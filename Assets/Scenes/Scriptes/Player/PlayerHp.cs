using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    // シングルトン
    public static PlayerHp instance;

    // playerのHP
    public float playerMaxHp;

    // ダメージの変数
    public float damage;

    // 爆破を入れるための変数
    public GameObject explosionPrefab;

    public void Awake()
    {
        if(instance == null)
        {
            // インスタンスの設定
            instance = this;
        }
    }


    void Start()
    {
        // 生成時に体力を指定しておく
        playerMaxHp = 100;
        // ダメージの設定
        damage = 10;
    }

    // Update is called once per frame
    void Update()
    {
        // 自機のHpが0になったら
        if (playerMaxHp <= 0)
        {
            // 爆破パーティクルを生成させる。
            //Instantiate(explosionPrefab, transform.position, Quaternion.identity);

            // フラグを立てる。
            GameManager.instance.isPlayerAlive = false;

            // Hpが0以下になったら0より小さくしない
            playerMaxHp = 0;

            // 自機を消す。
            Destroy(this.gameObject);
        }
    }

    public void Player_Damage()
    {
        // ダメージを受けたら
        playerMaxHp -= damage;

        // ダメージリソースのフラグを立てる。
        FlushController.instance.DamageFlag = true;
    }
}
