using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyShot : MonoBehaviour
{

    // ゲームオブジェクトをインスペクターから参照するための変数
    public GameObject en_bullet;

    int timer = 0;

    Enemy enemy_;
   

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        enemy_ = GetComponent<Enemy>();

        if(enemy_.en_ShotFag == true)
        {
            timer++;

            if (timer == 60)
            {
                GameObject en_bulletobject = Instantiate(en_bullet, transform.position, Quaternion.identity);

                //NewBehaviourScript en_bulletclone = en_bulletobject.GetComponent<NewBehaviourScript>();

                //en_bulletclone.SetEnemyVelocity(PlayerMove.instance.pos);

                //timer = 60;
            }
        }
    }
}
