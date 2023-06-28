using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewBehaviourScript : MonoBehaviour
{
    // �����̐ݒ�
    [SerializeField] private float speed = 0.1f;
    [SerializeField] private float ratio;

    // ���R���ł܂ł̃^�C�}�[
    [SerializeField] private float time = 60;

    // ���x
    [SerializeField] private Vector3 velocity;

    // �J����������̃t���O
    private bool bull_camera = true;

    //Enemy

    void FixedUpdate()
    {
        // ���@�̍��W����
        Vector3 target_position = PlayerMove.instance.pos;

        // �x�N�g�����擾
        var diff = target_position - transform.position;

        // �x�N�g���̕����Ɍ���
        var target_rot = Quaternion.LookRotation(diff);

        // ����n���E��n�ɕϊ�
        var q = target_rot * Quaternion.Inverse(transform.rotation);

        // �߂����ɉ���ė~�����̂�
        if (q.w < 0f)
        {
            q.x = -q.x;
            q.y = -q.y;
            q.z = -q.z;
            q.w = -q.w;
        }

        // ��������������
        if (diff.magnitude > 1)
        {
            // ���W�̍X�V
            var torque = new Vector3(q.x, q.y, q.z) * ratio;

            // �g���N��������B
            GetComponent<Rigidbody>().AddTorque(torque);
        }
        velocity = transform.forward * speed;

    }

    private void Update()
    {
        // �J�������ɂ��鎞
        if(bull_camera == true)
        {
            EnemyBulletMove();
        }

        // �J�������ɂ��Ȃ���
        else if (bull_camera == false)
        {
            Destroy(this.gameObject);
        }
       
    }

    public void EnemyBulletMove()
    {

        // ���ʂɂ܂��������
        transform.position += velocity;

        // ���Ԑ����������玩�R���ł���
        time -= Time.deltaTime;

        // ��莞�Ԍo��������ł���
        if (time <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    // �J�����t���O�֐�
    public void OnBecameInvisible()
    {
        bull_camera = false;
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Player")
        {
            PlayerHp.instance.Player_Damage();
            Destroy(this.gameObject);
        }

        else if (other.gameObject.tag == "PlayerBullet")
        {
            Destroy(this.gameObject);
        }
    }
}
