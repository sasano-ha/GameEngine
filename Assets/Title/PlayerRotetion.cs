using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerRotetion : MonoBehaviour
{

    //private Quaternion player;

    private Vector3 titlePlayer;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //titlePlayer += new Vector3(titlePlayer.x + 10, titlePlayer.y, titlePlayer.z);

        //transform.position += new Vector3(10, 0, 0);

        //transform.position += new Vector3(0, 0, 1) * Time.deltaTime;s

        gameObject.transform.Rotate(new Vector3(0.0f, 10.0f, 0.0f) * Time.deltaTime);
    }
}
