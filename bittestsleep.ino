#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  2        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int  loopCtr = 0;
RTC_DATA_ATTR byte x       = 0;

const int lvPower       = GPIO_NUM_26;


#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7

#define MDEL 10



//byte x = 0b00000000;  // the 0b prefix indicates a binary constant

int latchPin = GPIO_NUM_18;  //Pin connected to ST_CP (RCK) of 74HC595 pin 12
int clockPin = GPIO_NUM_19;  //Pin connected to SH_CP (SRCLK) of 74HC595 pin 11
int dataPin  = GPIO_NUM_23;  //Pin connected to DS of (SER) 74HC595 pin 14

void setMyBit(int myBit) {
  bitWrite(x, myBit, 1);
  Serial.println(x, BIN);
  myShiftOut(x);
  delay(MDEL);
}

void clrMyBit(int myBit) {
  bitWrite(x, myBit, 0);
  Serial.println(x, BIN);
  myShiftOut(x);
  delay(MDEL);
}

void myShiftOut (byte numberToDisplay) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
  digitalWrite(latchPin, HIGH);
  delay(MDEL);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}  // wait for serial port to connect. Needed for native USB port only
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(lvPower, OUTPUT);
}

void loop() {

  digitalWrite(lvPower, 1);
  Serial.println(x, BIN); // 10000000
  if (loopCtr < 4) {
    setMyBit(LED0);
    setMyBit(LED1);
    setMyBit(LED2);
    setMyBit(LED3);
    setMyBit(LED4);
    setMyBit(LED5);
    setMyBit(LED6);
    setMyBit(LED7);

    clrMyBit(LED0);
    clrMyBit(LED1);
    clrMyBit(LED2);
    clrMyBit(LED3);
    clrMyBit(LED4);
    clrMyBit(LED5);
    clrMyBit(LED6);
    clrMyBit(LED7);
  }
  Serial.println("\n");

  //x = 0b00000000;

  delay(MDEL * 4);

  if (loopCtr++ == 4) {
    setMyBit(LED3);
    setMyBit(LED5);
  } else {
    if (loopCtr % 2) {
      setMyBit(LED0);
    } else {
      clrMyBit(LED0);
    }

  }

  Serial.println(loopCtr);

  // do timer wakeup as usual
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();



}
