using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;

public class SemaphoreController : MonoBehaviour
{
    [SerializeField] PlayableDirector waitDirector;
    [SerializeField] PlayableDirector postDirector;
    [SerializeField] PlayableDirector usingDirector;
    [SerializeField] GameObject lamp;
    [SerializeField] GameObject lampOff;
    [SerializeField] GameObject waitingEffect;


    // Start is called before the first frame update
    void Start()
    {
        lamp.SetActive(false);
        lampOff.SetActive(true);
        waitingEffect.SetActive(false);
    }

    public void Wait()
    {
        waitDirector.Play();
    }

    public void Post()
    {
        postDirector.Play();
    }

    public void Using()
    {
        usingDirector.Play();
    }

    public bool Playing
    {
        get
        {
            bool playing = waitDirector.state == PlayState.Playing;
            playing = playing || postDirector.state == PlayState.Playing;
            playing = playing ||  usingDirector.state == PlayState.Playing;
            return playing;
        }
    }
}
