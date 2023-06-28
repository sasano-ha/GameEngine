using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialBullet : MonoBehaviour
{
    // 速さの設定
    private float speed = 3.0f;

    private Rigidbody rb;

    // 自然消滅までのタイマー
    public float time = 3;

    // 速度
    private Vector3 velocity;

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
    }

    public void SetVelocity(Vector3 target_)
    {
        // 弾のワールド座標を取得
        Vector3 pos = transform.position;

        // ベクトルを取得
        var direction = target_ - pos;

        // 正規化したベクトルに速さを掛けて速度にする。
        velocity = direction.normalized * speed;
    }
}
