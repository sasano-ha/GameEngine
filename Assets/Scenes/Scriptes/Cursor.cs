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

        // ���[���h���W�̏Ə��ɂȂ�B
        transform.position = mousePos;
    }

    private void CreateShot(float axis)
    {
        // �x�N�g�����擾
        //var dirction = transform.position - P
    }
}
