using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    // �V���O���g��
    public static PlayerHp instance;

    // player��HP
    public float playerMaxHp;

    // �_���[�W�̕ϐ�
    public float damage;

    // ���j�����邽�߂̕ϐ�
    public GameObject explosionPrefab;

    public void Awake()
    {
        if(instance == null)
        {
            // �C���X�^���X�̐ݒ�
            instance = this;
        }
    }


    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        playerMaxHp = 100;
        // �_���[�W�̐ݒ�
        damage = 10;
    }

    // Update is called once per frame
    void Update()
    {
        // ���@��Hp��0�ɂȂ�����
        if (playerMaxHp <= 0)
        {
            // ���j�p�[�e�B�N���𐶐�������B
            //Instantiate(explosionPrefab, transform.position, Quaternion.identity);

            // �t���O�𗧂Ă�B
            GameManager.instance.isPlayerAlive = false;

            // Hp��0�ȉ��ɂȂ�����0��菬�������Ȃ�
            playerMaxHp = 0;

            // ���@�������B
            Destroy(this.gameObject);
        }
    }

    public void Player_Damage()
    {
        // �_���[�W���󂯂���
        playerMaxHp -= damage;

        // �_���[�W���\�[�X�̃t���O�𗧂Ă�B
        FlushController.instance.DamageFlag = true;
    }
}
