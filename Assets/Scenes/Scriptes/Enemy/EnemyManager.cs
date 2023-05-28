using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EnemyManager : MonoBehaviour
{
    private GameObject[] enemies;

    private float enemy_timer = 845;

    public bool isEnemy_Die = true;

    // Update is called once per frame
    void Update()
    {
        // 敵タグを検索
        enemies = GameObject.FindGameObjectsWithTag("Enemy");


        // 敵タグがなくなったら消す。
        if (enemies.Length == 0)
        {
            isEnemy_Die = false;
            // 急にシーン遷移しないためのタイマー
            //enemy_timer -= 1.0f;

            // 定時になったらシーンをロードする。
            //if(enemy_timer <= 0)
            //{
            //    SceneManager.LoadScene("TitleScene");
            //}
        }
    }
}
