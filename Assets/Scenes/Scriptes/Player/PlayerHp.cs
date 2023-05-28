using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    public static PlayerHp instance;

    // playerのHP
    public float playerMaxHp;

    // ダメージの変数
    public float damage;

    public GameObject explosionPrefab;

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
        playerMaxHp = 10;
        // ダメージの設定
        damage = 10;
    }

    // Update is called once per frame
    void Update()
    {
        if (playerMaxHp <= 0)
        {
            Instantiate(explosionPrefab, transform.position, Quaternion.identity);
            Destroy(this.gameObject);
            GameManager.instance.isPlayerAlive = false;
        }
    }

    public void Damage()
    {
        playerMaxHp -= damage;
        FlushController.instance.DamageFlag = true;
    }
}
