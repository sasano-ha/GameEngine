using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SceneChangeManager : MonoBehaviour
{
    // ÉVÅ[ÉìïœçXä÷êî
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }

    public void SceneChangTitle()
    {
        SceneManager.LoadScene("TitleScene");
    }

    public void SceneChangGame()
    {
        SceneManager.LoadScene("GameScene");
    }

    public void SceneChangClear()
    {
        SceneManager.LoadScene("EndScene");
    }

    public void SceneChangEnd()
    {
        SceneManager.LoadScene("GameOverScene");
    }
}
