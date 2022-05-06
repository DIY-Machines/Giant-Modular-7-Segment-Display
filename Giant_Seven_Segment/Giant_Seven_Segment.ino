/*
 * Giant Modular 7 Segment Display made with a simple wooden frame, acrylic sheets and 3D printed enclosures - DIY Machines

==========

The following line numbers need modyfying if you are using an ESP8266 
 - Lines #46 through to #56
  - Line #234

Set the brightness of your display on line #59

More info and build instructions: https://www.youtube.com/diymachines

3D printed parts, wiring and technical drawings can all be found at www.diymachines.co.uk

You will need to install the Adafruit Neopixel library which can be found by searching for it in the library manager.

==========


 * SAY THANKS:

Buy me a coffee to say thanks: https://ko-fi.com/diymachines
Support thse projects on Patreon: https://www.patreon.com/diymachines

SUBSCRIBE:
■ https://www.youtube.com/channel/UC3jc4X-kEq-dEDYhQ8QoYnQ?sub_confirmation=1

INSTAGRAM: https://www.instagram.com/diy_machines/?hl=en
FACEBOOK: https://www.facebook.com/diymachines/

*/


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

unsigned long startMillis;  
volatile unsigned long currentMillis;
unsigned long elapsedMillis;
int secondsElapsedSinceRestart;
bool buttonBeenPressed = false;
String buttonThatWasPressed = "x"; 

const byte interruptPinVT = 2;  //2 on Nano, D2 on ESP8266
const byte remoteButtonA = 8;   // 8 on Nano, D1 on ESP8266
const byte remoteButtonB = 9;   //9 on Nano, D5 on ESP8266
const byte remoteButtonC = 10;  //10 on Nano D6 on ESP8266
const byte remoteButtonD = 11;  //11 on Nano, D7 on ESP8266

// Which pin on the micro controller is connected to the WS2812B / Neopixels?
#define LEDCLOCK_PIN    4  //4 on Nano, D4 on ESP8266

// How many WS2812B / Neopixels are attached to the micro controller?  (56 per character)
#define LEDCLOCK_COUNT 56

//Set brightness for the LEDs:
#define LED_BRIGHTNESS 150 //(MAX 255)


// Declare our NeoPixel objects:
Adafruit_NeoPixel stripClock(LEDCLOCK_COUNT, LEDCLOCK_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


  
  uint32_t green = stripClock.Color(0, 255, 0);
  uint32_t blue = stripClock.Color(0, 0, 255);
  uint32_t red = stripClock.Color(255, 0, 0);
  uint32_t white = stripClock.Color(255, 255, 255);
  uint32_t clockSecondColour = red;




void setup() {

  Serial.begin(9600);

  stripClock.begin();           // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripClock.show();            // Turn OFF all pixels ASAP
  stripClock.setBrightness(LED_BRIGHTNESS); // Set inital BRIGHTNESS (max = 255)

  pinMode(remoteButtonA, INPUT);
  pinMode(remoteButtonB, INPUT);
  pinMode(interruptPinVT, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPinVT), interuptingVT, RISING);


  startMillis = millis();  //initial start time
  
}

void loop() {
  
  //count how many seconds clock has been running
  countTheSeconds();

  //display the time on the LEDs
  displayTheTime();
  stripClock.show();

  //Serial.println(buttonThatWasPressed);

  if (buttonBeenPressed == true) {
    //Serial.println("Button on remote has been pressed.");
    if (buttonThatWasPressed == "A") {
      //reset the count up to 0
      buttonAPressed();
    }
    else if (buttonThatWasPressed == "B") {
      // start 3 second countdown with colours then start counting upwards
      buttonBPressed();
    }
    buttonBeenPressed = false;
  }

  //delay(100);   //a delay to slow things down during testing

}


void countTheSeconds(){
  // See how many seconds the clock has been running since last reset by remote
  currentMillis = millis();

  elapsedMillis = currentMillis - startMillis;
  //Serial.print("Elapsed millis = ");
  //Serial.println(elapsedMillis);

  secondsElapsedSinceRestart = elapsedMillis / 1000;
  //Serial.print("Seconds since last restart = ");
  //Serial.println(secondsElapsedSinceRestart);
}

void displayTheTime(){

  stripClock.clear(); //clear the clock face 

  int firstSecondDigit = secondsElapsedSinceRestart % 10; //work out the value of the first digit and then display it
  displayNumber(firstSecondDigit, 0, clockSecondColour);

  int secondSecondDigit = floor(secondsElapsedSinceRestart / 10); //work out the value for the second digit and then display it
  displayNumber(secondSecondDigit, 63, clockSecondColour);  

  }


void displayNumber(int digitToDisplay, int offsetBy, uint32_t colourToUse){
    switch (digitToDisplay){
    case 0:
    digitZero(offsetBy,colourToUse);
      break;
    case 1:
      digitOne(offsetBy,colourToUse);
      break;
    case 2:
    digitTwo(offsetBy,colourToUse);
      break;
    case 3:
    digitThree(offsetBy,colourToUse);
      break;
    case 4:
    digitFour(offsetBy,colourToUse);
      break;
    case 5:
    digitFive(offsetBy,colourToUse);
      break;
    case 6:
    digitSix(offsetBy,colourToUse);
      break;
    case 7:
    digitSeven(offsetBy,colourToUse);
      break;
    case 8:
    digitEight(offsetBy,colourToUse);
      break;
    case 9:
    digitNine(offsetBy,colourToUse);
      break;
    default:
     break;
  }
}
void beepPattern(){
  stripClock.clear(); //clear the clock face
  stripClock.fill(blue, (8 + 0), 8);
  stripClock.show();
  delay(1000);
  stripClock.fill(blue, (24 + 0), 8);
  stripClock.show();
  delay(1000);
  stripClock.fill(blue, (40 + 0), 8);
  stripClock.show();
  delay(1000);
  
/*    //This pattern would flash all three hoizontal segemtns three times as an alternative countdown   
  int loopsLeft = 3;
    while (loopsLeft > 0) {
    stripClock.clear(); //clear the clock face 
    stripClock.fill(blue, (8 + 0), 8);
    stripClock.fill(blue, (24 + 0), 8);
    stripClock.fill(blue, (40 + 0), 8);
    stripClock.show();
    delay(600);
    stripClock.clear();
    stripClock.show();
    delay(400);
    loopsLeft--;
  }
  */
  stripClock.fill(green, (0 + 0), 56);
  stripClock.show();
  delay(1000);
  startMillis = millis() - 1000;
}

void buttonAPressed() {
  startMillis = millis();  //restart count-up from 0
}

void buttonBPressed() {
   beepPattern();  //starts a 3 second countdown using color signals before counting upwards again
}

void interuptingVT() {   //For ESP8266 add 'ICACHE_RAM_ATTR' before the word VOID on this line so that it looks like: "    ICACHE_RAM_ATTR void interuptingVT() {   "
  if (digitalRead(remoteButtonA) == HIGH){
    buttonThatWasPressed = "A";
  }
  else if (digitalRead(remoteButtonB) == HIGH) {
    buttonThatWasPressed = "B";
  }
  else if (digitalRead(remoteButtonC) == HIGH) {
    buttonThatWasPressed = "C";
  }
  else if (digitalRead(remoteButtonD) == HIGH) {
    buttonThatWasPressed = "D";
  }
  buttonBeenPressed = true;
}

