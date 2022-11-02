using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    // カメラから見た画面左下の座標を入れる変数
    Vector3 LeftBottom;

    // カメラから見た画面右下の座標を入れる変数
    Vector3 RightTop;

    private Vector3 mouse;
    private Vector3 target;


    // Start is called before the first frame update
    void Start()
    {
        //// カメラとプレイヤーの距離を測る（表示画面の四隅を設定するために必要）
        //var distance = Vector3.Distance(Camera.main.transform.position, transform.position);

        //// スクリーン画面左下の位置を設定する
        //LeftBottom = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, distance));

        //// スクリーン画面左下の位置を設定する
        //RightTop = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, distance));
    }

    // Update is called once per frame
    void Update()
    {
        //// プレイヤーのワールド座標を取得
        //Vector3 pos = transform.position;

        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.D))
        //{
        //    pos.x += 1.0f;
        //}
        //// 左矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.A))
        //{
        //    pos.x -= 1.0f;
        //}
        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.W))
        //{
        //    pos.y += 1.0f;
        //}
        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.S))
        //{
        //    pos.y -= 1.0f;
        //}

        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.UpArrow))
        //{
        //    pos.z += 1.0f;
        //}

        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.DownArrow))
        //{
        //    pos.z -= 1.0f;
        //}

        //transform.position = new Vector3(pos.x, pos.y, pos.z);

        //transform.position = new Vector3(Mathf.Clamp(mouse.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
        //   Mathf.Clamp(mouse.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y), -4);

        mouse = Input.mousePosition;
        target = Camera.main.ScreenToWorldPoint(new Vector3(mouse.x, mouse.y, 5));
        transform.position = target;
    }
}
