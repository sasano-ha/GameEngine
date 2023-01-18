using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{

    private float velocity = 0.05f;
    private Rigidbody rb;
    // 自然消滅までのタイマー
    public float time = 3;


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
        // 弾のワールド座標を取得
        Vector3 pos = transform.position;

        // 正面にまっすぐ飛ぶ
        pos.z += 1.0f;

        // 弾の移動
        transform.position = new Vector3(pos.x, pos.y, pos.z);

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
}
