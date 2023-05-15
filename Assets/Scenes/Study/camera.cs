using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class camera : MonoBehaviour
{

    private float timer = 0;

    [SerializeField] Image image_;

    public bool flag = false;

    private void Awake()
    {
        //timer = 0;
        image_.enabled = false;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        timer++;
        if(timer >= 600)
        {
            flag = true;  
        }

        if(flag == true)
        {
            image_.enabled = true;
        }
    }
}
