using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

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
        StartCoroutine(SceneFadein_());
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Fadeout_()
    {
        StartCoroutine(SceneFadeout_());
    }

    private IEnumerator SceneFadeout_()
    {
        while (isSceneChage == true)
        {
            PanelColor.a += 0.1f;
            PanelImage.color = PanelColor;

            if (PanelColor.a >= 1.0f)
            {
                //isSceneChage = true;
                SceneManager.LoadScene("TitleScene");
            }
            yield return new WaitForSeconds(speed);
            
        }
        
    }

    private IEnumerator SceneFadein_()
    {
        while (!isSceneChage)
        {
            PanelColor.a -= 0.1f;
            PanelImage.color = PanelColor;

            if (PanelColor.a <= 0)
            {
                PanelColor.a = 0;
                isSceneChage = true;
            }
            yield return new WaitForSeconds(speed);
        }
    }
}
