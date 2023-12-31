#include <Adafruit_CircuitPlayground.h>

float X, Y, Z;
int stage = 0;
float value; 
int light_value;

bool start(){
  if ((PINF & (1<<6)) == 0){ // if not pressed
    return false;
  } 
  else { // pressed
    return true;
  }
}

bool up(float X, float Y, float Z){
  return (Z > 9);
}

bool down(float X, float Y, float Z){
  return (Z < -9);
}

bool left(float X, float Y, float Z){
  return (Y > 9);
}

bool right(float X, float Y, float Z){
  return (Y < -9);
}

bool forward(float X, float Y, float Z){
  return (X > 9);
}

bool backward(float X, float Y, float Z){
  return (X < -9);
}

bool shake(float X, float Y, float Z){
  return (Y > 15 || Y < -15);
}

bool goDown(float X, float Y, float Z){
  return (Z < 12);
}

bool goUp(float X, float Y, float Z){
  return (Z > 12);
}

bool blow(float val){
  return (val > 90);
}

bool dark(float val){
  return (val < 10);
}

void setup() {
  // set right button as input (PF6)
  DDRF &= ~(1<<6);

  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  delay(100);

  value = CircuitPlayground.mic.soundPressureLevel(10);
  
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();

  light_value = CircuitPlayground.lightSensor(); // dark approaches 0
  

  Serial.print("X: ");
  Serial.print(X);
  Serial.print("  Y: ");
  Serial.print(Y);
  Serial.print("  Z: ");
  Serial.println(Z);
  Serial.print("Stage  ");
  Serial.println(stage);
  // Serial.print("Sound Sensor SPL: ");
  // Serial.println(value);
  // Serial.print("Light Sensor: ");
  // Serial.println(light_value);

  // 10 gesture stages check
  if (stage == -1){
    CircuitPlayground.setPixelColor(0, 255,   0,   0);
  }
  if (stage == -2){
    CircuitPlayground.setPixelColor(1, 128, 128,   0);
  }
  if (stage == -3){
    CircuitPlayground.setPixelColor(2,   0, 255,   0);
  }
  if (stage == -4){
    CircuitPlayground.setPixelColor(3,   0, 128, 128);
  }
  if (stage == -5){
    CircuitPlayground.setPixelColor(4,   0,   0, 255);
  }
  if (stage == -6){
    CircuitPlayground.setPixelColor(5, 0xFF0000);
  }
  if (stage == -7){
    CircuitPlayground.setPixelColor(6, 0x808000);
  }
  if (stage == -8){
    CircuitPlayground.setPixelColor(7, 0x00FF00);
  }
  if (stage == -9){
    CircuitPlayground.setPixelColor(8, 0x008080);
  }
  if (stage == -10){
    CircuitPlayground.setPixelColor(9, 0x0000FF);
  }


  if (start()){
    if (stage == 0){
      if (up(X, Y, Z)) { stage = 1; }
      if (down(X, Y, Z)) { stage = 2; }
      if (forward(X, Y, Z)) { stage = 9; }
      if (left(X, Y, Z)) { stage = 11; }
      if (backward(X, Y, Z)) { stage = 13; }
      if (right(X, Y, Z)) { stage = 15;}
      
    }
    if (stage == 1){
      if (left(X, Y, Z)) { stage = 3; }
      if (right(X, Y, Z)) { stage = 4; }
      if (forward(X, Y, Z)) { stage = 5; }
      if (backward(X, Y, Z)) { stage = 6; }
      if (goUp(X, Y, Z)) { stage = 14; }
    }
    if (stage == 2){
      if (goDown(X, Y, Z)) { stage = 7; }
    }
    if (stage == 3){
      if (down(X, Y, Z)) { stage = -1; }
    }
    if (stage == 4){
      if (down(X, Y, Z)) { stage = -2; }
    }
    if (stage == 5){
      if (down(X, Y, Z)) { stage = -3; }
    }
    if (stage == 6){
      if (down(X, Y, Z)) { stage = -4; }
    }
    if (stage == 7){
      if (left(X, Y, Z)) { stage = 8; }
    }
    if (stage == 8){
      if (shake(X, Y, Z)) { stage = -6; }
    }
    if (stage == 9){
      if (blow(value)) { stage = 10; }
    }
    if (stage == 10){
      if (shake(X, Y, Z)) { stage = -7; }
    }
    if (stage == 11){
      if (dark(light_value)) { stage = -8; }
    }
    if (stage == 12){
      if (dark(light_value)) { stage = -9; }
    }
    if (stage == 13){
      if (blow(value)) { stage = 12; }
    }
    if (stage == 14){
      if (dark(light_value)) { stage = -10; }
    }
    if (stage == 15){
      if (up(X, Y, Z)) { stage = 16; }
    }
    if (stage == 16){
      if (shake(X, Y, Z)) { stage = -5; }
    }

  }
  // else{ // This is only for testing, in project we only need to reach one gesture stage
  //   CircuitPlayground.clearPixels();
  //   stage = 0;
  // }
  
}
