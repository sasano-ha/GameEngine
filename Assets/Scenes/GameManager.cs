using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    // �V���O���g��
    public static GameManager instance;

    // �G���j�p�ϐ�
    public int crushingCount = 0;

    // �G���j�p�e�L�X�g
    public Text crashText;

    // �X�R�A�p�e�L�X�g
    [SerializeField] private Text scoreCount;

    // �G�_�E����
    private int downScore = 0;

    // �g�[�^���X�R�A�̕ϐ�
    public int totalScore = 0;

    // ���@�����t���O
    public bool isPlayerAlive;

    // �^�C�}�[�X�g�b�v�p�ϐ�
    int stopTimer = 1;

    // ���@�̐����X�R�A�p�ϐ�
    int playerScore_;

    public GameObject enemy;


    public void Awake()
    {
        if (instance == null)
        {
            // �C���X�^���X�̐ݒ�
            instance = this;
        }

        // FPS��60�ɌŒ�
        Application.targetFrameRate = 60;
    }


    void Start()
    {
        isPlayerAlive = true;
    }


    void Update()
    {
        if (enemy.GetComponent<EnemyManager>().isEnemy_Die == true || PlayerManager.instance.player.Length > 0)
        {
            ScoreResults();
        }
        //ScoreResults();
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
        // �X���[���[�V����
        //Time.timeScale = 0.1f;

        // ���@�����񂾂�
        if (isPlayerAlive == false)
        {
            stopTimer = 0;
        }

        // �^�C�}�[�������_�ȉ��؂�̂Ă���B
        float timer = Time.deltaTime * 100;
        //float timer = 1.0f;

        // �v���C���[�̐�������
        playerScore_ += (int)timer;

        // �X�R�A�ɐ������Ԃƃ_�E���X�R�A�̉��Z�B
        totalScore = playerScore_ + downScore * stopTimer;

        // �ł��S�ẴX�R�A�𕶎��ŕ`��
        scoreCount.text = "" + totalScore.ToString("d7");
    }


    // �G�_�E���X�R�A�֐�
    public void AddDownScore()
    {
        downScore += 10;
    }
}
