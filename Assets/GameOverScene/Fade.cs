using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Fade : MonoBehaviour
{

    [SerializeField] private Image PanelImage;
    [SerializeField] private float speed;

    private bool isSceneChage;
    private Color PanelColor;

    private void Awake()
    {
        isSceneChage = false;
        PanelColor = PanelImage.color;
    }

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(SceneFadein());
    }

    // Update is called once per frame
    void Update()
    {
        
    }



    private IEnumerator SceneFadein()
    {
        while (!isSceneChage)
        {
            PanelColor.a -= 0.1f;
            PanelImage.color = PanelColor;

            if (PanelColor.a <= 0)
            {
                isSceneChage = true;
            }
            yield return new WaitForSeconds(speed);
        }
    }
}
