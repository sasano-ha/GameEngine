using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerRotetion : MonoBehaviour
{

    //private Quaternion player;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        gameObject.transform.Rotate(new Vector3(0.0f, 10.0f, 0.0f) * Time.deltaTime);
    }
}
