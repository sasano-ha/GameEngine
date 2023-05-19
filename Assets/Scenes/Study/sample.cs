using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class sample : MonoBehaviour
{
    // �J�������A�^�b�`����ׂ̕ϐ�
    [SerializeField] private GameObject MainCamera;

    // �V�[���C����image�̃^�C�}�[
    float image_time;

    // �V�[���A�E�g��image�̃^�C�}�[
    float image2_time;

    // �V�[���C����text�̃^�C�}�[
    float text_time;

    // �V�[���A�E�g��text�̃^�C�}�[
    float text2_time;

    // image�̍��W�̕ϐ�
    private RectTransform image_;

    // �C�[�W���O����
    float easingtime = 1.0f;

    // �J�n�l
    float start = 0;

    // �I���l
    float end = 500;

    // text���A�^�b�`���邽�߂̕ϐ�
    [SerializeField] private Text text;

    // ���l
    private Color alpha;

    // text�̃C�[�W���O�I���t���O
    private bool endflag = false;

    // �S�̂̎���
    public float totaletime = 0;

    // Start is called before the first frame update
    private void Awake()
    {
        // ���݂̐F����
        alpha = text.color;
    }

    void Start()
    {
        // FPS��60�ɌŒ�
        Application.targetFrameRate = 60;

        // image�̏c���̎擾
        image_ = GetComponent<RectTransform>();

        // text�͕`�悵�Ȃ�
        text.enabled = false;
    }


    void Update()
    {
        // �J�����̃t���O����������
        if (MainCamera.GetComponent<camera>().flag == true)
        {
            // ���U���g�i�g�j�̕`��
            ImageEasing();
        }

        // text���`�悳�ꂽ��
        if (text.enabled == true)
        {
            // text�̕`��
            TextEasing();

            // �X�R�A�𔽉f
            Scoure();

            // �S�̂̎��Ԃ�i�߂�
            totaletime += 1.0f;

             // �K�莞�ԂɂȂ�����
            if (totaletime > 300)
            {
                // �e�L�X�g�̕`��I��
                EndtextEasing();
            }
        }

        // �t���O����������
        if (endflag == true)
        {
            // ���U���g�i�g�j�̕`��I��
            EndEsing();
        }
    }


    // �C�[�W���O�֘A�̊֐�
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


    // �e�L�X�g�`��̊֐�
    private void ImageEasing()
    {
        // ���[�J���ϐ�
        float size;

        // �K�莞�ԓ��̎�
        if (0 < image_time && image_time < easingtime)
        {
            // �C�[�W���O��������
            size = SineOut(image_time, easingtime, start, end);

            // ��L�̒l��image�̏c���ɑ��
            image_.sizeDelta = new Vector2(size, size);
        }
        else if (easingtime < image_time)
        {
            // image�̒l���Œ�l��
            image_.sizeDelta = new Vector2(end, end);

            // �e�L�X�g�̕`��
            text.enabled = true;
        }

        // image�̃^�C�}�[��i�߂�
        image_time += Time.deltaTime;
    }

    // text�̕`��֐�
    private void TextEasing()
    {
        // �K�莞�ԓ��̎�
        if (0 < text_time && text_time < 10.0f)
        {
            // text�̃��l���C�[�W���O������
            alpha.a = QuintOut(text_time, 10.0f, 0, 1.0f);

            // ��L�̒l����
            text.color = alpha;
        }
        else if (10.0f < text_time)
        {
            // text��`�悳���Ȃ�
            text.enabled = false;

            // �t���O�𗧂Ă�
            endflag = true;
        }

        // �e�L�X�g�^�C�}�[��i�߂�
        text_time += Time.deltaTime;
    }


    // text�`��I���֐�
    private void EndtextEasing()
    {
        if (0 < text2_time && text2_time < 10.0f)
        {
            alpha.a = QuintOut(text2_time, 10.0f, 1.0f, 0);
            text.color = alpha;
        }
        else if (10.0f < text2_time)
        {
            alpha.a = 0;
            
            text.color = alpha;
        }

        text2_time += Time.deltaTime;
    }


    // image�̕`��I���֐�
    private void EndEsing()
    {
        float size_2;

        if (0 < image2_time && image2_time < easingtime)
        {
            size_2 = SineOut(image2_time, easingtime, end, start);
            image_.sizeDelta = new Vector2(size_2, size_2);
        }
        else if (easingtime < image2_time)
        {
            image_.sizeDelta = new Vector2(start, start);
        }

        image2_time += Time.deltaTime;
    }

    public void Scoure()
    {
        text.text = "�X�R�A : " + GameManager.instance.totalScore;
    }
}
