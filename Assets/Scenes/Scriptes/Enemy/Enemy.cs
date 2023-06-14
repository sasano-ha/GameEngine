using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    // �A�^�b�`���邽�߂̂���
    [SerializeField] GameObject explosionPrefab;

    // Enemy�̗̑͗p�ϐ�
    public float enemyHp;

    // �J�����̃t���O
    public bool isInsideCamera = true;

    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        enemyHp = 1;
    }

    // Update is called once per frame
    void Update()
    {
        // �G���J�������ɂ��鎞
        if (isInsideCamera == true)
        {
            En_Die();
        }

        // enemy���J�����O�ɍs������
        else if (isInsideCamera == false)
        {
            // enemy�̃I�u�W�F�N�g�������B
            Destroy(this.gameObject);
        }

    }

    // �J�����t���O�֐�
    public void OnBecameInvisible()
    {
        isInsideCamera = false;
    }

    // enemy�_���[�W�֐�
    public void Damage()
    {
        enemyHp -= 1.0f;

        if (enemyHp <= 0)
        {
            enemyHp = 0;
        }
    }

    public void En_Die()
    {
        // �����̗͂�0�ȉ��ɂȂ�����
        if (enemyHp == 0)
        {
            // �����p�[�e�B�N��
            Instantiate(explosionPrefab, transform.position, Quaternion.identity);

            // enemy�_�E�����֐��̌Ăяo���B
            GameManager.instance.AddCrushingCount();

            // �����ŏ�����B
            Destroy(this.gameObject);
        }
    }
}
