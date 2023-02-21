using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{

    // 敵撃破テキスト
    public Text scoreCount;

    float totalScore;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        // 自機の距離をスコアに変換。
        float playerScore_ = PlayerMove.instance.pos.z;

        // スコアが小数点第1位はいらないので切り捨て。
        totalScore = Mathf.Floor(playerScore_);

        // 出来たスコアを加算させる。
        scoreCount.text = "" + totalScore;
    }
}
