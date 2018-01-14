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
	}

	void OnMouseDown() {
		mPlayer.playbackSpeed += 0.1f;
		string s = "playback speed " + mPlayer.playbackSpeed;
		SetText(s);
		Debug.Log( mPlayer.playbackSpeed);
	}
}
