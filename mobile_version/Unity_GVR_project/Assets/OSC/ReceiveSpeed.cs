using UnityEngine;
using System.Collections;

public class ReceiveSpeed : MonoBehaviour {
    
   	public OSC osc;
	public float speed;

	UnityEngine.Video.VideoPlayer mVideo;

	// Use this for initialization
	void Start () {
	   osc.SetAddressHandler("/speed", OnReceiveSpeed);
	   // connect to the video player
	   mVideo = gameObject.GetComponent<UnityEngine.Video.VideoPlayer>();
	   Debug.Log("start receive speed " );

    }
	// Update is called once per frame
	void Update () {
	
	}
	void OnReceiveSpeed(OscMessage m){
		speed = m.GetFloat(0);
		mVideo.playbackSpeed = speed;
	}
}
