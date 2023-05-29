using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TextFade : MonoBehaviour
{
    [SerializeField] RectTransform text;

    // シーンインのimageのタイマー
    float text_time;

    // イージング時間
    float easingtime = 1.0f;

    // 開始値
    float start = 0;

    // 終了値
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
            // イージングをさせる
            sizeX = SineOut(text_time, easingtime, start, end);
            sizeY = SineOut(text_time, easingtime, start, end);

            // 上記の値をimageの縦横に代入
            text.localScale = new Vector2(sizeX, sizeY);
        }
        else if (easingtime < text_time)
        {
            // imageの値を固定値に
            text.localScale = new Vector2(end, end);
            textFlag = true;
        }

        // imageのタイマーを進める
        text_time += Time.deltaTime;
    }


    public static float SineOut(float t, float totaltime, float min, float max)
    {
        max -= min;

        // maxが振れ幅でminがその振れ幅の中央値
        return max * Mathf.Sin(t * (Mathf.PI * 90 / 180) / totaltime) + min;
    }
}
