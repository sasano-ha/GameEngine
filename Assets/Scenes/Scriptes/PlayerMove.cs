using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    // マウス
    private Vector3 mouse;

    // ターゲット
    private Vector3 target;

    // playerのHP
    private int playerHp;

    private bool cusorflag = true;

    // Start is called before the first frame update
    void Start()
    {
        // 生成時に体力を指定しておく
        playerHp = 3;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        // マウスカーソルを表示させない
        //Cursor.visible = false;

        // マウスカーソルの移動範囲の制限
        //Cursor.lockState = CursorLockMode.Confined;

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

        transform.position = new Vector3(pos.x, pos.y, pos.z);

        //transform.position = new Vector3(Mathf.Clamp(mouse.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
           //Mathf.Clamp(mouse.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y), -4);

        //mouse = Input.mousePosition;
        //target = Camera.main.ScreenToWorldPoint(new Vector3(mouse.x, mouse.y, 7));
        //transform.position = target;

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
