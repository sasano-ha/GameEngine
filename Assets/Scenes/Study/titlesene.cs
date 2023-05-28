using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class titlesene : MonoBehaviour
{

    [SerializeField] private Image PanelImage;
    [SerializeField] private float speed;

    private Color PanelColor;

    public sample pl;

    private void Awake()
    {
        PanelColor = PanelImage.color;


    }



    // Update is called once per frame
    void Update()
    {

    }

    //public void Fadeout_()
    //{
    //    StartCoroutine(SceneFadeout_());
    //}

    //private IEnumerator SceneFadeout_()
    //{
    //    while (pl.scenefade == true)
    //    {
    //        PanelColor.a += 0.1f;
    //        PanelImage.color = PanelColor;

    //        if (PanelColor.a >= 1.0f)
    //        {
    //            pl.scenefade = false;
    //        }
    //        yield return new WaitForSeconds(speed);
    //    }
    //    //SceneManager.LoadScene("TitleScene");
    //}
}
