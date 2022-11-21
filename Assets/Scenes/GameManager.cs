using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    private int crushingCount;
    public Text textComponent;

    private void Start()
    {
        crushingCount = 0;
        Application.targetFrameRate = 60;
    }

    //public void ChangScene(string nextScene)
    //{
    //    SceneManager.LoadScene(nextScene);
    //}

    public void AddCrushingCount()
    {
        crushingCount += 1;
        textComponent.text = "CrushingCount : " + crushingCount;
    }
}
