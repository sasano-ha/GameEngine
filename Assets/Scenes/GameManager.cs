using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    // シングルトン
    public static GameManager instance;

    // 敵撃破用変数
    public int crushingCount = 0;

    // 敵撃破用テキスト
    public Text crashText;

    // スコア用テキスト
    [SerializeField] private Text scoreCount;

    // 敵ダウン数
    public int downScore = 0;

    // トータルスコアの変数
    public int totalScore = 0;

    // 自機生存フラグ
    public bool isPlayerAlive;

    // タイマーストップ用変数
    public int stopTimer = 1;

    // 自機の生存スコア用変数
    public int playerScore_;

    public GameObject enemy;

    public void Awake()
    {
        if (instance == null)
        {
            // インスタンスの設定
            instance = this;
        }

        // FPSを60に固定
        Application.targetFrameRate = 60;
    }


    void Start()
    {
        isPlayerAlive = true;
    }


    void Update()
    {
        ScoreResults();
    }

    
    // 敵ダウン数関数
    public void AddCrushingCount()
    {
        crushingCount += 1;
        AddDownScore();
        crashText.text = "CrushingCount : " + crushingCount;
        PlayerPrefs.SetInt("Enemy", crushingCount);
        PlayerPrefs.Save();
    }

    // スコア処理
    public void ScoreResults()
    {
        // スローモーション
        //Time.timeScale = 0.1f;

        // 自機が死んだら
        if (isPlayerAlive == false)
        {
            stopTimer = 0;
        }

        // タイマーを小数点以下切り捨てする。
        float timer = Time.deltaTime * 100;

        // 敵が全滅していない 又は 自機が生きているなら
        if (enemy.GetComponent<EnemyManager>().isEnemy_Die == true && PlayerHp.instance.pl_ScoreFlag == false ||
            enemy.GetComponent<EnemyManager>().isEnemy_Die == false && PlayerHp.instance.pl_ScoreFlag == true)
        {
            // プレイヤーの生存時間
            playerScore_ += (int)timer;
        }

        // スコアに生存時間とダウンスコアの加算。
        totalScore = playerScore_ + downScore * stopTimer;
        

        // でた全てのスコアを文字で描画
        scoreCount.text = "" + totalScore.ToString("d7");

        // ゲームオーバーでスコアを使いたいので変数を保存
        PlayerPrefs.SetInt("Score", totalScore);
        PlayerPrefs.Save();
    }

    private void AddDownScore()
    {
        downScore += 100;
    }
}
