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

        // スクリーン座標をワールド座標に変更
        target = Camera.main.ScreenToWorldPoint(new Vector3(mousePos.x, mousePos.y, 7));

        transform.position = target;

        transform.position = new Vector3(mousePos.x, mousePos.y, 7);
    }
}
