using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SceneChangeManager : MonoBehaviour
{
    // シーン変更関数
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }
}
