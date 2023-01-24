using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{

    private float speed = 0.05f;
    private Rigidbody rb;
    // 自然消滅までのタイマー
    public float time = 3;

    private Vector3 velocity;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        BulletMove();
    }

    public void BulletMove()
    {

        // 正面にまっすぐ飛ぶ
        transform.position += velocity;

        // 時間制限が来たら自然消滅する
        time -= Time.deltaTime;

        // 一定距離進んだら消滅する
        if (time <= 0)
        {
            Destroy(this.gameObject);
        }
    }


    // 当たり判定
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Enemy")
        {
            other.GetComponent<Enemy>().Damage();
        }
        Destroy(this.gameObject);
    }

    public void SetVelocity(Vector3 target_)
    {
        // 弾のワールド座標を取得
        Vector3 pos = transform.position;

        // ベクトルを取得
        var direction = target_ - pos;

        velocity = direction.normalized * speed;


        // キューブと生成時のターゲットの値が同じか
        // ベクトルでブレイクポイント(z)
        // 前後で位置が変わったか31
    }
}
