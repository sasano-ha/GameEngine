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

    // 自機の座標の入れ物
    public Vector3 pos;


    Vector3 LeftBottom;


    Vector3 RightTop;

    [SerializeField] private float speed = 0.1f;

    public float moveForceMultiplier;

    // 水平移動時に機首を左右に向けるトルク
    public float yawTorqueMagnitude = 30.0f;

    // 垂直移動時に機首を上下に向けるトルク
    public float pitchTorqueMagnitude = 60.0f;

    // 水平移動時に機体を左右に傾けるトルク
    public float rollTorqueMagnitude = 30.0f;

    // バネのように姿勢を元に戻すトルク
    public float restoringTorqueMagnitude = 100.0f;

    private new Rigidbody rigidbody;

    public void Awake()
    {
        if (instance == null)
        {
            // インスタンスの設定
            instance = this;
        }

        rigidbody = GetComponent<Rigidbody>();

        // バネ復元力でゆらゆら揺れ続けるのを防ぐため、angularDragを大きめにしておく
        rigidbody.angularDrag = 20.0f;
    }


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
    void FixedUpdate()
    {
        // すぐに-1から1の範囲をfloat型で返す。
        float x = Input.GetAxisRaw("Horizontal");
        float y = Input.GetAxisRaw("Vertical");

        // xとyにspeedを掛ける。
        rigidbody.AddForce(x * speed, y * speed, 0);

        // vectorを0にする
        Vector3 moveVector = Vector3.zero;

        
        rigidbody.AddForce(moveForceMultiplier * (moveVector - rigidbody.velocity));

        Vector3 rotationTorque = new Vector3(-y * pitchTorqueMagnitude, x * yawTorqueMagnitude, -x * rollTorqueMagnitude);

        Vector3 right = transform.right;
        Vector3 up = transform.up;
        Vector3 forward = transform.forward;
        Vector3 restoringTorque = new Vector3(forward.y - up.z, right.z - forward.x, up.x - right.y) * restoringTorqueMagnitude;

        rigidbody.AddTorque(rotationTorque + restoringTorque);

        // プレイヤーのワールド座標を取得
        //pos = transform.position;

        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.D))
        //{
        //    rigidbody.AddForce(pos.x * speed, 0, 0);
        //    //pos.x += speed;
        //}
        //// 左矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.A))
        //{
        //    rigidbody.AddForce(pos.x * -speed, 0, 0);
        //    //pos.x -= speed;
        //}
        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.W))
        //{
        //    rigidbody.AddForce(0, pos.y * speed, 0);
        //    //pos.y += speed;
        //}
        //// 右矢印キーが入力されたら時
        //if (Input.GetKey(KeyCode.S))
        //{
        //    rigidbody.AddForce(0, pos.y * -speed, 0);
        //    //pos.y -= speed;
        //}

        //transform.position = new Vector2(
        //    Mathf.Clamp(transform.position.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
        //    Mathf.Clamp(transform.position.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y)
        //    );

        //transform.position = new Vector3(Mathf.Clamp(pos.x, LeftBottom.x + transform.localScale.x, RightTop.x - transform.localScale.x),
        //   Mathf.Clamp(pos.y, LeftBottom.y + transform.localScale.y, RightTop.y - transform.localScale.y), pos.z);

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
