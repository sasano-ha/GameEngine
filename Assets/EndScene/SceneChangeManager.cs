using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;

public class SceneChangeManager : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // ƒV[ƒ“•ÏXŠÖ”
    public void ChangScene(string nextScene)
    {
        SceneManager.LoadScene(nextScene);
    }
}
