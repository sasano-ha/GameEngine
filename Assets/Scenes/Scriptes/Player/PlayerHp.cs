using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    public static PlayerHp instance;

    // player��HP
    public float playerMaxHp;

    // �_���[�W�̕ϐ�
    public float damage;

    public GameObject explosionPrefab;

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
        playerMaxHp = 10;
        // �_���[�W�̐ݒ�
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
