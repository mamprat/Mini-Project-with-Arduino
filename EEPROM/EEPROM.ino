//EEPROM internal = penyimapan data yang terdapat di arduino 
//bersifat volatile = ketika tidak ada power data tetap tersimpan di arduino
//jumlah alamat tergantung kapasitas
//alamat penyimpanan = 0 - 1023
//untuk data yang bisa disimpan 8bit = 0 - 255
//batas penulisan,hapus dll = 100.000 kali
//baca = bebas

#include<EEPROM.h>
byte nilai;

void setup() {
  Serial.begin(9600);
  EEPROM.write(0,123);
  EEPROM.write(3,200);
}

void loop() {
  nilai =  EEPROM.read(0);
  Serial.print(nilai);
  delay(1000);

  nilai =  EEPROM.read(3);
  Serial.print(nilai);
  delay(1000);
}
