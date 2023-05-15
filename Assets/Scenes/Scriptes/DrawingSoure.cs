using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DrawingSoure : MonoBehaviour
{
    // 描画用のタイマー
    private float timer = 0;

    // image用の変数
    [SerializeField] Image image_;

    // 描画開始のフラグ
    public bool flag = false;

    // 別スクリプトから変数を使うための変数
    [SerializeField] private GameObject enemy;

    private void Awake()
    {
        // imageを描画させない
        image_.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        // 敵がいなくなったら
        if (enemy.GetComponent<EnemyManager>().isEnemy_Die == false)
        {
            // タイマーを進めて
            timer++;

            // 一定時間が経ったら
            if (timer >= 100)
            {
                //フラグを経てて
                flag = true;
            }

            if (flag == true)
            {
                // imageを描画させる
                image_.enabled = true;
            }
        }

    }
}
