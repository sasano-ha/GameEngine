using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyShot : MonoBehaviour
{
    // �Q�[���I�u�W�F�N�g���C���X�y�N�^�[����Q�Ƃ��邽�߂̕ϐ�
    public GameObject en_bullet;

    float timer = 60.0f;

    // Start is called before the first frame update
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update()
    {
        timer--;

        if(timer <= 0)
        {
            GameObject en_bulletobject = Instantiate(en_bullet, transform.position, Quaternion.identity);

            //NewBehaviourScript en_bulletclone = en_bulletobject.GetComponent<NewBehaviourScript>();

            
            //en_bulletclone.SetEnemyVelocity(PlayerMove.instance.pos);

            timer = 60;

        }
    }
}
