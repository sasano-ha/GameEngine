using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy: MonoBehaviour
{
    // Enemy‚Ì‘Ì—Í—p•Ï”
    private int enemyHp;

    private Vector3 targetpos;

    public GameManager gameManager;

    private bool isInsideCamera = true;

    // Start is called before the first frame update
    void Start()
    {
        // ¶¬‚É‘Ì—Í‚ğw’è‚µ‚Ä‚¨‚­
        enemyHp = 3;

        targetpos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if(isInsideCamera == true)
        {
            targetpos.z -= 0.005f;

            if (targetpos.z <= 2)
            {
                targetpos.x += 0.1f;
                targetpos.z -= 0.1f;
            }

            //targetpos.x -= 0.01f;

            transform.position = new Vector3(Mathf.Sin(Time.time) * 2.0f + targetpos.x, targetpos.y, targetpos.z);

            // ‚à‚µ‘Ì—Í‚ª0ˆÈ‰º‚É‚È‚Á‚½‚ç
            if (enemyHp <= 0 || targetpos.z <= -10)
            {
                gameManager.AddCrushingCount();
                // ©•ª‚ÅÁ‚¦‚é
                Destroy(this.gameObject);
            }
        }
        else if(isInsideCamera == false)
        {
            Destroy(this.gameObject);
        }
        
    }

    private void OnBecameInvisible()
    {
        isInsideCamera = false;
    }

    public void Damage()
    {
        enemyHp--;
    }
}
