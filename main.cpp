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
bool stage1(float X, float Y, float Z){
  return (X < 0);
}

bool stage2(float X, float Y, float Z){
  return (X > 0);
}

bool stage3(float X, float Y, float Z){
  return (Z < -8);
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
  Serial.print("Stage  ");
  Serial.println(stage);

  // 10 stage checks
  if (stage == 2){
    CircuitPlayground.setPixelColor(2, 0, 128, 128);
  }
  if (stage == 3){
    CircuitPlayground.setPixelColor(5, 0xFF0000);
  }

  delay(100);
  if (start()){
    if (stage == 0){
      if (stage1(X, Y, Z)) {stage = 1;}
    }
    if (stage == 1){
      if (stage2(X, Y, Z)) {stage = 2;}
    }
    if (stage == 2){
      if (stage3(X, Y, Z)) {stage = 3; }
    }
  }
  
}
