using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewBehaviourScript : MonoBehaviour
{
    // 速さの設定
    [SerializeField] private float speed = 0.1f;
    [SerializeField] private float ratio;

    // 自然消滅までのタイマー
    [SerializeField] private float time = 60;

    // 速度
    [SerializeField] private Vector3 velocity;

    // カメラ内判定のフラグ
    private bool bull_camera = true;

    //Enemy

    void FixedUpdate()
    {
        // 自機の座標を代入
        Vector3 target_position = PlayerMove.instance.pos;

        // ベクトルを取得
        var diff = target_position - transform.position;

        // ベクトルの方向に向く
        var target_rot = Quaternion.LookRotation(diff);

        // 左手系を右手系に変換
        var q = target_rot * Quaternion.Inverse(transform.rotation);

        // 近い方に回って欲しいので
        if (q.w < 0f)
        {
            q.x = -q.x;
            q.y = -q.y;
            q.z = -q.z;
            q.w = -q.w;
        }

        // 制限内だったら
        if (diff.magnitude > 1)
        {
            // 座標の更新
            var torque = new Vector3(q.x, q.y, q.z) * ratio;

            // トルクを加える。
            GetComponent<Rigidbody>().AddTorque(torque);
        }
        velocity = transform.forward * speed;

    }

    private void Update()
    {
        // カメラ内にいる時
        if(bull_camera == true)
        {
            EnemyBulletMove();
        }

        // カメラ内にいない時
        else if (bull_camera == false)
        {
            Destroy(this.gameObject);
        }
       
    }

    public void EnemyBulletMove()
    {

        // 正面にまっすぐ飛ぶ
        transform.position += velocity;

        // 時間制限が来たら自然消滅する
        time -= Time.deltaTime;

        // 一定時間経ったら消滅する
        if (time <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    // カメラフラグ関数
    public void OnBecameInvisible()
    {
        bull_camera = false;
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Player")
        {
            PlayerHp.instance.Player_Damage();
            Destroy(this.gameObject);
        }

        else if (other.gameObject.tag == "PlayerBullet")
        {
            Destroy(this.gameObject);
        }
    }
}
