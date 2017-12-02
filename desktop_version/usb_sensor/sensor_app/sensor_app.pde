import controlP5.*;
import netP5.*;
import oscP5.*;
import processing.serial.*;

ControlP5 cp5;
OscP5 oscP5;
NetAddress gRemoteLocation;

String gRemoteIp = "127.0.0.1";
int gRemotePort = 12000;
int gLocalPort = 12021;

Serial gSerial;  
String gFromSerial;
int kLF = 10;

int gSpeed = 0;

Knob gSpeedKnob;
Toggle gRecordToggle;

boolean gRecording = false;
StringList gLog = new StringList();
long gRecordingStart = 0;


void sendSpeed(int speed) {
  OscMessage m = new OscMessage("/speed");
  m.add(speed); 
  oscP5.send(m, gRemoteLocation); 
}

void connectSerial(String s) {
  try{
    gSerial = new Serial(this, s, 115200);
  } catch(Exception e){
    println(e.getMessage());
  }
  if ( gSerial != null) {
    println("serial is opened");
  } else {
    println("not connected to serial");
  }
}


void setup() {
  size(340,280);

  gRemoteLocation = new NetAddress(gRemoteIp,gRemotePort);
  oscP5 = new OscP5(this, gLocalPort);

  
  cp5 = new ControlP5(this);

  gSpeedKnob = cp5.addKnob("speed")
               .setRange(0,4)
               .setValue(1)
               .setPosition(30,50)
               .setRadius(100)
               .setDragDirection(Knob.HORIZONTAL)
               ;

  gRecordToggle = cp5.addToggle("record")
    .setPosition(230,50)
    .setSize(39,20)
    .align(ControlP5.CENTER, CENTER, CENTER, CENTER)
    ;


  setupConnectionControls();



  // connectSerial(Serial.list()[Serial.list().length-1]);
  
  
}







void draw() {
  background(0);
  
  if (gSerial == null) {
     if (keyPressed) {
       if (key=='a' || key=='a') {
         setSpeed( gSpeedKnob.getValue() - 0.01 );
       } else if (key=='d' || key=='D') {
         setSpeed( gSpeedKnob.getValue() + 0.01 );
       }
     }
  }
  
  if (gSerial != null) {
    while (gSerial.available() > 0) {
      String s = gSerial.readStringUntil(kLF);
      if (s != null) {
        float f = float( trim(s) );
        setSpeed( f );
      }
    }
  }
}

void record(int v) {
  if( v==1 ) {
    gLog.clear();
    gRecording = true;
    gRecordingStart = millis();
  } else {
    gRecording = false;
    String[] s = gLog.array();
    String filename = "log" + month() + "-" + day() + "-" + hour() + "-" + minute() + "-" + second() + ".csv";   
    
    saveStrings(filename, s);
  }
}

void setSpeed(float v) {
  gSpeedKnob.setValue(v);
  speed(v); 
}


void speed(float v) {
  println("a knob event: "+v);
  
  v = max(0.0, min(v, 4.0));
  
  
  if( gRecording ) {
       String l = str( (millis()-gRecordingStart)/1000.0f) + "," + v;
       gLog.append(l);
  }
  
  if (oscP5 != null) {
    OscMessage m = new OscMessage("/speed");
    m.add(v); 
    oscP5.send(m, gRemoteLocation); 
  }
}