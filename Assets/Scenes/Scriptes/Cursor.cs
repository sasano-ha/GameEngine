using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cursor : MonoBehaviour
{
    // 座標用の変数
    private Vector2 mousePos, target;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // マウス座標の取得
        mousePos = Input.mousePosition;
        // マウスの座標を代入する
        transform.position = mousePos;
    }
}
