//RTC DS3231SN hasilnya lebih akurat dan stabil
//RTC DS3231SN yang menggunakan xtal internal temperature compensation
//library : https://github.com/NorthernWidget/DS3231

#include <DS3231.h>
DS3231  rtc(SDA, SCL);

unsigned long samplingTime;
const unsigned long interval = 1000;


void setup() {
  Serial.begin(9600);
  rtc.begin();
  // dilakukan upload 2x untuk setting time saat ini, kemudian dilakukan upload coding kedua dengan comment settingan waktu
  //rtc.setDate(29, 3, 2023);     //dd//mm//yyyy
  //rtc.setTime(11, 00, 00);      //hh 11:00:00
  //rtc.setDOW(6);                //dd "Sabtu"
  delay(2000);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - samplingTime >= interval) {
    Serial.print(rtc.getDOWStr()); //pembacaan Hari DD
    Serial.print(" ");

    Serial.print(rtc.getDateStr()); //pembacaan Tanggal DD:MM:YYYY
    Serial.print(" -- ");

    Serial.println(rtc.getTimeStr()); //pembacaan Waktu HH:MM:SS
    samplingTime = currentTime;
  }
}
