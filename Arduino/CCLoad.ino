/**************************************************************************


 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define CHANGE_INTERVAL 4000
#define N_SAMPLES 200
#define SET_PIN A0
#define CURR_PIN A1
#define VOLT_PIN A2
#define SET_MULT 4.72
#define CURR_MULT 4.75
#define VOLT_MULT 29.23

float set = 0;
float u = 0;
float i = 0;
float r = 0;
float p = 0;

unsigned long previousMillis = 0;
int screen = 1;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL); // 1.1V internal voltage reference
  for(int i = 0; i < 20; i++) // Docs said first few readings may be inaccurate
    analogRead(A0);

  // Init OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  // Show init message
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);
  display.setCursor(20, 25);
  display.println(F("CC Load"));
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.display();

  previousMillis = millis();
}

void loop() {
  // Sample set current
  set = 0;
  for(int i = 0; i < N_SAMPLES; i++){
    set += float(analogRead(SET_PIN)) * 1.1 * SET_MULT / 1024.0;
  }
  set /= N_SAMPLES;

  // Sample voltage
  u = 0;
  for(int i = 0; i < N_SAMPLES; i++){
    u += float(analogRead(VOLT_PIN)) * 1.1 * VOLT_MULT / 1024.0;
  }
  u /= N_SAMPLES;

  // Sample current
  i = 0.0;
  for(int j = 0; j < N_SAMPLES; j++){
    i += float(analogRead(CURR_PIN)) * 1.1 * CURR_MULT / 1024.0;
  }
  i /= N_SAMPLES;
  if(i < 0.005)
    i = 0;
  
  // Calculate resistance
  r = u / i;
  
  // Calculate power
  p = i * u;
  
  // Display first screen
  if(screen){
    display.clearDisplay();
    display.setTextSize(2);
    if(set >= 0.10){
      display.setCursor(10, 5);
      display.print(F("I"));
      display.setTextSize(1);
      display.setCursor(20, 15);
      display.print(F("set"));
      display.setTextSize(2);
      display.setCursor(37, 5);
      display.print(F("="));
      display.setCursor(58, 5);
      display.print(set);
      display.print(F("A"));
    } else {
      display.setCursor(10, 5);
      display.print(F("I"));
      display.setTextSize(1);
      display.setCursor(20, 15);
      display.print(F("set"));
      display.setTextSize(2);
      display.setCursor(37, 5);
      display.print(F("="));
      display.setCursor(58, 5);
      if(set*1000 < 10)
        display.print(F(" "));
      if(set*1000 < 100)
        display.print(F(" "));
      display.print(int(set*1000));
      display.print(F("mA"));
    }
    if(i >= 0.10){
      display.setCursor(10, 25);
      display.print(F("I = "));
      display.print(i);
      display.print(F("A"));
    } else {
      display.setCursor(10, 25);
      display.print(F("I = "));
      if(i*1000 < 10)
        display.print(F(" "));
      if(i*1000 < 100)
        display.print(F(" "));
      display.print(int(i*1000));
      display.print("mA");
    }
    display.setCursor(10, 45);
    display.print(F("U ="));
    if(u < 10)
      display.print(F(" "));
    display.print(u);
    display.print(F("V"));
    display.display();
  }
  // Display second screen
  else{    
    display.clearDisplay();
    display.setCursor(10, 10);
    if(r < 1000){
      display.print(F("R="));
      if(r < 10)
        display.print(F(" "));
      if(r < 100)
        display.print(F(" "));
      display.print(r);
      display.print((char)234);
    } else if(r < 10000){
      display.print(F("R="));
      if(r < 10000)
        display.print(F(" "));
      display.print(r/1000);
      display.print(F("k"));
      display.print((char)234);
    }else{
      display.print(F("R="));
      display.print(F("  inf "));
      display.print((char)234);
    }
    if(p >= 0.10){
      display.setCursor(10, 35);
      display.print(F("P= "));
      if(p < 10)
        display.print(F(" "));
      display.print(p);
      display.print(F("W"));
      display.display();
    }
    else{
      display.setCursor(10, 35);
      display.print(F("P="));
      if(p*1000 < 10)
        display.print(F(" "));
      display.print(p*1000);
      display.print(F("mW"));
      display.display();
    }
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= CHANGE_INTERVAL) {
    previousMillis = currentMillis;
    screen = 1 - screen;
  }
  delay(50);
}
