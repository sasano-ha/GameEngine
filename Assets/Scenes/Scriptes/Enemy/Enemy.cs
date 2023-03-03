using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy: MonoBehaviour
{
    // Enemy�̗̑͗p�ϐ�
    private int enemyHp;

    // �_����������̕ϐ��B
    private Vector3 targetpos;

    // gameManager�Ăяo��
    public GameManager gameManager;

    // �X�R�A�N���X�̌Ăяo���B
    public Score scores;

    // �A�^�b�`���邽�߂̂���
    [SerializeField] GameObject explosionPrefab;

    // �J�����̃t���O
    private bool isInsideCamera = true;

    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        enemyHp = 2;

        // �ϐ��Ɋi�[����B
        targetpos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        // �G���J�������ɂ��鎞
        if(isInsideCamera == true)
        {
            // �X�s�[�h��^����
            //targetpos.z -= 0.005f;

            //if (targetpos.z <= 2)
            //{
            //    targetpos.x += 0.1f;
            //    targetpos.z -= 0.1f;
            //}

            //targetpos.x -= 0.01f;

            // �ʒu�̍X�V
            transform.position = new Vector3(Mathf.Sin(Time.time) * 2.0f + targetpos.x, targetpos.y, targetpos.z);

            // �����̗͂�0�ȉ��ɂȂ�����
            if (enemyHp == 0 )
            {
                // �����p�[�e�B�N��
                Instantiate(explosionPrefab, transform.position, Quaternion.identity);

                // enemy�_�E�����֐��̌Ăяo���B
                gameManager.AddCrushingCount();

                // enemy�_�E���X�R�A�֐��̌Ăяo���B
                scores.AddDownScore();

                // �����ŏ�����B
                Destroy(this.gameObject);
            }
        }

        // enemy���J�����O�ɍs������
        else if (isInsideCamera == false)
        {
            // enemy�̃I�u�W�F�N�g�������B
            Destroy(this.gameObject);
        }
        
    }

    // �����蔻��
    private void OnTriggerEnter(Collider other)
    {
        // "Player"�̃^�O��T���B
        if (other.gameObject.tag == "Player")
        {
            // player�_���[�W�֐��̌Ăяo���B
            other.GetComponent<PlayerHp>().Damage();
        }
    }


    // �J�����t���O�֐�
    private void OnBecameInvisible()
    {
        isInsideCamera = false;
    }

    // enemy�_���[�W�֐�
    public void Damage()
    {
        enemyHp--;
    }
}
