using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FlushController : MonoBehaviour
{
    public static FlushController instance;

    public Image image;

    public void Awake()
    {
        if (instance == null)
        {
            // インスタンスの設定
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        image = GetComponent<Image>();
        image.color = Color.clear;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        this.image.color = Color.Lerp(this.image.color, Color.clear, Time.deltaTime);
    }

    public void Damage()
    {
        this.image.color = new Color(0.5f, 0f, 0f, 0.5f);
    }
}
