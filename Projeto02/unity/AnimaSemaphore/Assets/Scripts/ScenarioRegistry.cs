using System;
using UnityEngine;
using UnityEngine.SceneManagement;


[CreateAssetMenu(menuName ="AnimaSemaphore/ScenarioRegistry")]
public class ScenarioRegistry : ScriptableObject
{
    [Serializable]
    public struct ScenarioInfo
    {
        public string scenarioName;
        public string sceneName;
    }
    
    [SerializeField] ScenarioInfo[] scenarios;

    public void LoadScenario(string name)
    {
        foreach(ScenarioInfo scenario in scenarios)
        {
            if(scenario.scenarioName == name)
            {
                SceneManager.LoadScene(scenario.sceneName);
            }
        }
    }

    
}
