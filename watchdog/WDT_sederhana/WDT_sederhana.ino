//WDT digunakan untuk me-reset arduino saat programnya hang/error seperti saat arduino dinyalakan.
//Error terjadi karena
//program rusak karena sensor, low merespon, data keliru, data overflow,
//kabel sensor atau modul terputus
//program akan aktif ketika sistem melebihi dari wdt_enable(max8detik) yang disetting
//ketika lebih maka akan dilakukan restrat

#include <avr/wdt.h>
//couter
const byte jumlah_kerupuk = 10;

//lama delay makan kerupuk dal ms
int lama_makan_kerupuk[jumlah_kerupuk] = {
  3000, 3500, 2000, 5500, 4000,
  9000, //keselek jadi lama
  2000, 3000, 4000, 5000
};

byte giliran = 0;

void setup() {
  // disable wdt
  //lalu tunggu hingga stabil
  wdt_disable();
  delay(2000);
  Serial.begin(19200);
  //
  //konfigurasi sesuai kebutuhan
  //
  Serial.println("===Start===");
  //aktifkan WDT dengan waktu tunggu 8detik
  wdt_enable(WDTO_8S);
}

void loop() {
  // lama makan kerupuk sesuai giliran
  delay(lama_makan_kerupuk[giliran]);
  giliran++;

  Serial.print("kerupuk No ");
  Serial.print(giliran);
  Serial.println(", habis!");

  //reset wdt,kerupuk sudah habis
  wdt_reset();
}
