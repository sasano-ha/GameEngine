using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class s : MonoBehaviour
{
    public float ratio;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        Vector3 target_position = PlayerMove.instance.pos;

        // ƒxƒNƒgƒ‹‚ðŽæ“¾
        var diff = target_position - transform.position;

        var target_rot = Quaternion.LookRotation(diff);

        var q = target_rot * Quaternion.Inverse(transform.rotation);

        if (q.w < 0f)
        {
            q.x = -q.x;
            q.y = -q.y;
            q.z = -q.z;
            q.w = -q.w;
        }

        var torque = new Vector3(q.x, q.y, q.z) * ratio;

        GetComponent<Rigidbody>().AddTorque(torque);
    }
}
