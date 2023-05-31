using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    // Enemyの体力用変数
    public float enemyHp;

    // 狙いたい相手の変数。
    private Vector3 targetpos;

    // スコアクラスの呼び出し。
    //public Score scores;

    // アタッチするためのもの
    [SerializeField] GameObject explosionPrefab;

    // カメラのフラグ
    private bool isInsideCamera = true;

    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        enemyHp = 1;

        // 変数に格納する。
        targetpos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        // 敵がカメラ内にいる時
        if (isInsideCamera == true)
        {
            // もし体力が0以下になったら
            if (enemyHp == 0)
            {
                // 爆発パーティクル
                Instantiate(explosionPrefab, transform.position, Quaternion.identity);

                // enemyダウン数関数の呼び出し。
                GameManager.instance.AddCrushingCount();

                // 自分で消える。
                Destroy(this.gameObject);
            }
        }

        // enemyがカメラ外に行った時
        else if (isInsideCamera == false)
        {
            // enemyのオブジェクトを消す。
            Destroy(this.gameObject);
        }

    }

    // 当たり判定
    //private void OnTriggerEnter(Collider other)
    //{
    //    // "Player"のタグを探す。
    //    if (other.gameObject.tag == "Player")
    //    {
    //        // playerダメージ関数の呼び出し。
    //        other.GetComponent<PlayerHp>().Player_Damage();
    //    }
    //}


    // カメラフラグ関数
    private void OnBecameInvisible()
    {
        isInsideCamera = false;
    }

    // enemyダメージ関数
    public void Damage()
    {
        enemyHp -= 1.0f;

        if (enemyHp <= 0)
        {
            enemyHp = 0;
        }
    }
}
