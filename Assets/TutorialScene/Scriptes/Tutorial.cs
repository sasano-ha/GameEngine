using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tutorial : MonoBehaviour
{

    [SerializeField] GameObject image1;
    [SerializeField] GameObject image2;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        TutorialPlayerMove move;
        GameObject player = GameObject.Find("StarSparrow1 1");
        move = player.GetComponent<TutorialPlayerMove>();

        if(move.ShotFlag == true)
        {
            image1.SetActive(false);
            image2.SetActive(true);
        }

    }
}
