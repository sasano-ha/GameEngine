using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleText : MonoBehaviour
{
    private int count = 0;

    private float move = 0.5f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        this.transform.position += new Vector3(0, move, 0);
        count++;

        if(count == 70)
        {
            count = 0;

            move *= -1;
        }
    }
}
