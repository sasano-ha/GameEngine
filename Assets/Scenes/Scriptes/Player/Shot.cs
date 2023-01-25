using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shot : MonoBehaviour
{
    // ゲームオブジェクトをインスペクターから参照するための変数
    public GameObject bullet;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            GameObject bulletobject = Instantiate(bullet, transform.position, Quaternion.identity);

            Bullet bulletclone = bulletobject.GetComponent<Bullet>();

            // 弾を生成する（クローンさせている）
            bulletclone.SetVelocity(Cursor.instance.target);
        }
    }
}
