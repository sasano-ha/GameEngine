using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class SceneFade : MonoBehaviour
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

    public void Fadeout()
    {
        StartCoroutine(SceneFadeout());
    }

    public void Fadein()
    {
        StartCoroutine(SceneFadein());
    }


    private IEnumerator SceneFadeout()
    {
        while (!isSceneChage)
        {
            PanelColor.a += 0.1f;
            PanelImage.color = PanelColor;

            if(PanelColor.a >= 1)
            {
                isSceneChage = true;
            }
            yield return new WaitForSeconds(speed);
        }
        SceneManager.LoadScene("GameScene");
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
