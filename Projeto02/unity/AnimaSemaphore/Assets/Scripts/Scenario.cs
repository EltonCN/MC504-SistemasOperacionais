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

        Debug.Log(screenplay.ScreenplayText);
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
                if(semaphores[objectId]!= null)
                {
                    semaphores[objectId].Wait();
                } 
            break;

            case "US":
                if(semaphores[objectId]!= null)
                {
                    semaphores[objectId].Using();
                }
            break;

            case "PT":
                if(semaphores[objectId]!= null)
                {
                    semaphores[objectId].Post();
                }
            break;

            default:
                if(characterId >= 0)
                {           
                    Debug.Log("Action "+currentLine.ToString()+": "+characterId.ToString()+" "+actionId+" "+objectId.ToString());
                }
            break;
        }

        if(characterId >= 0)
        {
            if(characters[characterId] != null)
            {
                characters[characterId].CharacterAction(actionId, objectId);
            }
            
        }
        
    }

    bool ActionPlaying
    {
        get
        {
            foreach(Character c in characters)
            {
                if(c == null)
                {
                    continue;
                }
                if(c.Playing())
                {
                    return true;
                }
            }

            foreach(SemaphoreController s in semaphores)
            {
                if(s == null)
                {
                    continue;
                }
                
                if(s.Playing)
                {
                    return true;
                }
            }

            return false;
        }
    }

}