
#include <Adafruit_NeoPixel.h>

// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    7
#define LED_PIN2    8

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 72
#define LED_COUNT2 62

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

// define non PHA
int PHA = 0xFF;

//using push button as trigger
const int buttonPin = 9;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

const int buttonPin2 = 10;     

int buttonState = 0;         // variable for reading the pushbutton status
int buttonState2 = 0; 

char val; // Data received from the serial port


void setup() {

  strip1.begin();           
  strip1.show();

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  
  //final brightness wil depend on spacing of white acrylic and LEDs
  strip.setBrightness(155); // Set BRIGHTNESS to about 1/5 (max = 255)

//  // initialize the LED pin as an output:
//  pinMode(ledPin, OUTPUT);
//  // initialize the pushbutton pin as an input:
//  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}


void loop() {

    if (Serial.available()) 
   { // If data is available to read,
     val = Serial.read(); // read it and store it in val
   } else {
    val = 0;
   }

  // check what Asteroid to fire (PHA or non PHA)
  if (val == 'a') {
    // turn LED on:

    digitalWrite(ledPin, HIGH);
    
    //notPHA
    meteorRain2(0x00, 0x00, PHA, 1, 150, true, 100);
    
  } 
  
  else if (val == 'b') {

    digitalWrite(ledPin, HIGH);

//    PHA
//    meteorRain(PHA, 0x00, 0x00, 1, 200, true, 150);
    meteorRain(PHA, 0x00, 0x00, 1, 150, true, 100);
    
  }

  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  Serial.println(val);
 
//  delay(500);
  
//    meteorRain(PHA, 0x00, 0x00, 1, 200, true, 100);

}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
//  setAll(0,0,0);
//  strip.clear();
// strip.show();
// strip.Color(0, 0, 0);
  
  for(int i = 0; i < LED_COUNT+LED_COUNT; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<LED_COUNT; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <LED_COUNT) && (i-j>=0) ) {
       strip.setPixelColor(i-j, red, green, blue);
      } 
    }
   
    strip.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

void meteorRain2(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
//  setAll(0,0,0);
//  strip.clear();
// strip.show();
// strip.Color(0, 0, 0);
  
  for(int i = 0; i < LED_COUNT2+LED_COUNT2; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<LED_COUNT2; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack2(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <LED_COUNT2) && (i-j>=0) ) {
       strip1.setPixelColor(i-j, red, green, blue);
      } 
    }
   
    strip1.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack2(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip1.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip1.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}
