using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cursor : MonoBehaviour
{
    // 座標用の変数
    private Vector3 mousePos, target;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //マウス座標の取得
        mousePos = Input.mousePosition;

        // ワールド座標の照準になる。
        transform.position = mousePos;
    }

    private void CreateShot(float axis)
    {
        // ベクトルを取得
        //var dirction = transform.position - P
    }
}
