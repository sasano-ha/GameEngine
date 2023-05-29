using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TextFade : MonoBehaviour
{
    [SerializeField] RectTransform text;

    // �V�[���C����image�̃^�C�}�[
    float text_time;

    // �C�[�W���O����
    float easingtime = 1.0f;

    // �J�n�l
    float start = 0;

    // �I���l
    float end = 1;

    public bool textFlag = false;

    // Update is called once per frame
    void Update()
    {
        Go_TextEasing();
    }

    private void Go_TextEasing()
    {
        float sizeX, sizeY;

        if (0 < text_time && text_time < easingtime)
        {
            // �C�[�W���O��������
            sizeX = SineOut(text_time, easingtime, start, end);
            sizeY = SineOut(text_time, easingtime, start, end);

            // ��L�̒l��image�̏c���ɑ��
            text.localScale = new Vector2(sizeX, sizeY);
        }
        else if (easingtime < text_time)
        {
            // image�̒l���Œ�l��
            text.localScale = new Vector2(end, end);
            textFlag = true;
        }

        // image�̃^�C�}�[��i�߂�
        text_time += Time.deltaTime;
    }


    public static float SineOut(float t, float totaltime, float min, float max)
    {
        max -= min;

        // max���U�ꕝ��min�����̐U�ꕝ�̒����l
        return max * Mathf.Sin(t * (Mathf.PI * 90 / 180) / totaltime) + min;
    }
}
