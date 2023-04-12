using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    private GameObject player;
    private Vector3 offset;

    private void Awake()
    {
        
    }

    // Start is called before the first frame update
    void Start()
    {
        GetComponent<SceneFade>().Fadein();
        this.player = GameObject.Find("GameObject");
        offset = transform.position - player.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = player.transform.position + offset;
    }
}
