using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cursor : MonoBehaviour
{

    // Start is called before the first frame update
    void Start()
    {
        transform.position = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        //マウス座標の取得
        transform.position = Input.mousePosition;
    }
}
