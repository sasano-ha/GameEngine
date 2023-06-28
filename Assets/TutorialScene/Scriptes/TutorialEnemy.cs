using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialEnemy : MonoBehaviour
{

    // �A�^�b�`���邽�߂̂���
    [SerializeField] GameObject explosionPrefab;

    // Enemy�̗̑͗p�ϐ�
    public float enemyHp;

    // �J�����̃t���O
    public bool isInsideCamera = true;

    // �G�@�֘A�̕ϐ�
    [SerializeField] private Vector3 en_pos, ap_force, es_force;

    public Enemy tutorialenemy;



    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        enemyHp = 1;

        tutorialenemy = GetComponent<Enemy>();
    }

    // Update is called once per frame
    void Update()
    {
        // �G���J�������ɂ��鎞
        if (isInsideCamera == true)
        {
           
        }
    }

    // �J�����t���O�֐�
    public void OnBecameInvisible()
    {
        isInsideCamera = false;
    }
}
