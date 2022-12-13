using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shot : MonoBehaviour
{
    // ゲームオブジェクトをインスペクターから参照するための変数
    public GameObject Bullet;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            // 弾を生成する（クローンさせている）
            Instantiate(Bullet, transform.position, Quaternion.identity);
        }
    }
}
