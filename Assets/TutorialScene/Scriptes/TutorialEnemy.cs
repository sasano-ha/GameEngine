using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialEnemy : MonoBehaviour
{

    // アタッチするためのもの
    [SerializeField] GameObject explosionPrefab;

    // Enemyの体力用変数
    public float Tu_enemyHp;

    // カメラのフラグ
    public bool isInsideCamera = true;

    // 敵機関連の変数
    [SerializeField] private Vector3 en_pos, ap_force, es_force;

    public Enemy tutorialenemy;



    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        Tu_enemyHp = 1;

        tutorialenemy = GetComponent<Enemy>();
    }

    // Update is called once per frame
    void Update()
    {
        // 敵がカメラ内にいる時
        if (isInsideCamera == true)
        {
            Tu_En_Die();
        }
    }

    // カメラフラグ関数
    public void OnBecameInvisible()
    {
        isInsideCamera = false;
    }

    public void Tu_Damage()
    {
        Tu_enemyHp -= 1.0f;

        if (Tu_enemyHp <= 0)
        {
            Tu_enemyHp = 0;
        }
    }

    // 敵機が死んだ関数
    public void Tu_En_Die()
    {
        // もし体力が0以下になったら
        if (Tu_enemyHp == 0)
        {
            // 爆発パーティクル
            Instantiate(explosionPrefab, transform.position, Quaternion.identity);

            // enemyダウン数関数の呼び出し。
            //GameManager.instance.AddCrushingCount();

            // 自分で消える。
            Destroy(this.gameObject);
        }
    }
}
