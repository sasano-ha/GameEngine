using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoresEasing: MonoBehaviour
{
    // image�^�C�}�[�̓��ꕨ
    float image_time;

    // text�^�C�}�[�̓��ꕨ
    float text_time;

    // image�̏c�����g�����߂̕ϐ�
    private RectTransform image_;

    // �C�[�W���O�Ɏg���^�C�}�[�ϐ�
    float easingtime = 1.0f;

    // �n�܂鎞��
    float start = 0;

    // �I��鎞��
    float end = 500;

    // �ʃX�N���v�g����ϐ����g�����߂̕ϐ�
    public GameObject camera_s;

    // �e�L�X�g�p�ϐ�
    public Text text;

    // �e�L�X�g�̃��l�p�̕ϐ�
    private Color a;

    // Start is called before the first frame update
    private void Awake()
    {
        // �����Ńe�L�X�g�Ɠ������l�����Ƃ�
        a = text.color;
    }

    void Start()
    {
        // �c���𓮂��������̂Ŏ����Ă���
        image_ = GetComponent<RectTransform>();

        // �e�L�X�g�`������Ȃ��B
        text.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        // �c���p�̕ϐ�
        float size;

        // �G�����Ȃ��Ȃ�����
        if (camera_s.GetComponent<DrawingSoure>().flag == true)
        {
            // ���Ԏw�����������C�[�W���O���g����image�̕ϐ���ύX
            if (0 < image_time && image_time < easingtime)
            {
                // �C�[�W���O
                size = SineOut(image_time, easingtime, start, end);

                // �C�[�W���O�Ŏg�����ϐ����c���ɑ��
                image_.sizeDelta = new Vector2(size, size);
            }
            
            // ����̎w�莞�ԊO�ɂȂ�����C�[�W���O���~�߂ČŒ�l������
            else if (easingtime < image_time)
            {
                // �c���ɌŒ�l������
                image_.sizeDelta = new Vector2(end, end);

                // �e�L�X�g��`�悳����
                text.enabled = true;
            }

            // image�̃^�C�}�[�ɑ��
            image_time += Time.deltaTime;
        }

        // �e�L�X�g���`�悳�ꂽ��
        if (text.enabled == true)
        {
            // ���e�͏�L�Ɠ���
            if (0 < text_time && text_time < 10.0f)
            {
                a.a = QuintOut(text_time, 10.0f, 0, 1.0f);
                text.color = a;


            }
            else if (10.0f < text_time)
            {
                a.a = 1.0f;
                text.color = a;
            }

            text_time += Time.deltaTime;
        }
    }

    public static float ExpOut(float t, float totaltime, float min, float max)
    {
        max -= min;
        return t == totaltime ? max + min : max * (-Mathf.Pow(2, -10 * t / totaltime) + 1) + min;
    }
    public static float QuintOut(float t, float totaltime, float min, float max)
    {
        max -= min;
        t = t / totaltime - 1;
        return max * (t * t * t * t * t + 1) + min;
    }

    public static float SineOut(float t, float totaltime, float min, float max)
    {
        max -= min;

        // max���U�ꕝ��min�����̐U�ꕝ�̒����l
        return max * Mathf.Sin(t * (Mathf.PI * 90 / 180) / totaltime) + min;
    }
}
