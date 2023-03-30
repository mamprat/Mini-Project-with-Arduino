//WDT digunakan untuk me-reset arduino saat programnya hang/error seperti saat arduino dinyalakan.
//Error terjadi karena
//program rusak karena sensor, low merespon, data keliru, data overflow,
//kabel sensor atau modul terputus
//program akan aktif ketika sistem melebihi dari wdt_enable(max8detik) yang disetting
//ketika lebih maka akan dilakukan restrat

#include <avr/wdt.h>
//couter
byte couter = 0;

void setup() {
  // disable wdt
  //lalu tunggu hingga stabil
  wdt_disable();
  delay(2000);
  Serial.begin(19200);
  while (!Serial);
  //
  //konfigurasi sesuai kebutuhan
  //
  Serial.println("===Start===");
  //aktifkan WDT dengan waktu tunggu 4detik
  wdt_enable(WDTO_4S);
}

void loop() {
  Serial.print("couter No ");
  Serial.print(couter);
  Serial.print(" ->");

  if (couter == 0) {
    Serial.println(" 2 Detik");
    delay(2000);
  }
  else if (couter == 1) {
    Serial.println(" 6 Detik");
    delay(1000);
    delay(1000);
    delay(1000);
    wdt_reset();
    delay(1000);
    delay(1000);
    delay(1000);
    wdt_reset();
  }
  else if (couter == 2) {
    Serial.println(" 11 Detik");
    for (byte i=0; i < 11; i++) {
      delay(1000);
      wdt_reset();
    }
  }
  else {
    //blok program 4.5 detik
    Serial.println(" 4.5 Detik");
    delay(4500);
  }
  couter++;
  //reset wdt,kerupuk sudah habis
  wdt_reset();
}
