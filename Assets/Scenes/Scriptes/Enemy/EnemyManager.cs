using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EnemyManager : MonoBehaviour
{
    private GameObject[] enemies;

    public bool isEnemy_Die = false;

    // Update is called once per frame
    void Update()
    {
        // �G�^�O������
        enemies = GameObject.FindGameObjectsWithTag("Enemy");


        // �G�^�O���Ȃ��Ȃ���������B
        if (enemies.Length == 0)
        {
            isEnemy_Die = true;
        }
    }
}
