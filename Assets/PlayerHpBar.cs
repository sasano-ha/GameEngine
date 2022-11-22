using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerHpBar : MonoBehaviour
{
    [SerializeField]
    Image image1;
    Image image2;

    bool mouseButton = false;

    // Start is called before the first frame update
    void Start()
    {
        image2 = GetComponent<Image>();
    }

    // Update is called once per frame
    void Update()
    {
        image2.fillAmount = 1 - PlayerHp.instance.playerHp / 100.0f;

        // Fill Amount�ɂ���ăQ�[�W�̐F��ς���
        // �͈͂� 0-1 �ŁA0 �͉����\�����ꂸ�A1 �Ŋ��S�� Image ���\������܂��B
        if (image2.fillAmount > 0.5f)
        {

            image1.color = Color.red;

        }
        else if (image2.fillAmount > 0.2f)
        {

            image1.color = new Color(1f, 0.67f, 0f);

        }
        else
        {

            image1.color = Color.green;

        }



        // �}�E�X���g���ăQ�[�W�𑝌�������
        if (Input.GetKey(KeyCode.DownArrow))
        {
            mouseButton = true;
        }
        else if (Input.GetKey(KeyCode.UpArrow))
        {
            mouseButton = false;
        }


        if (mouseButton)
        {

            image2.fillAmount += Time.deltaTime;

        }
        else if (image2.fillAmount > 0f)
        {

            image2.fillAmount -= Time.deltaTime;

        }
    }
}
