using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    // �G���j�p�ϐ�
    private int crushingCount;

    // �G���j�e�L�X�g
    public Text crashText;

    private void Start()
    {
        crushingCount = 0;
        Application.targetFrameRate = 60;
    }

    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }

    public void AddCrushingCount()
    {
        crushingCount += 1;
        crashText.text = "CrushingCount : " + crushingCount;
    }
}
