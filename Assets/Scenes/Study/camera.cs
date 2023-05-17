using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class camera : MonoBehaviour
{

    private float timer = 0;

    [SerializeField] Image image_;

    public bool flag = false;

    // 別スクリプトから変数を使うための変数
    [SerializeField] private GameObject enemy;

    //[SerializeField] private GameObject enemy;

    private void Awake()
    {
        //timer = 0;
        image_.enabled = false;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (enemy.GetComponent<EnemyManager>().isEnemy_Die == false)
        {
            timer += 1.0f;
            if (timer >= 100)
            {
                flag = true;
            }

            if (flag == true)
            {
                image_.enabled = true;
            }
        }
    }
}
