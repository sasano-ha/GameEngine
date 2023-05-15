using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class jump : MonoBehaviour
{

    float jump_ = 10;

    Rigidbody rg;

    float speed = 10;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            Rigidbody rg = GetComponent<Rigidbody>();

            rg.velocity = new Vector3(0, jump_, 0);
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            Rigidbody rg = GetComponent<Rigidbody>();
            rg.velocity = new Vector3(-speed, 0, 0);
        }
        if (Input.GetKeyDown(KeyCode.W))
        {
            Rigidbody rg = GetComponent<Rigidbody>();
            rg.velocity = new Vector3(0, 0, speed);
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            Rigidbody rg = GetComponent<Rigidbody>();
            rg.velocity = new Vector3(0, 0, -speed);
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            Rigidbody rg = GetComponent<Rigidbody>();
            rg.velocity = new Vector3(speed, 0, 0);
        }

    }
}
