#include <Adafruit_CircuitPlayground.h>

float X, Y, Z;
int stage = 0;

bool start(){
  if ((PINF & (1<<6)) == 0){ // if not pressed
    return false;
  } 
  else { // pressed
    return true;
  }
}

// we can add facing direction later
bool moveLeft(float X, float Y, float Z){
  return (X>=7);
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

  if (stage == 1){
    CircuitPlayground.setPixelColor(1, 0, 128, 128);
  }

  delay(100);
  if (start()){
    if (moveLeft(X, Y, Z)) {
      stage = 1;
    }
  }
  
}
