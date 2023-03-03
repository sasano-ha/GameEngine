using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UiText : MonoBehaviour
{
    // Text—p‚Ì“ü‚ê•¨
    public Text textUi;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        GetComponent<PlayerHp>().Damage();
        textUi.text = string.Format("100", PlayerHp.instance.playerMaxHp);
    }
}
