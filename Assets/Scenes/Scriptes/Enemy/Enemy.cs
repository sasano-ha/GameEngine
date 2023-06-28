using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    // �G�@�̍s���J��
    public enum State {
        approach,   // �߂Â�
        offence,    // �U��
        escape,     //������
    }

    // �s���J�ڕϐ�
    State state_;

    // �A�^�b�`���邽�߂̂���
    [SerializeField] GameObject explosionPrefab;

    // Enemy�̗̑͗p�ϐ�
    public float enemyHp;

    // �J�����̃t���O
    public bool isInsideCamera = true;

    // �G�@�֘A�̕ϐ�
    [SerializeField] private Vector3 en_pos, ap_force, es_force;

    // �G�@�����������̃t���O
    public bool en_ShotFag = false;

    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        enemyHp = 1;

        // �ŏ��̍s���J��
        state_ = State.approach;
    }

    private void FixedUpdate()
    {
        switch (state_)
        {
            case State.approach:
            default:
                EnemyApproach();
                break;

            case State.offence:
                EnemyOffence();
                break;

            case State.escape:
                EnmeyEscape();
                break;
        }
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

    // �G�@�����񂾊֐�
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

    // �G�@�̋߂Â��֐�
    private void EnemyApproach()
    {
        Rigidbody rb = this.GetComponent<Rigidbody>();

        ap_force = new Vector3(0, 0, -3.0f);
        rb.AddForce(ap_force, ForceMode.Force);

        if (isInsideCamera == true)
        {
            state_ = State.offence;
        }
    }

    // �G�@�̍U���֐�
    private void EnemyOffence()
    {
        en_ShotFag = true;

        Rigidbody rb = this.GetComponent<Rigidbody>();

        ap_force = new Vector3(0, 0, -3.0f);
        rb.AddForce(ap_force, ForceMode.Force);

        en_pos = transform.position;

        var diff = PlayerMove.instance.pos - en_pos;

        if (diff.magnitude < 20)
        {
            state_ = State.escape;
        }
    }

    // �G�@�̓�����֐�
    private void EnmeyEscape()
    {
        Rigidbody rb = this.GetComponent<Rigidbody>();

        if(PlayerMove.instance.pos.x > en_pos.x)
        {
            int random = Random.Range(3, 7);
            es_force = new Vector3(-3.0f, random, -3.0f);
        }
        else if(PlayerMove.instance.pos.x < en_pos.x)
        {
            int random = Random.Range(3, 7);
            es_force = new Vector3(3.0f, random, -3.0f);
        }

        rb.AddForce(es_force, ForceMode.Force);
    }
}
