using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    Vector3 mousePos, worldPos;

    //public Camera UICamera;
    public Transform target;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //mousePos = Input.mousePosition;

       // Vector3 ScreenPos = Camera.main.WorldToViewportPoint(target.position);
        //ScreenPos.z = 0;

        //Vector3 ScreenPos = Camera.main.WorldToViewportPoint(new Vector3(0, 0, 10));

        //worldPos = Camera.main.WorldToScreenPoint(new Vector3(0, 0, 10));
        //worldPos = UICamera.ViewportToWorldPoint(ScreenPos);

        //worldPos = target.position;

        //worldPos = Camera.main.ScreenToWorldPoint(new Vector3(mousePos.x, mousePos.y, 10f));

        transform.position = target.position;
    }
}
