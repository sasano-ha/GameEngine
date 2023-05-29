using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Result : MonoBehaviour
{

    // カメラをアタッチする為の変数
    [SerializeField] private GameObject gameover;

    // シーンインのimageのタイマー
    float image_time;

    // シーンアウトのimageのタイマー
    float image2_time;

    // シーンインのtextのタイマー
    float text_time;

    // シーンアウトのtextのタイマー
    float text2_time;

    // imageの座標の変数
    private RectTransform image_;

    // イージング時間
    float easingtime = 1.0f;

    // 開始値
    float start = 0;

    // 終了値
    float end = 500;

    // scoretextをアタッチするための変数
    [SerializeField] private Text scoretext;

    // enemytextをアタッチするための変数
    [SerializeField] private Text enemytext;

    // α値
    private Color socre_alpha;

    private Color enemy_alpha;

    // textのイージング終了フラグ
    private bool endflag = false;

    // 全体の時間
    public float totaletime = 0;

    // enemytext描画の為のフラグ
    private bool enemyFlag = false;

    private int scenech = 250;

    public bool scenefade = false;

    //public titlesene fade;

    //[SerializeField] private Image fadeout;

    public float alpha = 0;

    // Start is called before the first frame update
    private void Awake()
    {
        // 現在の色を代入
        socre_alpha = scoretext.color;
        enemy_alpha = enemytext.color;
    }

    void Start()
    {
        // FPSを60に固定
        Application.targetFrameRate = 60;

        // imageの縦横の取得
        image_ = GetComponent<RectTransform>();

        // scoretextは描画しない
        scoretext.enabled = false;

        // enemytextは描画しない
        enemytext.enabled = false;
    }


    void Update()
    {
        // カメラのフラグがたった時
        if (gameover.GetComponent<TextFade>().textFlag == true)
        {
            // リザルト（枠）の描画
            ImageEasing();
        }

        // textが描画されたら
        if (scoretext.enabled == true)
        {
            // textの描画
            TextEasing();

            // スコアを反映
            Scoure();

            Enemy();
        }
    }


    // イージング関連の関数
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

        // maxが振れ幅でminがその振れ幅の中央値
        return max * Mathf.Sin(t * (Mathf.PI * 90 / 180) / totaltime) + min;
    }


    // テキスト描画の関数
    private void ImageEasing()
    {
        // ローカル変数
        float size;

        // 規定時間内の時
        if (0 < image_time && image_time < easingtime)
        {
            // イージングをさせる
            size = SineOut(image_time, easingtime, start, end);

            // 上記の値をimageの縦横に代入
            image_.sizeDelta = new Vector2(size, size);
        }
        else if (easingtime < image_time)
        {
            // imageの値を固定値に
            image_.sizeDelta = new Vector2(end, end);

            // テキストの描画
            scoretext.enabled = true;
            enemytext.enabled = true;
        }

        // imageのタイマーを進める
        image_time += Time.deltaTime;
    }

    // textの描画関数
    private void TextEasing()
    {
        // 規定時間内の時
        if (0 < text_time && text_time < 10.0f)
        {
            // textのα値をイージングさせる
            socre_alpha.a = QuintOut(text_time, 10.0f, 0, 1.0f);
            enemy_alpha.a = QuintOut(text_time, 10.0f, 0, 1.0f);

            // 上記の値を代入
            scoretext.color = socre_alpha;
            enemytext.color = enemy_alpha;
        }
        else if (10.0f < text_time)
        {
            // textを描画させない
            //scoretext.enabled = false;
            //enemytext.enabled = false;

            // フラグを立てる
            endflag = true;
        }

        // テキストタイマーを進める
        text_time += Time.deltaTime;
    }


    // text描画終了関数
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


    // imageの描画終了関数
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


        scoretext.text = "スコア : " + resultScor;
    }

    private void Enemy()
    {
        int enemyscore = PlayerPrefs.GetInt("Enemy");

        enemytext.text = "撃破 : " + enemyscore;
    }
}
