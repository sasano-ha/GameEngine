using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EnemyManager : MonoBehaviour
{
    private GameObject[] enemies;

    private float enemy_timer = 845;

    public bool isEnemy_Die = true;

    // Update is called once per frame
    void Update()
    {
        // �G�^�O������
        enemies = GameObject.FindGameObjectsWithTag("Enemy");


        // �G�^�O���Ȃ��Ȃ���������B
        if (enemies.Length == 0)
        {
            isEnemy_Die = false;
            // �}�ɃV�[���J�ڂ��Ȃ����߂̃^�C�}�[
            //enemy_timer -= 1.0f;

            // �莞�ɂȂ�����V�[�������[�h����B
            //if(enemy_timer <= 0)
            //{
            //    SceneManager.LoadScene("TitleScene");
            //}
        }
    }
}
