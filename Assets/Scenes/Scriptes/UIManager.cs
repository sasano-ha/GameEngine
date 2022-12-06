using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class UiManager : MonoBehaviour
{

	//作成した照準のImageを紐付けしておく。
	[SerializeField]
	RectTransform reticleRt;

	//照準のImageの親キャンバスを紐付けしておく。
	[SerializeField]
	RectTransform reticleCanvasRt;

	Camera mainCamera;


	//一応キャッシュしておく。
	PointerEventData pointer = new PointerEventData(EventSystem.current);
	EventSystem eventSystem;

	//タッチ位置のUI要素が返されるList。再確保されないようにキャパシティは、やや多めに指定しておく。
	List<RaycastResult> isPointerOverUIResults = new List<RaycastResult>(10);


	//1回しか使わないので良いかも知れないが、一応定数化。
	static readonly string EnemyStr = "Enemy";

	Vector3 screenCenterPosition;

	Coroutine aimingSmoothDamp;
	Vector3 touchPosition;
	Vector3 reticleVelocity;

	//最終射撃目標位置と現在の射撃目標位置が、この距離以下になるとエイミングを終了する(sqrMagnitude)。
	static readonly float EndAimingSqr = 0.1f;
	//【任意の値】射撃目標の敵との判定を取るRayの最大距離。
	static readonly float CheckTouchMaxDistance = 100.0f;

	//敵等のエイム時に優先したいオブジェクトのレイヤー。
	//SerializeField指定して、インスペクターから設定しても良い。
	//コードで複数レイヤーを指定する場合は、「1 << LayerMask.NameToLayer("A") | 1 << LayerMask.NameToLayer("B")」みたいな感じで「|」で区切る。
	LayerMask checkTouchTargetLayer;

	Ray checkTouchRay;

	//Rayの判定の結果。一番手前の物だけで良いので1のみ。
	RaycastHit[] checkTouchResults = new RaycastHit[1];

	//射撃目標の位置。
	Vector3 targetPosition;

	//照準(画像)の位置。
	Vector3 reticlePosition;

	//Screen Space - Cameraのキャンバス用に変換した照準の位置。
	Vector2 reticleLocalPosition;

	//SmoothDampを完了する大体の長さ(大体なのでピッタリには終わらない)。
	static readonly float AimingSmoothTime = 0.2f;

	//SmoothDampする最大速度。多分deltaTimeが掛かるので、想像の100倍程の大きさで設定。
	static readonly float AimingMaxSpeed = 3000.0f;

	//【任意の値】カメラから射撃目標位置への相対距離。
	static readonly float CameraToTargetRelativeDistance = 30.0f;

	//コルーチンのウェイト。LateUpdate相当。描画系は、このタイミングで更新すれば良い模様。
	static readonly WaitForEndOfFrame EndOfFrameWait = new WaitForEndOfFrame();



	void Awake()
	{


		eventSystem = EventSystem.current;
		checkTouchTargetLayer = 1 << LayerMask.NameToLayer(EnemyStr);
		mainCamera = Camera.main;

		//デフォルトの照準位置を計算。
		screenCenterPosition.Set(Screen.width / 2, Screen.height / 2, CameraToTargetRelativeDistance);

		//リセット時には、照準位置に適用しておく。
		touchPosition = screenCenterPosition;
		reticlePosition = screenCenterPosition;


	}


	void Update()
	{
		if (Input.GetMouseButton(0))
		{
			if (IsPointerOverUI())
				return;

			if (aimingSmoothDamp != null)
			{
				StopCoroutine(aimingSmoothDamp);
			}
			aimingSmoothDamp = StartCoroutine(AimingSmoothDamp());
		}
	}


	IEnumerator AimingSmoothDamp()
	{
		touchPosition = Input.mousePosition;
		touchPosition.z = CameraToTargetRelativeDistance;

		while (EndAimingSqr < (touchPosition - reticlePosition).sqrMagnitude)
		{
			//連続して実行した時(画面押しっぱなし時)、先にウェイトを入れないとカクつく。
			yield return EndOfFrameWait;

			reticlePosition = Vector3.SmoothDamp(reticlePosition, touchPosition, ref reticleVelocity, AimingSmoothTime, AimingMaxSpeed);
			RectTransformUtility.ScreenPointToLocalPointInRectangle(reticleCanvasRt, reticlePosition, mainCamera, out reticleLocalPosition);

			reticleRt.localPosition = reticleLocalPosition;
		}

		aimingSmoothDamp = null;
	}

	//射撃する前にコレを呼んで、照準の位置から射撃目標位置へ変換しておく(照準の先に敵が居る場合はソチラのZ座標を優先する)。
	void CheckTargetPosition()
	{
		checkTouchRay = mainCamera.ScreenPointToRay(reticlePosition);
		if (0 < Physics.RaycastNonAlloc(checkTouchRay, checkTouchResults, CheckTouchMaxDistance, checkTouchTargetLayer))
		{
			targetPosition = checkTouchResults[0].point;
		}
		else
		{
			targetPosition = mainCamera.ScreenToWorldPoint(reticlePosition);
		}
	}

	//タップ(クリック)位置にボタン等のRaycast Targetが有効なUI要素が1つでもあればtrueを返す。
	bool IsPointerOverUI()
	{
		pointer.position = Input.mousePosition;
		eventSystem.RaycastAll(pointer, isPointerOverUIResults);
		return 0 < isPointerOverUIResults.Count;
	}
}