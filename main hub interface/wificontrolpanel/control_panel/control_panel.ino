//#include <pitches.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Adafruit_ESP8266.h>
#include <SoftwareSerial.h>

#define ROWS 4 //four rows
#define COLS 3 //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 10, 11}; //connect to the column pinouts of the keypad

#define ESP_RX   2
#define ESP_TX   3
#define ESP_RST  12
SoftwareSerial softser(ESP_RX, ESP_TX);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define backlight A5
LiquidCrystal lcd(A7, A0, A1, A2, A3, A4);

// Must declare output stream before Adafruit_ESP8266 constructor; can be
// a SoftwareSerial stream, or Serial/Serial1/etc. for UART.
Adafruit_ESP8266 wifi(&softser, &Serial, ESP_RST);
// Must call begin() on the stream(s) before using Adafruit_ESP8266 object.

#define ESP_SSID "SSIDNAME" // Your network name here
#define ESP_PASS "PASSWORD" // Your network password here

#define HOST     "www.adafruit.com"     // Host to contact
#define PAGE     "/testwifi/index.html" // Web page to request
#define PORT     80                     // 80 = HTTP default port

#define LED_PIN  A5

void setup() {
  // hardware serial connection to hopper
  Serial.begin(9600);
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  */
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight,HIGH);

  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("hello, world!");
/*
  //==================================ESP8266 setup===================
  char buffer[50];

  // Flash LED on power-up
  pinMode(LED_PIN, OUTPUT);
  for(uint8_t i=0; i<3; i++) {
    digitalWrite(13, HIGH); delay(50);
    digitalWrite(13, LOW);  delay(100);
  }

  // This might work with other firmware versions (no guarantees)
  // by providing a string to ID the tail end of the boot message:
  
  // comment/replace this if you are using something other than v 0.9.2.4!
  wifi.setBootMarker(F("Version:0.9.2.4]\r\n\r\nready"));

  softser.begin(9600); // Soft serial connection to ESP8266
  Serial.begin(57600); while(!Serial); // UART serial debug

  Serial.println(F("Adafruit ESP8266 Demo"));

  // Test if module is ready
  Serial.print(F("Hard reset..."));
  if(!wifi.hardReset()) {
    Serial.println(F("no response from module."));
    for(;;);
  }
  Serial.println(F("OK."));

  Serial.print(F("Soft reset..."));
  if(!wifi.softReset()) {
    Serial.println(F("no response from module."));
    for(;;);
  }
  Serial.println(F("OK."));

  Serial.print(F("Checking firmware version..."));
  wifi.println(F("AT+GMR"));
  if(wifi.readLine(buffer, sizeof(buffer))) {
    Serial.println(buffer);
    wifi.find(); // Discard the 'OK' that follows
  } else {
    Serial.println(F("error"));
  }

  Serial.print(F("Connecting to WiFi..."));
  if(wifi.connectToAP(F(ESP_SSID), F(ESP_PASS))) {

    // IP addr check isn't part of library yet, but
    // we can manually request and place in a string.
    Serial.print(F("OK\nChecking IP addr..."));
    wifi.println(F("AT+CIFSR"));
    if(wifi.readLine(buffer, sizeof(buffer))) {
      Serial.println(buffer);
      wifi.find(); // Discard the 'OK' that follows

      Serial.print(F("Connecting to host..."));
      if(wifi.connectTCP(F(HOST), PORT)) {
        Serial.print(F("OK\nRequesting page..."));
        if(wifi.requestURL(F(PAGE))) {
          Serial.println("OK\nSearching for string...");
          // Search for a phrase in the open stream.
          // Must be a flash-resident string (F()).
          if(wifi.find(F("working"), true)) {
            Serial.println(F("found!"));
          } else {
            Serial.println(F("not found."));
          }
        } else { // URL request failed
          Serial.println(F("error"));
        }
        wifi.closeTCP();
      } else { // TCP connect failed
        Serial.println(F("D'oh!"));
      }
    } else { // IP addr check failed
      Serial.println(F("error"));
    }
    wifi.closeAP();
  } else { // WiFi connection failed
    Serial.println(F("FAIL"));
  }
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
    lcd.setCursor(0, 2);
  }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}



/*
// ==================================================================
// ==================================================================
// ==================================================================
// notes in the melody:
int shavenotes[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int shavetime[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// ==================================================================
int alarmnotes[] ={
  NOTE_C4, NOTE_G3, NOTE_A3, 0, NOTE_C4, NOTE_G3, NOTE_A3, 0, NOTE_C4, NOTE_G3, NOTE_A3
};
int alarmtime[] = {
  4, 8, 4, 2, 4, 8, 4, 2, 4, 8, 4, 2,
};

// ==================================================================
// ==================================================================
// ==================================================================

void alert(int melody, int noteDurations) {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
*/
