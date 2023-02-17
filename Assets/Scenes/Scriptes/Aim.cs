using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Aim : MonoBehaviour
{
    public static Aim instance;

    public Vector3 target;

    public void Awake()
    {
        if (instance == null)
        {
            // �C���X�^���X�̐ݒ�
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        // �J�[�\�����\���ɂ���B
        Cursor.visible = false;

        // �J�[�\���ړ��̐����i��ʓ��j
        Cursor.lockState = CursorLockMode.Confined;
    }

    // Update is ca��lled once per frame
    void Update()
    {
        // �}�E�X���W�̎擾�i�X�N���[�����W�j
        transform.position = Input.mousePosition;

        // �擾�����X�N���[�����W�����[���h���W�ɕϊ�
        target = Camera.main.ScreenToWorldPoint(new Vector3(transform.position.x, transform.position.y, 40));
    }
}
