using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DrawingSoure : MonoBehaviour
{
    // �`��p�̃^�C�}�[
    private float timer = 0;

    // image�p�̕ϐ�
    [SerializeField] Image image_;

    // �`��J�n�̃t���O
    public bool flag = false;

    // �ʃX�N���v�g����ϐ����g�����߂̕ϐ�
    [SerializeField] private GameObject enemy;

    private void Awake()
    {
        // image��`�悳���Ȃ�
        image_.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        // �G�����Ȃ��Ȃ�����
        if (enemy.GetComponent<EnemyManager>().isEnemy_Die == false)
        {
            // �^�C�}�[��i�߂�
            timer++;

            // ��莞�Ԃ��o������
            if (timer >= 100)
            {
                //�t���O���o�Ă�
                flag = true;
            }

            if (flag == true)
            {
                // image��`�悳����
                image_.enabled = true;
            }
        }

    }
}
