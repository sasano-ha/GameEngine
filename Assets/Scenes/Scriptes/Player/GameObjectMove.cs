using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameObjectMove : MonoBehaviour
{
    public Vector3 gameobject;

    [SerializeField] public float speed = 10;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 gameobject = transform.position;
        gameobject.z += speed;
        transform.position = new Vector3(gameobject.x, gameobject.y, gameobject.z);
    }
}
