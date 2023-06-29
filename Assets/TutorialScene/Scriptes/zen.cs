using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class zen : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        GetComponent<RectTransform>().SetAsLastSibling();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
