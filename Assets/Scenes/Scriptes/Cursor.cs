using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cursor : MonoBehaviour
{
    // ���W�p�̕ϐ�
    private Vector3 mousePos, target;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //�}�E�X���W�̎擾
        mousePos = Input.mousePosition;

        // �X�N���[�����W�����[���h���W�ɕύX
        target = Camera.main.ScreenToWorldPoint(new Vector3(mousePos.x, mousePos.y, 7));

        transform.position = target;

        transform.position = new Vector3(mousePos.x, mousePos.y, 7);
    }
}
