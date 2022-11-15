using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy: MonoBehaviour
{
    // Enemy�̗̑͗p�ϐ�
    private int enemyHp;

    private Vector3 targetpos;

    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        enemyHp = 3;

        targetpos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        targetpos.z -= 0.005f;

        if(targetpos.z <= 2)
        {
            targetpos.x += 0.1f;
            targetpos.z -= 0.1f;
        }

        //targetpos.x -= 0.01f;

        transform.position = new Vector3(Mathf.Sin(Time.time) * 2.0f + targetpos.x, targetpos.y, targetpos.z);

        // �����̗͂�0�ȉ��ɂȂ�����
        if (enemyHp <= 0 || targetpos.z <= -10)
        {
            // �����ŏ�����
            Destroy(this.gameObject);
        }
    }

    public void Damage()
    {
        enemyHp--;
    }
}
