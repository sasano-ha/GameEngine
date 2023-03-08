using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    // シングルトン
    public static GameManager instance;

    // 敵撃破用変数
    private int crushingCount = 0;

    // 敵撃破用テキスト
    public Text crashText;

    // スコア用テキスト
    [SerializeField] private Text scoreCount;

    // 敵ダウン数
    private int downScore = 0;

    // トータルスコアの変数
    int totalScore = 0;

    // 自機生存フラグ
    public bool isPlayerAlive;

    // タイマーストップ用変数
    int stopTimer = 1;

    // 自機の生存スコア用変数
    int playerScore_;


    public void Awake()
    {
        if (instance == null)
        {
            // インスタンスの設定
            instance = this;
        }
    }


    void Start()
    {
        // FPSを60に固定
        Application.targetFrameRate = 60;

        isPlayerAlive = true;
    }


    void Update()
    {
        ScoreResults();
    }


    // シーン変更関数
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }

    
    // 敵ダウン数関数
    public void AddCrushingCount()
    {
        crushingCount += 1;
        crashText.text = "CrushingCount : " + crushingCount;
    }

    // スコア処理
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


    // 敵ダウンスコア関数
    public void AddDownScore()
    {
        downScore += 10;
    }
}
