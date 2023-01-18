using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiddleCursor : MonoBehaviour
{
    private Vector3 mousPos;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        mousPos = Input.mousePosition;

        transform.position = Camera.main.ScreenToWorldPoint(new Vector3(mousPos.x, mousPos.y, 50));
    }
}
