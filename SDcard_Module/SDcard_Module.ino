//Modul SDcard difungsikan sebagai media penyimpanan data hasil pendeteksian datalogger yang biasanya dikombinasikan dengan RTC untuk pewaktuan
//library : https://github.com/arduino-libraries/SD

#include <SPI.h>
#include <SD.h>

unsigned long samplingTime;
const unsigned long interval = 1000;

File myFile;

void setup() {
  Serial.begin(9600);
  if (!SD.begin(10)) { //inisialisasi pin CS(10) | MOSI(11) | MISO(12) | SCK(13) pada arduino UNO
  Serial.println("Gagal Membuka Micro SD!");
    return;
  }
  Serial.println("Berhasil Membuka Micro SD");
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - samplingTime >= interval) {
    myFile = SD.open("logger.txt", FILE_WRITE);
//misalnya ingin menyimpan data dari RTC DS3231SN
//    myFile.print(rtc.getDOWStr()); //pembacaan Hari DD
//    myFile.print(" ");
//
//    myFile.print(rtc.getDateStr()); //pembacaan Tanggal DD:MM:YYYY
//    myFile.print(" -- ");
//
//    myFile.println(rtc.getTimeStr()); //pembacaan Waktu HH:MM:SS
//    myFile.close();
    samplingTime = currentTime;
  }
}
