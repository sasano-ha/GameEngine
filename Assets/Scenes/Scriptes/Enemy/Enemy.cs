using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{

    public enum State {
        approach,
        offence,
        escape,
    }

    State state_;

    // アタッチするためのもの
    [SerializeField] GameObject explosionPrefab;

    // Enemyの体力用変数
    public float enemyHp;

    // カメラのフラグ
    public bool isInsideCamera = true;

    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        enemyHp = 1;

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

    private void EnemyApproach()
    {
        Rigidbody rb = this.GetComponent<Rigidbody>();

        Vector3 force = new Vector3(0, 0, -2.0f);
        rb.AddForce(force, ForceMode.Force);

        Vector3 en_pos = transform.position;

        var diff = PlayerMove.instance.pos - en_pos;

        if(diff.magnitude < 20)
        {
            state_ = State.escape;
        }

    }

    private void EnmeyEscape()
    {
        Rigidbody rb = this.GetComponent<Rigidbody>();

        Vector3 force = new Vector3(-2.0f, 1.0f, -1.0f);
        rb.AddForce(force, ForceMode.Force);
    }
}
