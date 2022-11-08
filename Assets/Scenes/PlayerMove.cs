using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    // �}�E�X
    private Vector3 mouse;

    // �^�[�Q�b�g
    private Vector3 target;

    // player��HP
    private int playerHp;


    // Start is called before the first frame update
    void Start()
    {
        // �}�E�X�J�[�\���̈ړ��͈͂̐���
        Cursor.lockState = CursorLockMode.Confined;

        // �������ɑ̗͂��w�肵�Ă���
        playerHp = 3;
    }

    // Update is called once per frame
    void Update()
    {
        // �}�E�X�J�[�\����\�������Ȃ�
        Cursor.visible = false;

        //// �v���C���[�̃��[���h���W���擾
        //Vector3 pos = transform.position;

        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.D))
        //{
        //    pos.x += 1.0f;
        //}
        //// �����L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.A))
        //{
        //    pos.x -= 1.0f;
        //}
        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.W))
        //{
        //    pos.y += 1.0f;
        //}
        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.S))
        //{
        //    pos.y -= 1.0f;
        //}

        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.UpArrow))
        //{
        //    pos.z += 1.0f;
        //}

        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.DownArrow))
        //{
        //    pos.z -= 1.0f;
        //}

        //transform.position = new Vector3(pos.x, pos.y, pos.z);

        //transform.position = new Vector3(Mathf.Clamp(mouse.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
        //   Mathf.Clamp(mouse.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y), -4);

        mouse = Input.mousePosition;
        target = Camera.main.ScreenToWorldPoint(new Vector3(mouse.x, mouse.y, 5));
        transform.position = target;

        if(playerHp <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    public void Damage()
    {
        playerHp--;
    }
}
