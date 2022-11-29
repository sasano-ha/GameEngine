using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HpText : MonoBehaviour
{

    // “GŒ‚”j—p•Ï”
    private float hitPointCount;

    // “GŒ‚”jƒeƒLƒXƒg
    public Text textHitPoint;

    void Start()
    {
        textHitPoint.color = Color.green;
    }

    void LateUpdate()
    {
        hitPointCount = PlayerHp.instance.playerHp;
        textHitPoint.text = "" + hitPointCount;

        if (hitPointCount < 50)
        {
            textHitPoint.color = Color.red;
        }
        else if(hitPointCount < 80)
        {
            textHitPoint.color = new Color(1f, 0.67f, 0f);
        }
    }
}
