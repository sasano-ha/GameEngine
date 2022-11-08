using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{

    // Enemyの体力用変数
    private int enemyHp;

    private float chargeTime = 5.0f;
    private float timeCount;

    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        enemyHp = 3;
    }

    // Update is called once per frame
    void Update()
    {
        timeCount += Time.deltaTime;

        // 自動前進
        transform.position += transform.forward * Time.deltaTime;

        // 指定時間の経過（条件）
        if (timeCount > chargeTime)
        {
            // 進路をランダムに変更する
            Vector3 course = new Vector3(0, Random.Range(0, 180), 0);
            transform.localRotation = Quaternion.Euler(course);

            // タイムカウントを０に戻す
            timeCount = 0;
        }

        // もし体力が0以下になったら
        if (enemyHp <= 0)
        {
            // 自分で消える
            Destroy(this.gameObject);
        }
    }

    public void Damage()
    {
        enemyHp--;
    }
}
