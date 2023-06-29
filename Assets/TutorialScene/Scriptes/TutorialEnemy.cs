using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialEnemy : MonoBehaviour
{

    // �A�^�b�`���邽�߂̂���
    [SerializeField] GameObject explosionPrefab;

    // Enemy�̗̑͗p�ϐ�
    public float Tu_enemyHp;

    // �J�����̃t���O
    public bool isInsideCamera = true;

    // �G�@�֘A�̕ϐ�
    [SerializeField] private Vector3 en_pos, ap_force, es_force;

    public Enemy tutorialenemy;



    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        Tu_enemyHp = 1;

        tutorialenemy = GetComponent<Enemy>();
    }

    // Update is called once per frame
    void Update()
    {
        // �G���J�������ɂ��鎞
        if (isInsideCamera == true)
        {
            Tu_En_Die();
        }
    }

    // �J�����t���O�֐�
    public void OnBecameInvisible()
    {
        isInsideCamera = false;
    }

    public void Tu_Damage()
    {
        Tu_enemyHp -= 1.0f;

        if (Tu_enemyHp <= 0)
        {
            Tu_enemyHp = 0;
        }
    }

    // �G�@�����񂾊֐�
    public void Tu_En_Die()
    {
        // �����̗͂�0�ȉ��ɂȂ�����
        if (Tu_enemyHp == 0)
        {
            // �����p�[�e�B�N��
            Instantiate(explosionPrefab, transform.position, Quaternion.identity);

            // enemy�_�E�����֐��̌Ăяo���B
            //GameManager.instance.AddCrushingCount();

            // �����ŏ�����B
            Destroy(this.gameObject);
        }
    }
}
