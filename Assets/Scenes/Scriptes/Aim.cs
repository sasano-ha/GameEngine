using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Aim : MonoBehaviour
{
    public static Aim instance;

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
        // カーソルを非表示にする。
        Cursor.visible = false;

        // カーソル移動の制限（画面内）
        Cursor.lockState = CursorLockMode.Confined;

        // 画像を半透明にする
        gameObject.GetComponent<Image>().color = new Color(1, 1, 1, 0.8f);

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
