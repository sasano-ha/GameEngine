using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialActive : MonoBehaviour
{
    public GameObject enemy_;

    public bool flag = false;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        TutorialShot shot;

        GameObject enemy = GameObject.Find("Barrel");

        shot = enemy.GetComponent<TutorialShot>();

        if(shot.Tu_enemy == true)
        {
            if(enemy_ != null)
            {
                enemy_.SetActive(true);
                flag = true;
            }
        }
    }
}