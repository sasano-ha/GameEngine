using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    public static PlayerHp instance;

    // player��HP
    public float playerHp;

    // �_���[�W�̕ϐ�
    public float damage;


    public void Awake()
    {
        if(instance == null)
        {
            // �C���X�^���X�̐ݒ�
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        playerHp = 100;
        // �_���[�W�̐ݒ�
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
