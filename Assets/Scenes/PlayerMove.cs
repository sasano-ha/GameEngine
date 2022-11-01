using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    // �J�������猩����ʍ����̍��W������ϐ�
    Vector3 LeftBottom;

    // �J�������猩����ʉE���̍��W������ϐ�
    Vector3 RightTop;

    private Vector3 mouse;
    private Vector3 target;


    // Start is called before the first frame update
    void Start()
    {
        // �J�����ƃv���C���[�̋����𑪂�i�\����ʂ̎l����ݒ肷�邽�߂ɕK�v�j
        var distance = Vector3.Distance(Camera.main.transform.position, transform.position);

        // �X�N���[����ʍ����̈ʒu��ݒ肷��
        LeftBottom = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, distance));

        // �X�N���[����ʍ����̈ʒu��ݒ肷��
        RightTop = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, distance));
    }

    // Update is called once per frame
    void Update()
    {
        //// �v���C���[�̃��[���h���W���擾
        //Vector3 pos = transform.position;

        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.D))
        //{
        //    pos.x += 0.01f;
        //}
        //// �����L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.A))
        //{
        //    pos.x -= 0.01f;
        //}
        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.W))
        //{
        //    pos.y += 0.01f;
        //}
        //// �E���L�[�����͂��ꂽ�玞
        //if (Input.GetKey(KeyCode.S))
        //{
        //    pos.y -= 0.01f;
        //}

        mouse = Input.mousePosition;
        target = Camera.main.ScreenToWorldPoint(new Vector3(mouse.x, mouse.y, 5));
        this.transform.position = target;

        //transform.position = new Vector3(Mathf.Clamp(mouse.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
        //   Mathf.Clamp(mouse.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y), -4);
    }
}
