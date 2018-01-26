using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class sphereScript : MonoBehaviour {

	public UnityEngine.Video.VideoPlayer mPlayer;

	public GameObject statusText;

	// Use this for initialization
	void Start () {
		mPlayer = gameObject.GetComponent<UnityEngine.Video.VideoPlayer>();
		
		string s = "playback speed posible" + mPlayer.canSetPlaybackSpeed;
		SetText(s);
				Debug.Log( mPlayer.playbackSpeed);

	}

	void SetText(string s) {
		statusText.GetComponent<TextMesh>().text = s;
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown(0)) {
			mPlayer.playbackSpeed += 0.1f;
			string s = "playback speed " + mPlayer.playbackSpeed;
			SetText(s);
			Debug.Log( mPlayer.playbackSpeed);
		}

		// decode in ASCII
		// (a - 48.0) / 10.0f;
		// (0)48 == 0 ; v(118) = 7.0;
		// 49 == 0.1 . D == 2.0

		if(Input.inputString!="")
         {
             char last=Input.inputString[Input.inputString.Length - 1];
			 int ascii = (int)last; 
			 if( ascii >= 48) {
				 float speed = (float)(ascii-48) / 10.0f;
				 Debug.Log(speed);
				 mPlayer.playbackSpeed = speed;
			 }
         }

	}

	void OnMouseDown() {
		mPlayer.playbackSpeed += 0.1f;
		string s = "playback speed " + mPlayer.playbackSpeed;
		SetText(s);
		Debug.Log( mPlayer.playbackSpeed);
	}
}
