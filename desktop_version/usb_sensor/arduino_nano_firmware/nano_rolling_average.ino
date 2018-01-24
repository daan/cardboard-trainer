

int playhead = 0; // Position
int array_length;
int average_speed;
float array_speed[100];

long first_hit_time;
long second_hit_time;
long duration;
long last_send_time = 0;


float rotation_speed;
float average_rotation_speed;

boolean first_hit = true;
boolean detectState = false;
boolean lastDetectState = false;

void setup(void)
{


  // sensor input
  pinMode(A3, INPUT_PULLUP);
    pinMode(13, OUTPUT);

  Serial.begin(9600);
  


}

void loop()
{
  
  
  pollIR(); // IR sensor
  
  //Every 5 seconds, displaying the data
  if (millis() - last_send_time > 2000){

    

//Serial.print("Average :");
Serial.println(calculate_average());


    last_send_time = millis();
  }  
}



void pollIR() {
int sensor = analogRead(A3);


  if (sensor < 900 ) {
    detectState = true;
    if (detectState != lastDetectState) {
      // run the first time reflection is detected

        lastDetectState = true;

        
        delay(10);
        digitalWrite(13, HIGH);
        
        // Calculating the duration between two detections
        if(first_hit){
          first_hit_time = millis();
          first_hit = false;
        }
        else{
          second_hit_time = millis();
          first_hit = true; 
        }
        
        if(second_hit_time >= first_hit_time){
          duration = (second_hit_time - first_hit_time);
        }
        
        else if(second_hit_time!= 0 && first_hit_time >= second_hit_time){
          duration = (first_hit_time - second_hit_time);
        }
  

        Speed_Data();
      
    }
    else {
      // here we are seeing the same reflection over several frames
      // turn test LED on to give visual indication of a positive reflection
      digitalWrite(13, HIGH);
     
    }
  }
  else {
    detectState = false;
    lastDetectState = false;
    digitalWrite(13, LOW);
    
    delay(10);
    
  }
}

void Speed_Data(){
  if (duration!=0){
    add_value_to_array(calculate_speed(duration,21));
    array_length++;
//    Serial.print("Speed 00 ");   
//    Serial.println(array_speed[0]);
//    Serial.print("Speed 01 ");   
//    Serial.println(array_speed[1]);
//    Serial.print("Speed 02 ");   
//    Serial.println(array_speed[2]);
//    Serial.print("Speed 03 ");   
//    Serial.println(array_speed[3]);
//    Serial.print("Speed 04 ");   
//    Serial.println(array_speed[4]);
//    Serial.print("Speed 05 ");   
//    Serial.println(array_speed[5]);
//    Serial.println();
//    Serial.println("/////////////////////////////////////////");
  }  
}


float calculate_speed(float duration, int radius){
  float rotation_speed;
  rotation_speed = (2*PI*radius*10)/(duration);
  duration = 0;
  return rotation_speed;
}
    
  
void initialize_array() {
    for(int i=0; i < array_length; i++) array_speed[i] = 0;
    array_length = 0;
}


void add_value_to_array(float value) {
    array_speed[array_length] = value;    
}


float calculate_average() {
  float sum = 0; 
  float average = 0;
  for(int i=0; i < array_length; i++) sum += array_speed[i];
  average = sum/array_length;
  if(array_length == 0){
    average = 0;}
  initialize_array();
  return average;
}
