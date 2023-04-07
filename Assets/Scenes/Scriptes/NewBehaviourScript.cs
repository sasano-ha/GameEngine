using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewBehaviourScript : MonoBehaviour
{
    // �����̐ݒ�
    [SerializeField] private float speed = 0.1f;
    [SerializeField] private float ratio;

    // ���R���ł܂ł̃^�C�}�[
    [SerializeField] private float time = 1000;

    // ���x
    [SerializeField] private Vector3 velocity;

    // Start is called before the first frame update
    void Start()
    {

    }

    void FixedUpdate()
    {
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

        // ���W�̍X�V
        var torque = new Vector3(q.x, q.y, q.z) * ratio;

        // �g���N��������B
        GetComponent<Rigidbody>().AddTorque(torque);

        velocity = transform.forward * speed;
    }

    private void Update()
    {
        EnemyBulletMove();
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
}
