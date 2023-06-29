using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TutorialFade : MonoBehaviour
{
    public float alpha = 0;

    [SerializeField] private Image fadeout;

    [SerializeField] private GameObject enemy;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        TutorialEnemyManager enemyes;
        GameObject Tu_enemy = GameObject.Find("EnemyManager");
        enemyes = Tu_enemy.GetComponent<TutorialEnemyManager>();

        if (enemyes.isEnemy_Die == false)
        {
            Tu_Fadeout();
        }
    }

    private void Tu_Fadeout()
    {
        alpha += 0.01f;

        fadeout.color = new Color(0, 0, 0, alpha);

        if (alpha >= 1.0f)
        {
            SceneManager.LoadScene("ExecutableScene");
        }
    }
}
