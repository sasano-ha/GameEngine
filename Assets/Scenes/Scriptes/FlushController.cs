using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FlushController : MonoBehaviour
{
    Image image;

    // Start is called before the first frame update
    void Start()
    {
        image = GetComponent<Image>();
        image.color = Color.clear;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        if (Input.GetMouseButtonDown(0))
        {
            this.image.color = new Color(0.5f, 0f, 0f, 0.5f);
        }
        else
        {
            this.image.color = Color.Lerp(this.image.color, Color.clear, Time.deltaTime);
        }
    }
}
