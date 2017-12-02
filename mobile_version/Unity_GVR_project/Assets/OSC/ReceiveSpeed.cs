using UnityEngine;
using System.Collections;

public class ReceiveSpeed : MonoBehaviour {
    
   	public OSC osc;

	// Use this for initialization
	void Start () {
	   osc.SetAddressHandler("/speed", OnReceiveSpeed);
    }
	// Update is called once per frame
	void Update () {
	
	}
	void OnReceiveSpeed(OscMessage message){
		float x = message.GetFloat(0);
	}
}
