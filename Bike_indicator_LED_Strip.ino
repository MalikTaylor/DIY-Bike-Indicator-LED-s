#include <FastLED.h>

#define L_LED_PIN     6

#define NUM_OF_LED    3
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

#define R_LED_PIN     3
CRGB leftIndicator[NUM_OF_LED];
CRGB rightIndicator[NUM_OF_LED]; 

//Buttons
const int leftTurnButtonPin = 8;
const int rightTurnButtonPin = 2;

//State of the Button
int leftTurnButtonState = 0;
int rightTurnButtonState = 0;

//LED's
const int indicatorLEDCount = 3;
//const int brakeLEDCount = 3;

int leftIndicatorPin = 6;
int rightIndicatorPin = 3;

const int duration = 3;

void setup() {

  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, L_LED_PIN, COLOR_ORDER>(leftIndicator, NUM_OF_LED).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, R_LED_PIN, COLOR_ORDER>(rightIndicator, NUM_OF_LED).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  Serial.begin(9600);
  pinMode(leftTurnButtonPin, INPUT);
  pinMode(rightTurnButtonPin, INPUT);
 
}

CRGB Scroll(int pos) {
  CRGB color (0,0,0);
  if(pos < 85) {
    color.g = 0;
    color.r = ((float)pos / 85.0f) * 255.0f;
    color.b = 255 - color.r;
  } else if(pos < 170) {
    color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
    color.r = 255 - color.g;
    color.b = 0;
  } else if(pos < 256) {
    color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
    color.g = 255 - color.b;
    color.r = 1;
  }
  return color;
}

void Clear(String indicator_LED_side){
  if(indicator_LED_side == "right"){
    for(int i = 0; i < NUM_OF_LED; i++){
      rightIndicator[i] = CHSV( 0, 0, 0);
    }
  }else{
    for(int i = 0; i < NUM_OF_LED; i++){
     leftIndicator[i] = CHSV( 0, 0, 0);
    }
  }
  delay(500);
  FastLED.show();
 
}

void loop() {

    
  leftTurnButtonState = digitalRead(leftTurnButtonPin);
  rightTurnButtonState = digitalRead(rightTurnButtonPin);

  Serial.print(rightTurnButtonState);

  //Left Turn
  if(leftTurnButtonState == HIGH){
    indicateLeft();
  }
  
  //Right Turn
  if(rightTurnButtonState == HIGH){
      Serial.print("Right Indicator button pressed");
      indicateRight();
  }

  FastLED.clear();
}

void indicateLeft(){
  Serial.print("left");
  for(int d = 0; d <= 2; d++){
    for(int i = 0; i < NUM_OF_LED; i++) {  
      leftIndicator[i] = CRGB::Yellow;  
      delay(500);
      FastLED.show();
      FastLED.clear();
    }
  }
  Clear("left");
}

void indicateRight(){
  Serial.print("right");
  for(int d = 0; d <= 2; d++){
    for(int i = 0; i < NUM_OF_LED; i++) {  
      rightIndicator[i] = CRGB::Yellow;  
      delay(500);
      FastLED.show();
      FastLED.clear();
    }
  }
  Clear("right");
}
