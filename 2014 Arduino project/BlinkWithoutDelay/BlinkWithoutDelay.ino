/* 

Sinterklaas Map Game

1. Push a start button

2. Play an LED sequence on the map

3. Wait for pedalling. Count times that we pass the reed switch (=1 revolution), advance on the map one country at a time

 */

const int startButtonPin = 6;
const int reedSwitchPin = 7;
const int ledPins[] = {8,9,10,11,12};
const int numLeds = 5;
const long interval = 1000;           // interval at which to blink (milliseconds)
const int revolutionsPerStage = 15;

int debounceDelay = 500; // for switches--interval to ignore short button presses/reed switch open/close
long lastDebounce = 0;
int buttonState = LOW;
int mapStage = 0;
int currentRevolutions = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousReedMillis = 0; // will store last time we passed the Reed switch to allow some debouncing

void setup() {
  // set pin modes
  for (int thisPin = 0; thisPin < numLeds; thisPin++)  {
    pinMode(ledPins[thisPin], OUTPUT);      
  }
  pinMode(startButtonPin, INPUT);
  pinMode(reedSwitchPin,INPUT);
  
  // activate the pull-up resistor for buttons
  digitalWrite(reedSwitchPin,HIGH); 
  digitalWrite(startButtonPin,HIGH);
  
}

// Main program loop
void loop()
{

  buttonState = digitalRead(startButtonPin);
  
  // wait for button press to begin program proper. we won't get back to this state except on first boot or if program finishes
  if (buttonState == HIGH) {
    
    blinkLEDs();
      
      //trackProgress();
  }
  
}


void trackProgress() {
  
  int blinkState = LOW;
  unsigned long currentMillis = millis();
  unsigned int numRevolutions = 0;
  int reedState = LOW;
  
  do {
    
    currentMillis = millis();
    
    if (mapStage > 0) {
      digitalWrite(ledPins[mapStage-1], HIGH); // set the previous LED pin to ON
    }
    
    // blink the current goal LED at constant interval specified earlier
    if (currentMillis - previousMillis >= interval ) {
      // save the last time you blinked the LED 
      previousMillis = currentMillis;   
      blinkState = !blinkState;
      digitalWrite(ledPins[mapStage], blinkState);
    } 
    
    reedState = digitalRead(reedSwitchPin);
    
    if (reedState == HIGH) {
        numRevolutions++;
    }
    
    if (numRevolutions >= revolutionsPerStage) {
       mapStage++;
       numRevolutions = 0;
    }
     
  } while (mapStage < numLeds);
  
}

// perform a simple welcome sequence to indicate we are ready to start pedalling
void blinkLEDs() {
        
   // flash the LEDs twice
   for (int k = 0; k < 2; k++) {
     for (int l = 0; l < numLeds; l++) {
         digitalWrite(ledPins[l], HIGH);
     }
     delay(100);
     for (int m = 0; m < numLeds; m++) {
         digitalWrite(ledPins[m], LOW);
     }
   }

}
