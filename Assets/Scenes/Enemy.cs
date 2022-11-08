using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{

    // Enemy�̗̑͗p�ϐ�
    private int enemyHp;

    private float chargeTime = 5.0f;
    private float timeCount;

    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        enemyHp = 3;
    }

    // Update is called once per frame
    void Update()
    {
        timeCount += Time.deltaTime;

        // �����O�i
        transform.position += transform.forward * Time.deltaTime;

        // �w�莞�Ԃ̌o�߁i�����j
        if (timeCount > chargeTime)
        {
            // �i�H�������_���ɕύX����
            Vector3 course = new Vector3(0, Random.Range(0, 180), 0);
            transform.localRotation = Quaternion.Euler(course);

            // �^�C���J�E���g���O�ɖ߂�
            timeCount = 0;
        }

        // �����̗͂�0�ȉ��ɂȂ�����
        if (enemyHp <= 0)
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
