#include <SendOnlySoftwareSerial.h>
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#define DS1307_ADDR   0x68              // I2C real time clock

byte seconds, minutes, hours, day_of_week, days, months, years, PM, hour12, DST;
SendOnlySoftwareSerial Serial(4);  // Serial transmission on Trinket Pin 3

void setup() {
  Serial.begin(9600);
  TinyWireM.begin();                    // initialize I2C lib
  delay (2000);
}


void loop() {
  Get_Time();                           // read current time                        // wait a few sec before next reading
}

void Get_Time() {        // get the time and date from the DS1307 chip
  byte wireRet = 0;
  memset(timeString, 0, sizeof(timeString)); // initialize the strings
  memset(dateString, 0, sizeof(dateString));

  TinyWireM.beginTransmission(DS1307_ADDR); // reset DS1307 register pointer
  TinyWireM.send(0);
  wireRet = TinyWireM.endTransmission();
  wireRet = TinyWireM.requestFrom(DS1307_ADDR, 7);    // request 7 bytes from DS1307
  
  seconds = bcdToDec(TinyWireM.receive());  // handle the 7 bytes received
  minutes = bcdToDec(TinyWireM.receive());
  hours = bcdToDec(TinyWireM.receive());
  day_of_week = TinyWireM.receive();
  days = bcdToDec(TinyWireM.receive());
  months = bcdToDec(TinyWireM.receive());
  years = bcdToDec(TinyWireM.receive());

  Serial.print("H:");
  Serial.print(hours);
  Serial.print(" M:");
  Serial.print(minutes);
  Serial.print(" S:");
  Serial.println(seconds);

  Serial.print("DOW:");
  Serial.print(day_of_week);
  Serial.print(" D/");
  Serial.print(days);
  Serial.print(" M");
  Serial.print(months);
  Serial.print(" Y/");
  Serial.println(years);
}

byte bcdToDec(byte val) {               // Convert binary coded decimal to normal decimal numbers
  return ((val / 16 * 10) + (val % 16));
}
