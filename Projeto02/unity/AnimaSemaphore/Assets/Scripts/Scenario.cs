using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Scenario : MonoBehaviour
{
    [SerializeField] List<SemaphoreController> semaphores;
    [SerializeField] List<Character> characters;
    [SerializeField] float startWaitTime = 2f;
    [SerializeField] [TextArea(3, 5)] string screenplay;
    

    List<(int, string, int)> parsedScreenplay;

    int currentLine;



    void Start()
    {
        currentLine = -1;

        parseScreenplay();
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

    void parseScreenplay()
    {   
        string[] lines = screenplay.Split('\n');

        parsedScreenplay = new List<(int, string, int)>();


        for(int i = 1; i< lines.Length; i++)
        {
            int characterId = -1;
            string action = "";
            int objectId = -1;

            string[] elements = lines[i].Replace("\n", "").Replace("\r", "").Split(' ');

            if(elements.Length == 1 && elements[0] == "")
            {
                continue;
            }

            try
            {
                characterId = int.Parse(elements[0]);
                action = elements[1];

                if(elements.Length == 3)
                {
                    objectId = int.Parse(elements[2]);
                }
                
                parsedScreenplay.Add((characterId, action, objectId));
            }
            finally
            {
                
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

        characters[characterId].CharacterAction(actionId, objectId);
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