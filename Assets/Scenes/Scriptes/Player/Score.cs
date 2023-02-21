using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{

    // �G���j�e�L�X�g
    public Text scoreCount;

    float totalScore;

    private float downScore;

    // Start is called before the first frame update
    void Start()
    {
        // �l�̏�����
        totalScore = 0;

        downScore = 0;
    }

    // Update is called once per frame
    void Update()
    {
        // ���@�̋������X�R�A�ɕϊ��B
        float playerScore_ = PlayerMove.instance.pos.z;

        // �X�R�A�������_��1�ʂ͂���Ȃ��̂Ő؂�̂āB
        totalScore = Mathf.Floor(playerScore_);

        // �o�����X�R�A�����Z������B
        scoreCount.text = "" + totalScore;
    }

    public void AddDownScore()
    {
        downScore += 10;
        scoreCount.text = "DownScore : " + downScore;
    }
}
