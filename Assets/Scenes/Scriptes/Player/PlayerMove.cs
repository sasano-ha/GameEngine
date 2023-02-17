using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    public static PlayerMove instance;

    // マウス
    private Vector3 mouse;

    // ターゲット
    private Vector3 target;

    // playerのHP
    private int playerHp;

    Vector3 LeftBottom;

    Vector3 RightTop;


    // Start is called before the first frame update
    void Start()
    {
        var distans = Vector3.Distance(Camera.main.transform.position, transform.position);


        LeftBottom = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, distans));

        RightTop = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, distans));

        // 生成時に体力を指定しておく
        playerHp = 3;
    }

    // Update is called once per frame
    void LateUpdate()
    {

        // プレイヤーのワールド座標を取得
        Vector3 pos = transform.position;

        // 右矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.D))
        {
            pos.x += 0.1f;
        }
        // 左矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.A))
        {
            pos.x -= 0.1f;
        }
        // 右矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.W))
        {
            pos.y += 0.1f;
        }
        // 右矢印キーが入力されたら時
        if (Input.GetKey(KeyCode.S))
        {
            pos.y -= 0.1f;
        }

        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.UpArrow))
        //{
        //    pos.z += 0.1f;
        //}

        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.DownArrow))
        //{
        //    pos.z -= 0.1f;
        //}

        //transform.position = new Vector3(pos.x, pos.y, pos.z);

        transform.position = new Vector3(Mathf.Clamp(pos.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
           Mathf.Clamp(pos.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y), pos.z);

        if (playerHp <= 0)
        {
            Destroy(this.gameObject);
        }
    }

    //public void Damage()
    //{
    //    playerHp--;
    //}
}
