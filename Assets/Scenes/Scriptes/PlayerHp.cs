using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    public static PlayerHp instance;

    // playerのHP
    public float playerHp;

    // Start is called before the first frame update
    void Start()
    {
        instance = this;
        // 生成時に体力を指定しておく
        playerHp = 100;
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
        playerHp -= 1;
    }
}
