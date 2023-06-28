using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialBullet : MonoBehaviour
{
    // �����̐ݒ�
    private float speed = 3.0f;

    private Rigidbody rb;

    // ���R���ł܂ł̃^�C�}�[
    public float time = 3;

    // ���x
    private Vector3 velocity;

    // Update is called once per frame
    void Update()
    {
        BulletMove();
    }

    public void BulletMove()
    {

        // ���ʂɂ܂��������
        transform.position += velocity;

        // ���Ԑ����������玩�R���ł���
        time -= Time.deltaTime;

        // ��苗���i�񂾂���ł���
        if (time <= 0)
        {
            Destroy(this.gameObject);
        }
    }


    // �����蔻��
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Enemy")
        {
            other.GetComponent<Enemy>().Damage();
        }
    }

    public void SetVelocity(Vector3 target_)
    {
        // �e�̃��[���h���W���擾
        Vector3 pos = transform.position;

        // �x�N�g�����擾
        var direction = target_ - pos;

        // ���K�������x�N�g���ɑ������|���đ��x�ɂ���B
        velocity = direction.normalized * speed;
    }
}
