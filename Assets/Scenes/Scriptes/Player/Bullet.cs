using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{

    private float velocity = 0.05f;
    private Rigidbody rb;
    // ���R���ł܂ł̃^�C�}�[
    public float time = 3;


    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        BulletMove();
    }

    public void BulletMove()
    {
        // �e�̃��[���h���W���擾
        Vector3 pos = transform.position;

        // ���ʂɂ܂��������
        pos.z += 1.0f;

        // �e�̈ړ�
        transform.position = new Vector3(pos.x, pos.y, pos.z);

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
        Destroy(this.gameObject);
    }
}
