using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cursor : MonoBehaviour
{
    // ���W�p�̕ϐ�
    private Vector2 mousePos, target;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // �}�E�X���W�̎擾
        mousePos = Input.mousePosition;
        // �}�E�X�̍��W��������
        transform.position = mousePos;
    }
}
