using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHp : MonoBehaviour
{
    // player‚ÌHP
    private int playerHp;

    // Start is called before the first frame update
    void Start()
    {
        // ¶¬‚É‘Ì—Í‚ğw’è‚µ‚Ä‚¨‚­
        playerHp = 3;
    }

    // Update is called once per frame
    void Update()
    {
        if (playerHp <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    public void Damage()
    {
        playerHp--;
    }
}
