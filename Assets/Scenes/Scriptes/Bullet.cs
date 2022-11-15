using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // ’e‚Ìƒ[ƒ‹ƒhÀ•W‚ðŽæ“¾
        Vector3 pos = transform.position;

        // ³–Ê‚É‚Ü‚Á‚·‚®”ò‚Ô
        pos.z += 0.05f;

        // ’e‚ÌˆÚ“®
        transform.position = new Vector3(pos.x, pos.y, pos.z);

        // ˆê’è‹——£i‚ñ‚¾‚çÁ–Å‚·‚é
        if(pos.z >= 20)
        {
            Destroy(this.gameObject);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Enemy")
        {
            other.GetComponent<Enemy>().Damage();
        }
        Destroy(this.gameObject);
    }
}
