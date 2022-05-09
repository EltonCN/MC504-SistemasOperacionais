using System.Collections;
using System.Collections.Generic;
using System;

using UnityEngine;

[CreateAssetMenu(menuName ="AnimaSemaphore/Screenplay")]
public class Screenplay : ScriptableObject
{
    [SerializeField][TextArea(3, 5)] string screenplay;
    string scenarioName;
    int scenarioSize;
    List<(int, string, int)> parsedScreenplay;

    void OnValidate()
    {
        parseScreenplay();
        Debug.Log("Screenplay parse complete");
    }

    public void parseScreenplay()
    {   
        string[] lines = screenplay.Split('\n');

        parsedScreenplay = new List<(int, string, int)>();

        string[] scenarioInfo = lines[0].Replace("\n", "").Replace("\r", "").Split(' ');
        
        if(scenarioInfo[0].Equals("SCENARIO") == false)
        {
            Debug.LogException(new ArgumentException("Scenario screenplay must start with 'SCENARIO'.") , this);
        }

        scenarioName = scenarioInfo[1];
        scenarioSize = int.Parse(scenarioInfo[2]);

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

    public List<(int, string, int)> ParsedScreenplay
    {
        get
        {
            return this.parsedScreenplay;
        }
    }

    public string ScenarioName
    {
        get
        {
            return this.scenarioName;
        }
    }

    public int ScenarioSize
    {
        get
        {
            return this.scenarioSize;
        }
    }

    public string ScreenplayText
    {
        set
        {
            this.screenplay = value;
            parseScreenplay();
        }

        get
        {
            return this.screenplay;
        }
    }
}