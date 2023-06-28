using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialEnemy : MonoBehaviour
{

    // アタッチするためのもの
    [SerializeField] GameObject explosionPrefab;

    // Enemyの体力用変数
    public float enemyHp;

    // カメラのフラグ
    public bool isInsideCamera = true;

    // 敵機関連の変数
    [SerializeField] private Vector3 en_pos, ap_force, es_force;

    public Enemy tutorialenemy;



    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        enemyHp = 1;

        tutorialenemy = GetComponent<Enemy>();
    }

    // Update is called once per frame
    void Update()
    {
        // 敵がカメラ内にいる時
        if (isInsideCamera == true)
        {
           
        }
    }

    // カメラフラグ関数
    public void OnBecameInvisible()
    {
        isInsideCamera = false;
    }
}
