using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }
}
