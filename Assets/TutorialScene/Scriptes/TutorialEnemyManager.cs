using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialEnemyManager : MonoBehaviour
{
    private GameObject[] enemies;

    public bool isEnemy_Die = true;

    // Update is called once per frame
    void Update()
    {

        TutorialShot shot;

        GameObject enemy = GameObject.Find("Barrel");

        shot = enemy.GetComponent<TutorialShot>();

        if (shot.Tu_enemy == true)
        {
            // �G�^�O������
            enemies = GameObject.FindGameObjectsWithTag("Enemy");


            // �G�^�O���Ȃ��Ȃ���������B
            if (enemies.Length <= 0)
            {
                isEnemy_Die = false;
            }
        }
    }
}
