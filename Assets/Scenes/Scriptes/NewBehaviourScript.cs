using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewBehaviourScript : MonoBehaviour
{
    // 速さの設定
    private float speed = 0.00f;
    public float ratio;

    // 自然消滅までのタイマー
    public float time = 3;

    // 速度
    [SerializeField] private Vector3 velocity;

    // Start is called before the first frame update
    void Start()
    {

    }

    private void Update()
    {
        EnemyBulletMove();
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

    public void SetEnemyVelocity(Vector3 target_position)
    {
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

        //velocity = diff.normalized * speed;

        //transform.rotation *= q;

        // 座標の更新
        var torque = new Vector3(q.x, q.y, q.z) * ratio;

        // トルクを加える。
        GetComponent<Rigidbody>().AddTorque(torque);

        velocity = transform.forward * speed;
    }
}
