using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SceneChangeManager : MonoBehaviour
{
    // �V�[���ύX�֐�
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }
}
