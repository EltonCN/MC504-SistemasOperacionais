using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SimpleFileBrowser;

public class LoadFile : MonoBehaviour
{
    [SerializeField] ScenarioRegistry registry;
    [SerializeField] Screenplay screenplay;

    public void AskFileAndLoad()
    {
        StartCoroutine( ShowLoadDialogCoroutine() );
    }

    IEnumerator ShowLoadDialogCoroutine()
    {
        yield return FileBrowser.WaitForLoadDialog( FileBrowser.PickMode.Files, false, null, null, "Load screenplay", "Load" );

        if(FileBrowser.Success)
        {
            string filepath = FileBrowser.Result[0];
            screenplay.ScreenplayText = System.IO.File.ReadAllText(filepath);
            registry.LoadScenario(screenplay.ScenarioName);
        }
    }    
}
