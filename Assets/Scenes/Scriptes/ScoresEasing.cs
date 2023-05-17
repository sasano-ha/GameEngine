using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoresEasing : MonoBehaviour
{
    // imageタイマーの入れ物
    float image_time;
    float image2_time;

    // textタイマーの入れ物
    float text_time;
    float text2_time;

    // imageの縦横を使うための変数
    private RectTransform image_;

    // イージングに使うタイマー変数
    float easingtime = 1.0f;

    // 始まる時間
    float start = 0;

    // 終わる時間
    float end = 500;

    // 別スクリプトから変数を使うための変数
    public GameObject camera_s;

    // テキスト用変数
    public Text text;

    // テキストのα値用の変数
    private Color a;

    private bool endflag = false;

    float totaletime = 0;

    // Start is called before the first frame update
    private void Awake()
    {
        // ここでテキストと同じα値を入れとく
        a = text.color;
    }

    void Start()
    {
        // 縦横を動かしたいので持ってくる
        image_ = GetComponent<RectTransform>();

        // テキスト描画をしない。
        text.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        // 敵がいなくなったら
        if (camera_s.GetComponent<DrawingSoure>().flag == true)
        {
            ImageEasing();
        }

        if (text.enabled == true)
        {
            TextEasing();
            totaletime++;
        }

        if (totaletime > 1000)
        {
            EndtextEasing();
        }

        if (endflag == true)
        {
            EndEsing();
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

        // maxが振れ幅でminがその振れ幅の中央値
        return max * Mathf.Sin(t * (Mathf.PI * 90 / 180) / totaltime) + min;
    }

    private void ImageEasing()
    {
        // 縦横用の変数
        float size;

        // 時間指定内だったらイージングを使ってimageの変数を変更
        if (0 < image_time && image_time < easingtime)
        {
            // イージング
            size = SineOut(image_time, easingtime, start, end);

            // イージングで使った変数を縦横に代入
            image_.sizeDelta = new Vector2(size, size);
        }

        // 先程の指定時間外になったらイージングを止めて固定値を入れる
        else if (easingtime < image_time)
        {
            // 縦横に固定値を入れる
            image_.sizeDelta = new Vector2(end, end);

            // テキストを描画させる
            text.enabled = true;
        }

        // imageのタイマーに代入
        image_time += Time.deltaTime;
    }

    private void TextEasing()
    {
        // 内容は上記と同じ
        if (0 < text_time && text_time < 10.0f)
        {
            a.a = QuintOut(text_time, 10.0f, 0, 1.0f);
            text.color = a;
        }
        else if (10.0f < text_time)
        {
            text.enabled = false;
            endflag = true;
        }

        text_time += Time.deltaTime;
    }

    private void EndtextEasing()
    {
        if (0 < text2_time && text2_time < 10.0f)
        {
            a.a = QuintOut(text2_time, 10.0f, 1.0f, 0);
            text.color = a;
        }
        else if (10.0f < text2_time)
        {
            a.a = 0;

            text.color = a;
        }

        text2_time += Time.deltaTime;
    }


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
            //text.enabled = true;
        }

        image2_time += Time.deltaTime;
    }
}
