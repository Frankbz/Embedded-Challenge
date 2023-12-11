#include <Adafruit_CircuitPlayground.h>

float X, Y, Z;

bool start(){
  if ((PINF & (1<<6)) == 0){ // if not pressed
    return false;
  } 
  else { // pressed
    return true;
  }
}

void setup() {
  // set right button as input (PF6)
  DDRF &= ~(1<<6);

  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {

  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();

  Serial.print("X: ");
  Serial.print(X);
  Serial.print("  Y: ");
  Serial.print(Y);
  Serial.print("  Z: ");
  Serial.println(Z);

  delay(100);
  if (start()){
    CircuitPlayground.setPixelColor(3, 0, 128, 128);
  }
  else{
    CircuitPlayground.clearPixels();
  }
}
