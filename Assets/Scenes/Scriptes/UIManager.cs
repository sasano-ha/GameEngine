using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class UiManager : MonoBehaviour
{

	//�쐬�����Ə���Image��R�t�����Ă����B
	[SerializeField]
	RectTransform reticleRt;

	//�Ə���Image�̐e�L�����o�X��R�t�����Ă����B
	[SerializeField]
	RectTransform reticleCanvasRt;

	Camera mainCamera;


	//�ꉞ�L���b�V�����Ă����B
	PointerEventData pointer = new PointerEventData(EventSystem.current);
	EventSystem eventSystem;

	//�^�b�`�ʒu��UI�v�f���Ԃ����List�B�Ċm�ۂ���Ȃ��悤�ɃL���p�V�e�B�́A��⑽�߂Ɏw�肵�Ă����B
	List<RaycastResult> isPointerOverUIResults = new List<RaycastResult>(10);


	//1�񂵂��g��Ȃ��̂ŗǂ������m��Ȃ����A�ꉞ�萔���B
	static readonly string EnemyStr = "Enemy";

	Vector3 screenCenterPosition;

	Coroutine aimingSmoothDamp;
	Vector3 touchPosition;
	Vector3 reticleVelocity;

	//�ŏI�ˌ��ڕW�ʒu�ƌ��݂̎ˌ��ڕW�ʒu���A���̋����ȉ��ɂȂ�ƃG�C�~���O���I������(sqrMagnitude)�B
	static readonly float EndAimingSqr = 0.1f;
	//�y�C�ӂ̒l�z�ˌ��ڕW�̓G�Ƃ̔�������Ray�̍ő勗���B
	static readonly float CheckTouchMaxDistance = 100.0f;

	//�G���̃G�C�����ɗD�悵�����I�u�W�F�N�g�̃��C���[�B
	//SerializeField�w�肵�āA�C���X�y�N�^�[����ݒ肵�Ă��ǂ��B
	//�R�[�h�ŕ������C���[���w�肷��ꍇ�́A�u1 << LayerMask.NameToLayer("A") | 1 << LayerMask.NameToLayer("B")�v�݂����Ȋ����Łu|�v�ŋ�؂�B
	LayerMask checkTouchTargetLayer;

	Ray checkTouchRay;

	//Ray�̔���̌��ʁB��Ԏ�O�̕������ŗǂ��̂�1�̂݁B
	RaycastHit[] checkTouchResults = new RaycastHit[1];

	//�ˌ��ڕW�̈ʒu�B
	Vector3 targetPosition;

	//�Ə�(�摜)�̈ʒu�B
	Vector3 reticlePosition;

	//Screen Space - Camera�̃L�����o�X�p�ɕϊ������Ə��̈ʒu�B
	Vector2 reticleLocalPosition;

	//SmoothDamp�����������̂̒���(��̂Ȃ̂Ńs�b�^���ɂ͏I���Ȃ�)�B
	static readonly float AimingSmoothTime = 0.2f;

	//SmoothDamp����ő呬�x�B����deltaTime���|����̂ŁA�z����100�{���̑傫���Őݒ�B
	static readonly float AimingMaxSpeed = 3000.0f;

	//�y�C�ӂ̒l�z�J��������ˌ��ڕW�ʒu�ւ̑��΋����B
	static readonly float CameraToTargetRelativeDistance = 30.0f;

	//�R���[�`���̃E�F�C�g�BLateUpdate�����B�`��n�́A���̃^�C�~���O�ōX�V����Ηǂ��͗l�B
	static readonly WaitForEndOfFrame EndOfFrameWait = new WaitForEndOfFrame();



	void Awake()
	{


		eventSystem = EventSystem.current;
		checkTouchTargetLayer = 1 << LayerMask.NameToLayer(EnemyStr);
		mainCamera = Camera.main;

		//�f�t�H���g�̏Ə��ʒu���v�Z�B
		screenCenterPosition.Set(Screen.width / 2, Screen.height / 2, CameraToTargetRelativeDistance);

		//���Z�b�g���ɂ́A�Ə��ʒu�ɓK�p���Ă����B
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
			//�A�����Ď��s������(��ʉ������ςȂ���)�A��ɃE�F�C�g�����Ȃ��ƃJ�N���B
			yield return EndOfFrameWait;

			reticlePosition = Vector3.SmoothDamp(reticlePosition, touchPosition, ref reticleVelocity, AimingSmoothTime, AimingMaxSpeed);
			RectTransformUtility.ScreenPointToLocalPointInRectangle(reticleCanvasRt, reticlePosition, mainCamera, out reticleLocalPosition);

			reticleRt.localPosition = reticleLocalPosition;
		}

		aimingSmoothDamp = null;
	}

	//�ˌ�����O�ɃR�����Ă�ŁA�Ə��̈ʒu����ˌ��ڕW�ʒu�֕ϊ����Ă���(�Ə��̐�ɓG������ꍇ�̓\�`����Z���W��D�悷��)�B
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

	//�^�b�v(�N���b�N)�ʒu�Ƀ{�^������Raycast Target���L����UI�v�f��1�ł������true��Ԃ��B
	bool IsPointerOverUI()
	{
		pointer.position = Input.mousePosition;
		eventSystem.RaycastAll(pointer, isPointerOverUIResults);
		return 0 < isPointerOverUIResults.Count;
	}
}