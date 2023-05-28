using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PlayerManager : MonoBehaviour
{
    public static PlayerManager instance;

    public GameObject[] player;

    public Image fadeout;

    public float alpha = 0;

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
        
    }

    // Update is called once per frame
    void Update()
    {
        player = GameObject.FindGameObjectsWithTag("Player");

        if (player.Length == 0)
        {
            Fadeout_2();
        }
    }

    private void Fadeout_2()
    {
        alpha += 0.01f;

        fadeout.color = new Color(0, 0, 0, alpha);

        if (alpha >= 1.0f)
        {
            SceneManager.LoadScene("GameOverScene");
        }
    }
}
