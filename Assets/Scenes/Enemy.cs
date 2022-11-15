using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    // Enemyの体力用変数
    private int enemyHp;

    private Vector3 targetpos;

    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        enemyHp = 3;

        targetpos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        targetpos.z -= 0.005f;
        //targetpos.x -= 0.01f;

        transform.position = new Vector3(Mathf.Sin(Time.time) * 2.0f + targetpos.x, targetpos.y, targetpos.z);

        // もし体力が0以下になったら
        if (enemyHp <= 0 || targetpos.z <= -10)
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
