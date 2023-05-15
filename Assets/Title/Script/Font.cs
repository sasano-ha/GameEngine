using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class Font : MonoBehaviour
{

    [SerializeField] private TextMeshProUGUI font_text;

    private Color text;

    private bool isfont;

    [SerializeField] private float frame;

    private void Awake()
    {
        isfont = false;
        text = font_text.color;
    }

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(fontFadeIn());
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    private IEnumerator fontFadeIn()
    {
        while (!isfont)
        {
            for (float i = 1.0f; i >= 0f; i -= 0.1f)
            {
                text.a = i;
                font_text.color = text;
                yield return new WaitForSeconds(frame);
            }

            for (float k = 0; k <= 1.0f; k += 0.1f)
            {
                text.a = k;
                font_text.color = text;
                yield return new WaitForSeconds(frame);
            }
        }
    }
}