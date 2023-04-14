using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Font : MonoBehaviour
{

    [SerializeField] private Text font_text;

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
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    private IEnumerator fontFadeIn()
    {
        while (!isfont)
        {
            text.a -= 0.1f;
            font_text.color = text;

            if(text.a <= 0f)
            {
                isfont = true;
            }
            yield return new WaitForSeconds(frame);
        }
    }
}
