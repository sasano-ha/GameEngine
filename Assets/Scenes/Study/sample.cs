using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class sample : MonoBehaviour
{
    private camera camera_;
    float image_time;
    float text_time;
    private RectTransform image_;

    float easingtime = 1.0f;
    float start = 0;
    float end = 500;

    public GameObject camera_s;

    public Text text;

    private Color a;

    // Start is called before the first frame update
    private void Awake()
    {
        a = text.color;
    }

    void Start()
    {
        image_ = GetComponent<RectTransform>();
        text.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        float size;

        if (camera_s.GetComponent<camera>().flag == true)
        {
            if (0 < image_time && image_time < easingtime)
            {
                size = SineOut(image_time, easingtime, start, end);
                image_.sizeDelta = new Vector2(size, size);
            }
            else if (easingtime < image_time)
            {
                image_.sizeDelta = new Vector2(end, end);
                text.enabled = true;
            }
            image_time += Time.deltaTime;
        }

        if(text.enabled == true)
        {
            if(0 < text_time && text_time < 10.0f)
            {
                a.a = QuintOut(text_time, 10.0f, 0, 1.0f);
                text.color = a;


            }
            else if(10.0f < text_time)
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

        // max‚ªU‚ê•‚Åmin‚ª‚»‚ÌU‚ê•‚Ì’†‰›’l
        return max * Mathf.Sin(t * (Mathf.PI * 90 / 180) / totaltime) + min;
    }
}
