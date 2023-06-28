using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    // 敵機の行動遷移
    public enum State {
        approach,   // 近づく
        offence,    // 攻撃
        escape,     //逃げる
    }

    // 行動遷移変数
    State state_;

    // アタッチするためのもの
    [SerializeField] GameObject explosionPrefab;

    // Enemyの体力用変数
    public float enemyHp;

    // カメラのフラグ
    public bool isInsideCamera = true;

    // 敵機関連の変数
    [SerializeField] private Vector3 en_pos, ap_force, es_force;

    // 敵機が撃った時のフラグ
    public bool en_ShotFag = false;

    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        enemyHp = 1;

        // 最初の行動遷移
        state_ = State.approach;
    }

    private void FixedUpdate()
    {
        switch (state_)
        {
            case State.approach:
            default:
                EnemyApproach();
                break;

            case State.offence:
                EnemyOffence();
                break;

            case State.escape:
                EnmeyEscape();
                break;
        }
    }

    // Update is called once per frame
    void Update()
    {
        // 敵がカメラ内にいる時
        if (isInsideCamera == true)
        {
            En_Die();
        }

        // enemyがカメラ外に行った時
        else if (isInsideCamera == false)
        {
            // enemyのオブジェクトを消す。
            Destroy(this.gameObject);
        }
    }

    // カメラフラグ関数
    public void OnBecameInvisible()
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

    // 敵機が死んだ関数
    public void En_Die()
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

    // 敵機の近づく関数
    private void EnemyApproach()
    {
        Rigidbody rb = this.GetComponent<Rigidbody>();

        ap_force = new Vector3(0, 0, -3.0f);
        rb.AddForce(ap_force, ForceMode.Force);

        if (isInsideCamera == true)
        {
            state_ = State.offence;
        }
    }

    // 敵機の攻撃関数
    private void EnemyOffence()
    {
        en_ShotFag = true;

        Rigidbody rb = this.GetComponent<Rigidbody>();

        ap_force = new Vector3(0, 0, -3.0f);
        rb.AddForce(ap_force, ForceMode.Force);

        en_pos = transform.position;

        var diff = PlayerMove.instance.pos - en_pos;

        if (diff.magnitude < 20)
        {
            state_ = State.escape;
        }
    }

    // 敵機の逃げる関数
    private void EnmeyEscape()
    {
        Rigidbody rb = this.GetComponent<Rigidbody>();

        if(PlayerMove.instance.pos.x > en_pos.x)
        {
            int random = Random.Range(3, 7);
            es_force = new Vector3(-3.0f, random, -3.0f);
        }
        else if(PlayerMove.instance.pos.x < en_pos.x)
        {
            int random = Random.Range(3, 7);
            es_force = new Vector3(3.0f, random, -3.0f);
        }

        rb.AddForce(es_force, ForceMode.Force);
    }
}
