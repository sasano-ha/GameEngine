using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy: MonoBehaviour
{
    // Enemy�̗̑͗p�ϐ�
    private int enemyHp;

    private Vector3 targetpos;

    // gameManager�Ăяo��
    public GameManager gameManager;

    public Score scores;

    [SerializeField] GameObject explosionPrefab;

    private bool isInsideCamera = true;

    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        enemyHp = 2;

        targetpos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if(isInsideCamera == true)
        {
            targetpos.z -= 0.005f;

            if (targetpos.z <= 2)
            {
                targetpos.x += 0.1f;
                targetpos.z -= 0.1f;
            }

            //targetpos.x -= 0.01f;

            transform.position = new Vector3(Mathf.Sin(Time.time) * 2.0f + targetpos.x, targetpos.y, targetpos.z);

            // �����̗͂�0�ȉ��ɂȂ�����
            if (enemyHp <= 0 )
            {
                gameManager.AddCrushingCount();
                scores.AddDownScore();
                Instantiate(explosionPrefab, transform.position, Quaternion.identity);
                // �����ŏ�����
                Destroy(this.gameObject);
            }
        }
        else if(isInsideCamera == false)
        {
            Destroy(this.gameObject);
        }
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            other.GetComponent<PlayerHp>().Damage();
        }
    }

    private void OnBecameInvisible()
    {
        isInsideCamera = false;
    }

    public void Damage()
    {
        enemyHp--;
    }
}
