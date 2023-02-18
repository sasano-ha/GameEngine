using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{

    // �G���j�e�L�X�g
    public Text scoreCount;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float score = PlayerMove.instance.pos.z;

        score = Mathf.Floor(score);

        scoreCount.text = "" + score;
    }
}
