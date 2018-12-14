#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

int sep = 2 ; //Pin number for Arduino output for seperation
int stg2 = 3 ; //Pin number for Arduino output for stage2
int aThreshold = 70; //Adjust this to change acceleration threshold to trigger the seperation
float delay2sep = 4000.0 ; // Adjust this to change delay before seperation 
float sep2ignition = 2000.0 ; // Adjust this to change delay for ignition 


Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(9600);

  /*if (! mma.begin()) {
    Serial.println("Couldnt start"); //Checks to see if the accelerometer is connected 
    while (1);
  }
  Serial.println("MMA8451 found!"); //Used during the testing stage to ensure there are no connection issues */
  
  mma.setRange(MMA8451_RANGE_8_G);

  sensors_event_t event ; 
  mma.getEvent(&event) ; 

  pinMode(sep, OUTPUT) ; 
  pinMode(stg2, OUTPUT) ; 
  digitalWrite(sep, HIGH); //Depending on the relay you are using this might need to be set to LOW first, test to see which pin output would close the relay first 
  digitalWrite(stg2, HIGH); 
  
  


}


void loop() {
  sensors_event_t event; 
  mma.getEvent(&event);

  float accel = sqrt( pow(event.acceleration.x, 2) + pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2) ); //Calculates aggregate acceleration of all three axis ;
  Serial.print(accel); 
  if (accel > aThreshold) { // Refer to the acceleration threshold number above, we found 70 to be enough so that the accelerometer won't go off in lab conditions 
    delay(delay2sep) ; // Sets the delay before seperation, delay can be changed above 
    digitalWrite(sep, LOW) ; // sets sep pin to HIGH 
    delay(sep2ignition) ; // waits sep2stg2
    digitalWrite(stg2, LOW) ; // sets stg2 pin to HIGH 
    

  }
  
}
