using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cursor : MonoBehaviour
{
    public static Cursor instance;

    public Vector3 target;

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
        // 計算した3Dオブジェクトのいれものを作る
    }

    // Update is caｓlled once per frame
    void Update()
    {
        // マウス座標の取得（スクリーン座標）
        transform.position = Input.mousePosition;

        // 取得したスクリーン座標をワールド座標に変換
        target = Camera.main.ScreenToWorldPoint(new Vector3(transform.position.x, transform.position.y, 40));
    }
}
