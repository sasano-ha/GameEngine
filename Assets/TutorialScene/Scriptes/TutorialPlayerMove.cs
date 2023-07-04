using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TutorialPlayerMove : MonoBehaviour
{
    // �}�E�X
    private Vector3 mouse;

    // �^�[�Q�b�g
    private Vector3 target;

    // player��HP
    private int playerHp;

    // ���@�̍��W�̓��ꕨ
    public Vector3 pos;

    [SerializeField] private float speed = 0.1f;

    public float moveForceMultiplier;

    // �����ړ����ɋ@������E�Ɍ�����g���N
    public float yawTorqueMagnitude = 30.0f;

    // �����ړ����ɋ@����㉺�Ɍ�����g���N
    public float pitchTorqueMagnitude = 90.0f;

    // �����ړ����ɋ@�̂����E�ɌX����g���N
    public float rollTorqueMagnitude = 30.0f;

    // �o�l�̂悤�Ɏp�������ɖ߂��g���N
    public float restoringTorqueMagnitude = 100.0f;

    private new Rigidbody rigidbody;

    private bool MoveFlag = false;

    public bool ShotFlag = false;

    public float MoveTimer = 0;

    public void Awake()
    {
        rigidbody = GetComponent<Rigidbody>();

        // �o�l�����͂ł����h�ꑱ����̂�h�����߁AangularDrag��傫�߂ɂ��Ă���
        rigidbody.angularDrag = 20.0f;
    }


    // Start is called before the first frame update
    void Start()
    {
        // �������ɑ̗͂��w�肵�Ă���
        playerHp = 3;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        Tu_move();
    }

    private void Update()
    {
        if(Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.D))
        {
            MoveFlag = true;
        }
    }

    private void Tu_move()
    {
        if (MoveFlag == true)
        {
            MoveTimer += 1.0f;

            // ������-1����1�͈̔͂�float�^�ŕԂ��B
            float x = Input.GetAxisRaw("Horizontal");
            float y = Input.GetAxisRaw("Vertical");

            // x��y��speed���|����B
            rigidbody.AddForce(x * speed, y * speed, 0);

            // vector��0�ɂ���
            Vector3 moveVector = Vector3.zero;


            rigidbody.AddForce(moveForceMultiplier * (moveVector - rigidbody.velocity));

            Vector3 rotationTorque = new Vector3(-y * pitchTorqueMagnitude, x * yawTorqueMagnitude, -x * rollTorqueMagnitude);

            Vector3 right = transform.right;
            Vector3 up = transform.up;
            Vector3 forward = transform.forward;
            Vector3 restoringTorque = new Vector3(forward.y - up.z, right.z - forward.x, up.x - right.y) * restoringTorqueMagnitude;

            rigidbody.AddTorque(rotationTorque + restoringTorque);
        }

        if (MoveTimer > 300)
        {
            ShotFlag = true;
        }
    }
}