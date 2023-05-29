using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Result : MonoBehaviour
{

    // �J�������A�^�b�`����ׂ̕ϐ�
    [SerializeField] private GameObject gameover;

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

    // scoretext���A�^�b�`���邽�߂̕ϐ�
    [SerializeField] private Text scoretext;

    // enemytext���A�^�b�`���邽�߂̕ϐ�
    [SerializeField] private Text enemytext;

    // ���l
    private Color socre_alpha;

    private Color enemy_alpha;

    // text�̃C�[�W���O�I���t���O
    private bool endflag = false;

    // �S�̂̎���
    public float totaletime = 0;

    // enemytext�`��ׂ̈̃t���O
    private bool enemyFlag = false;

    private int scenech = 250;

    public bool scenefade = false;

    //public titlesene fade;

    //[SerializeField] private Image fadeout;

    public float alpha = 0;

    // Start is called before the first frame update
    private void Awake()
    {
        // ���݂̐F����
        socre_alpha = scoretext.color;
        enemy_alpha = enemytext.color;
    }

    void Start()
    {
        // FPS��60�ɌŒ�
        Application.targetFrameRate = 60;

        // image�̏c���̎擾
        image_ = GetComponent<RectTransform>();

        // scoretext�͕`�悵�Ȃ�
        scoretext.enabled = false;

        // enemytext�͕`�悵�Ȃ�
        enemytext.enabled = false;
    }


    void Update()
    {
        // �J�����̃t���O����������
        if (gameover.GetComponent<TextFade>().textFlag == true)
        {
            // ���U���g�i�g�j�̕`��
            ImageEasing();
        }

        // text���`�悳�ꂽ��
        if (scoretext.enabled == true)
        {
            // text�̕`��
            TextEasing();

            // �X�R�A�𔽉f
            Scoure();

            Enemy();
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
            scoretext.enabled = true;
            enemytext.enabled = true;
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
            socre_alpha.a = QuintOut(text_time, 10.0f, 0, 1.0f);
            enemy_alpha.a = QuintOut(text_time, 10.0f, 0, 1.0f);

            // ��L�̒l����
            scoretext.color = socre_alpha;
            enemytext.color = enemy_alpha;
        }
        else if (10.0f < text_time)
        {
            // text��`�悳���Ȃ�
            //scoretext.enabled = false;
            //enemytext.enabled = false;

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
            socre_alpha.a = QuintOut(text2_time, 10.0f, 1.0f, 0);
            enemy_alpha.a = QuintOut(text2_time, 10.0f, 1.0f, 0);
            scoretext.color = socre_alpha;
            enemytext.color = socre_alpha;
        }
        else if (10.0f < text2_time)
        {
            socre_alpha.a = 0;
            enemy_alpha.a = 0;
            scoretext.color = socre_alpha;
            enemytext.color = socre_alpha;

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

    private void Scoure()
    {

        int resultScor = PlayerPrefs.GetInt("Score");


        scoretext.text = "�X�R�A : " + resultScor;
    }

    private void Enemy()
    {
        int enemyscore = PlayerPrefs.GetInt("Enemy");

        enemytext.text = "���j : " + enemyscore;
    }
}
