using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialShot : MonoBehaviour
{
    // ゲームオブジェクトをインスペクターから参照するための変数
    public GameObject bullet;

    // 長押しの為のフラグ
    private bool mouseflag;

    // 間隔のタイマー
    public float timer;

    TutorialPlayerMove shot;

    // Start is called before the first frame update
    void Start()
    {
        // フラグを設定
        mouseflag = false;

        // タイマーを設定
        timer = 15.0f;
    }

    // Update is called once per frame
    void Update()
    {
        TutorialPlayerMove shot;

        GameObject barrel = GameObject.Find("StarSparrow1 1");

        shot = barrel.GetComponent<TutorialPlayerMove>();

        if (shot.ShotFlag == true)
        {
            // 左クリックを押した瞬間
            if (Input.GetMouseButtonDown(0))
            {
                // フラグを立てる
                mouseflag = true;
            }

            // 左クリックを離した瞬間
            if (Input.GetMouseButtonUp(0))
            {
                // フラグを降ろす
                mouseflag = false;
            }

            // フラグが立っていたら
            if (mouseflag == true)
            {
                // タイマーを進める
                timer--;

                if (timer <= 0)
                {
                    // 弾を生成する
                    GameObject bulletobject = Instantiate(bullet, transform.position, Quaternion.identity);

                    // 複製弾をここで生成
                    TutorialBullet bulletclone = bulletobject.GetComponent<TutorialBullet>();

                    // ここで速度を作る
                    bulletclone.SetVelocity(Aim.instance.target);

                    // タイマー元に戻す
                    timer = 15.0f;
                }
            }
        }
    }
}
