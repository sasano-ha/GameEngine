using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{

    // 敵撃破テキスト
    [SerializeField] private Text scoreCount;
     
    int totalScore;

    private int downScore;

    // Start is called before the first frame update
    void Start()
    {
        // 値の初期化
        //totalScore = 0;

        downScore = 0;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        // 自機の距離をスコアに変換。
        int playerScore_ = (int)PlayerMove.instance.pos.z;

        totalScore = playerScore_ + downScore;

        // スコアが小数点第1位はいらないので切り捨て。
        //totalScore = Mathf.Floor(playerScore_);

        // 出来たスコアを加算させる。
        scoreCount.text = "" + totalScore.ToString("d5");
    }

    public void AddDownScore()
    {
        downScore += 10;
    }
}
