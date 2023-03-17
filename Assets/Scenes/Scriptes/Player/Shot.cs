using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shot : MonoBehaviour
{
    // �Q�[���I�u�W�F�N�g���C���X�y�N�^�[����Q�Ƃ��邽�߂̕ϐ�
    public GameObject bullet;

    // �������ׂ̈̃t���O
    private bool mouseflag;

    // �Ԋu�̃^�C�}�[
    public float timer;

    // Start is called before the first frame update
    void Start()
    {
        // �t���O��ݒ�
        mouseflag = false;

        // �^�C�}�[��ݒ�
        timer = 15.0f;
    }

    // Update is called once per frame
    void Update()
    {
        // ���N���b�N���������u��
        if (Input.GetMouseButtonDown(0))
        {
            // �t���O�𗧂Ă�
            mouseflag = true;
        }

        // ���N���b�N�𗣂����u��
        if (Input.GetMouseButtonUp(0))
        {
            // �t���O���~�낷
            mouseflag = false;
        }

        // �t���O�������Ă�����
        if(mouseflag == true)
        {
            // �^�C�}�[��i�߂�
            timer--;

            if(timer <= 0)
            {
                // �e�𐶐�����
                GameObject bulletobject = Instantiate(bullet, transform.position, Quaternion.identity);

                // �����e�������Ő���
                Bullet bulletclone = bulletobject.GetComponent<Bullet>();

                // �����ő��x�����
                bulletclone.SetVelocity(Aim.instance.target);

                // �^�C�}�[���ɖ߂�
                timer = 15.0f;
            }
        }
    }
}
