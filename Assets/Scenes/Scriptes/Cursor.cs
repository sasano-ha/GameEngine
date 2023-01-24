using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cursor : MonoBehaviour
{
    public static Cursor instance;

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
        // �v�Z����3D�I�u�W�F�N�g�̂�����̂����
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
