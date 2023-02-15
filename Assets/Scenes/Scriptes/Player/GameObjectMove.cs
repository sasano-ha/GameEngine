using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameObjectMove : MonoBehaviour
{
    public static GameObjectMove instance;

    public Vector3 gameobject;

    public void Awake()
    {
        if (instance == null)
        {
            // インスタンスの設定
            instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 gameobject = transform.position;
        gameobject.z += 0.1f;
        transform.position = new Vector3(gameobject.x, gameobject.y, gameobject.z);
    }
}
