using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    public static PlayerHp instance;

    // player��HP
    public float playerHp;

    // Start is called before the first frame update
    void Start()
    {
        instance = this;
        // �������ɑ̗͂��w�肵�Ă���
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
