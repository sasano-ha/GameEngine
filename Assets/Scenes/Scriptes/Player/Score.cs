using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{

    // �G���j�e�L�X�g
    [SerializeField] private Text scoreCount;
     
    int totalScore;

    private int downScore;

    // Start is called before the first frame update
    void Start()
    {
        // �l�̏�����
        //totalScore = 0;

        downScore = 0;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        // ���@�̋������X�R�A�ɕϊ��B
        int playerScore_ = (int)PlayerMove.instance.pos.z;

        totalScore = playerScore_ + downScore;

        // �X�R�A�������_��1�ʂ͂���Ȃ��̂Ő؂�̂āB
        //totalScore = Mathf.Floor(playerScore_);

        // �o�����X�R�A�����Z������B
        scoreCount.text = "" + totalScore.ToString("d5");
    }

    public void AddDownScore()
    {
        downScore += 10;
    }
}
