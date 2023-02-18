using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{

    // 敵撃破テキスト
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
