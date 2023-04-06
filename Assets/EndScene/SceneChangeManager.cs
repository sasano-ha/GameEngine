using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SceneChangeManager : MonoBehaviour
{
    // ƒV[ƒ“•ÏXŠÖ”
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }
}
