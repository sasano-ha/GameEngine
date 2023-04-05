using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyShot : MonoBehaviour
{
    // ゲームオブジェクトをインスペクターから参照するための変数
    public GameObject en_bullet;

    float timer;

    // Start is called before the first frame update
    void Start()
    {
        timer = 60.0f;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        timer--;

        if(timer <= 0)
        {
            GameObject en_bulletobject = Instantiate(en_bullet, transform.position, Quaternion.identity);

            NewBehaviourScript en_bulletclone = en_bulletobject.GetComponent<NewBehaviourScript>();

            en_bulletclone.SetEnemyVelocity(PlayerMove.instance.pos);

        }
    }
}
