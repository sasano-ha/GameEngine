using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UiText : MonoBehaviour
{
    // Text�p�̓��ꕨ
    public Text textUi;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //���@�̃_���[�W�֐��̌Ăяo���B
        GetComponent<PlayerHp>().Player_Damage();

        // �e�L�X�g�`��
        textUi.text = string.Format("100", PlayerHp.instance.playerMaxHp);
    }
}
