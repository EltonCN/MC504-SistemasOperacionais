using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Scenario : MonoBehaviour
{
    [SerializeField] List<SemaphoreController> semaphores;
    [SerializeField] List<Character> characters;
    [SerializeField] float startWaitTime = 2f;
    [SerializeField] Screenplay screenplay;
    

    List<(int, string, int)> parsedScreenplay;

    int currentLine;



    void Start()
    {
        currentLine = -1;
        parsedScreenplay = screenplay.ParsedScreenplay;
    }

    void Update()
    {
        if(Time.time < startWaitTime)
        {
            return;
        }

        if(!ActionPlaying)
        {
            currentLine += 1;

            if(currentLine < parsedScreenplay.Count)
            {
                RunAction(parsedScreenplay[currentLine].Item1, parsedScreenplay[currentLine].Item2, parsedScreenplay[currentLine].Item3);
            }
        }
    }

   

    
    public void RunAction(int characterId, string actionId, int objectId)
    {
        switch(actionId)
        {
            case "WT":
                semaphores[objectId].Wait();
            break;

            case "US":
                semaphores[objectId].Using();
            break;

            case "PT":
                semaphores[objectId].Post();
            break;
        }

        if(characterId > 0)
        {
            Debug.Log("Action: "+characters[characterId].gameObject.name+" "+actionId+" "+objectId.ToString());

            characters[characterId].CharacterAction(actionId, objectId);
        }
        
    }

    bool ActionPlaying
    {
        get
        {
            foreach(Character c in characters)
            {
                if(c.Playing())
                {
                    return true;
                }
            }

            foreach(SemaphoreController s in semaphores)
            {
                if(s.Playing)
                {
                    return true;
                }
            }

            return false;
        }
    }

}