using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBullet : MonoBehaviour
{
    // �e�̃X�s�[�h
    public float speed = 1;

    // ���R���ł܂ł̃^�C�}�[
    public float time = 2;

    // �i�s����
    protected Vector3 forward = new Vector3(1, 1, 1);

    // �ł��o�����̊p�x
    protected Quaternion forwardAxis = Quaternion.identity;

    // Rigidbody�p�ϐ�
    protected Rigidbody rb;

    // Enemy�p�ϐ�
    protected GameObject enemy;

    public float ratio;


    // Start is called before the first frame update
    void Start()
    {
        // Rigidbody�ϐ���������
        rb = this.GetComponent<Rigidbody>();

        // �������ɐi�s���������߂�
        if(enemy != null)
        {
            forward = enemy.transform.forward;
        }
    }

    // Update is called once per frame
    void Update()
    {
        //homing();

        // �ړ��ʂ�i�s�����ɃX�s�[�h������������
        rb.velocity = forwardAxis * forward * speed;

        // ���Ԑ����������玩�R���ł���
        time -= Time.deltaTime;

        if(time <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    // �e��ł��o�����L�����N�^�[�̏���n���֐�
    public void SetCharacterObject(GameObject character)
    {
        // �e��ł��o�����L�����N�^�[�̏����󂯂�
        this.enemy = character;
    }

    // �ł��o�������������p�x�����肷�邽�߂̊֐�
    public void SetForwardAxis(Quaternion axis)
    {
        // �ݒ肳�ꂽ�p�x���󂯎��
        this.forwardAxis = axis;
    }

    // �����蔻��i�G�e�����@�ɓ����������j
    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Player")
        {
            other.GetComponent<PlayerHp>().Player_Damage();
            Destroy(this.gameObject);
        }

        else if(other.gameObject.tag == "PlayerBullet")
        {
            Destroy(this.gameObject);
        }
        
    }

    //private void homing()
    //{
    //    var diff = PlayerMove.instance.pos - transform.position;
    //    var target_rot = Quaternion.LookRotation(diff);
    //    var q = target_rot * Quaternion.Inverse(transform.rotation);
    //    if (q.w < 0f)
    //    {
    //        q.x = -q.x;
    //        q.y = -q.y;
    //        q.z = -q.z;
    //        q.w = -q.w;
    //    }
    //    var torque = new Vector3(q.x, q.y, q.z) * ratio;
    //    GetComponent<Rigidbody>().AddTorque(torque);
    //}
}
