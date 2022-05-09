using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Atom : Character
{
    [SerializeField] Vector3 spawnAreaMin;
    [SerializeField] Vector3 spawnAreaMax;
    [SerializeField] float waitTime = 0.5f;

    Rigidbody rb;

    float startTime;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    public override void CharacterAction(string actionID, int objectId)
    {
        switch(actionID)
        {
            case "WB":
                reset();
            break;

            case "ET":
                gameObject.layer = LayerMask.NameToLayer("WaitingBond");
                startTime = Time.time;
            break;

            case "BD":
                gameObject.layer = LayerMask.NameToLayer("Bonding");
                startTime = Time.time;
            break;

            case "ED":
                GameObject.Destroy(this.gameObject);
            break;
        }
    }

    public void reset()
    {
        gameObject.layer = LayerMask.NameToLayer("WaitingEntry");
        float x = Random.Range(spawnAreaMin.x, spawnAreaMax.x);
        float y = Random.Range(spawnAreaMin.y, spawnAreaMax.y);
        float z = Random.Range(spawnAreaMin.z, spawnAreaMax.z);

        rb.velocity = Vector3.zero;
        rb.angularVelocity = Vector3.zero;
        rb.position = new Vector3(x, y, z);
        startTime = Time.time;
    }

    public override bool Playing()
    {
        if(Time.time - startTime < waitTime)
        {
            return true;
        }
        return false;
    }
}
