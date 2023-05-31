using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UiText : MonoBehaviour
{
    // Text用の入れ物
    public Text textUi;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //自機のダメージ関数の呼び出し。
        GetComponent<PlayerHp>().Player_Damage();

        // テキスト描画
        textUi.text = string.Format("100", PlayerHp.instance.playerMaxHp);
    }
}
