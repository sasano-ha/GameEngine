using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class test : MonoBehaviour
{
    //�X�^�[�g�ƏI���̖ڈ�
    public Transform startMarker;
    public Transform endMarker;

    // �X�s�[�h
    public float speed = 1.0F;

    //��_�Ԃ̋���������
    private float distance_two;

    void Start()
    {

    }

    void Update()
    {
        speed += Time.deltaTime;
        transform.position = sineinout(speed, 1.0f, startMarker.position, endMarker.position);
    }

    public static Vector3 sineinout(float t, float totaltime, Vector3 min, Vector3 max)
    {
        max -= min;
        return -max / 2 * (Mathf.Cos(t * Mathf.PI / totaltime) - 1) + min;
    }
}
