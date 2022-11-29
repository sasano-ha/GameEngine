using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    public static PlayerHp instance;

    // playerのHP
    public float playerHp;

    // ダメージの変数
    public float damage;


    public void Awake()
    {
        if(instance == null)
        {
            // インスタンスの設定
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        playerHp = 100;
        // ダメージの設定
        damage = 10;
    }

    // Update is called once per frame
    void Update()
    {
        if (playerHp <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    public void Damage()
    {
        playerHp -= damage;
    }
}
