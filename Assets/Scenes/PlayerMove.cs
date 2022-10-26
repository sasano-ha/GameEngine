using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    // カメラから見た画面左下の座標を入れる変数
    Vector3 LeftBottom;

    // カメラから見た画面右下の座標を入れる変数
    Vector3 RightTop;


    // Start is called before the first frame update
    void Start()
    {
        // カメラとプレイヤーの距離を測る（表示画面の四隅を設定するために必要）
        var distance = Vector3.Distance(Camera.main.transform.position, transform.position);

        // スクリーン画面左下の位置を設定する
        LeftBottom = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, distance));

        // スクリーン画面左下の位置を設定する
        RightTop = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, distance));
    }

    // Update is called once per frame
    void Update()
    {
        // プレイヤーのワールド座標を取得
        Vector3 pos = transform.position;

        // 右矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.D))
        {
            pos.x += 0.01f;
        }
        // 左矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.A))
        {
            pos.x -= 0.01f;
        }
        // 右矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.W))
        {
            pos.y += 0.01f;
        }
        // 右矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.S))
        {
            pos.y -= 0.01f;
        }

        transform.position = new Vector3(Mathf.Clamp(pos.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
           Mathf.Clamp(pos.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y),pos.z);
    }
}
