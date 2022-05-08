using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;

public class Character : MonoBehaviour
{
    [Serializable]
    public struct Action
    {
        public string name;
        public PlayableDirector director;
    }
    
    [SerializeField] Action[] actions;
    

    public virtual void CharacterAction(string actionID, int objectId)
    {

        foreach(Action action in actions)
        {
            if(action.name == actionID)
            {
                if(action.director != null)
                {
                    
                    action.director.Play();
                }
                break;
            }
        }
    }

    public virtual bool Playing()
    {
        foreach(Action action in actions)
        {
            if(action.director == null)
            {
                continue;
            }

            if(action.director.state == PlayState.Playing)
            {
                return true;
            }
        }

        return false;
    }
}
