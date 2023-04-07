using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyObjectManager : MonoBehaviour
{
    [SerializeField] private GameObject EnemyScale;
    [SerializeField] private float speed;
    [SerializeField] private float max_siz;

    private bool isInsideCamera = false;

    // Start is called before the first frame update
    void Start()
    {

    }

    private void Update()
    {
        
    }

    private IEnumerator ScaleUp()
    {
        for (float i = 0; i <= max_siz; i += speed)
        {
            EnemyScale.transform.localScale = new Vector3(i, i, i);
            yield return new WaitForSeconds(speed);
        }
    }

    private void OnBecameVisible()
    {
        StartCoroutine("ScaleUp");
    }
}
