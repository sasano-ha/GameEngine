using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    // �V���O���g��
    public static GameManager instance;

    // �G���j�p�ϐ�
    private int crushingCount = 0;

    // �G���j�p�e�L�X�g
    public Text crashText;

    // �X�R�A�p�e�L�X�g
    [SerializeField] private Text scoreCount;

    // �G�_�E����
    private int downScore = 0;

    // �g�[�^���X�R�A�̕ϐ�
    int totalScore = 0;

    // ���@�����t���O
    public bool isPlayerAlive;

    // �^�C�}�[�X�g�b�v�p�ϐ�
    int stopTimer = 1;

    // ���@�̐����X�R�A�p�ϐ�
    int playerScore_;


    public void Awake()
    {
        if (instance == null)
        {
            // �C���X�^���X�̐ݒ�
            instance = this;
        }
    }


    void Start()
    {
        // FPS��60�ɌŒ�
        Application.targetFrameRate = 60;

        isPlayerAlive = true;
    }


    void Update()
    {
        ScoreResults();
    }


    // �V�[���ύX�֐�
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }

    
    // �G�_�E�����֐�
    public void AddCrushingCount()
    {
        crushingCount += 1;
        crashText.text = "CrushingCount : " + crushingCount;
    }

    // �X�R�A����
    private void ScoreResults()
    {
        Time.timeScale = 1.0f;

        if (isPlayerAlive == false)
        {
            stopTimer = 0;
        }

        playerScore_ += (int)Time.time * stopTimer;

        totalScore = playerScore_ + downScore;

        scoreCount.text = "" + totalScore.ToString("d5");
    }


    // �G�_�E���X�R�A�֐�
    public void AddDownScore()
    {
        downScore += 10;
    }
}
