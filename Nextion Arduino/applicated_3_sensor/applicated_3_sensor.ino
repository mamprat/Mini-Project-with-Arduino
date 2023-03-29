//program sederhana HMI nextion menggunakan library untuk
//menampilkan nilai
//mengganti nilai dan save (eeprom)
//dicontohkan dalam mengatur suhu,ph dan tss

//Library
#include "Nextion.h"
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//PIN
OneWire ds18b20_pin(2);
DallasTemperature DS18B20(&ds18b20_pin);
int ph_pin = A0;
int turbidity_pin = A1;

//Kalibrasi PH
float acid_voltage = 1960.80;
float neutral_voltage = 1480.80;

//Inisialisasi nilai
float value_temperature;
float voltage_ph;
float value_ph;
float voltage_turbidity;
float value_tss;

//Inisialisasi offset
float Offset_temperature;
float Offset_ph;
float Offset_tss;

//inisialisasi jeda
unsigned long samplingTime_ds18b20;
unsigned long samplingTime_ph;
unsigned long samplingTime_turbidity;
const unsigned long interval_ds18b20 = 1000;
const unsigned long interval_ph = 1000;
const unsigned long interval_turbidity = 1000;

//Deklarasi tombol yang digunakan
NexButton s1 = NexButton(2, 3, "s1");
NexButton s2 = NexButton(2, 4, "s2");
NexButton p1 = NexButton(2, 6, "p1");
NexButton p2 = NexButton(2, 7, "p2");
NexButton t1 = NexButton(2, 9, "t1");
NexButton t2 = NexButton(2, 10, "t2");

char buffer[100] = {0};
NexTouch *nex_listen_list[] = {
  &s1,    &s2,  &p1,  &p2,  &t1,  &t2,
  NULL
};
//=========suhu===============
void s2PushCallback(void *ptr) {
  Offset_temperature += 0.1;
  memset(buffer, 0, sizeof(buffer));
  itoa(Offset_temperature, buffer, 10);
  EEPROM.write(Offset_temperature, value_temperature);
}
void s1PushCallback(void *ptr) {
  Offset_temperature -= 0.1;
  memset(buffer, 0, sizeof(buffer));
  itoa(Offset_temperature, buffer, 10);
  EEPROM.write(Offset_temperature, value_temperature);
}
//=========pH===============
void p2PushCallback(void *ptr) {
  Offset_ph += 0.1;
  memset(buffer, 0, sizeof(buffer));
  itoa(Offset_ph, buffer, 10);
  EEPROM.write(Offset_ph, value_ph);
}
void p1PushCallback(void *ptr) {
  Offset_ph -= 0.1;
  memset(buffer, 0, sizeof(buffer));
  itoa(Offset_ph, buffer, 10);
  EEPROM.write(Offset_ph, value_ph);
}
//=========TSS===============
void t2PushCallback(void *ptr) {
  Offset_tss += 0.1;
  memset(buffer, 0, sizeof(buffer));
  itoa(Offset_tss, buffer, 10);
  EEPROM.write(Offset_tss, value_tss);
}
void t1PushCallback(void *ptr) {
  Offset_tss -= 0.1;
  memset(buffer, 0, sizeof(buffer));
  itoa(Offset_tss, buffer, 10);
  EEPROM.write(Offset_tss, value_tss);
}


void setup() {
  Serial3.begin(9600); //sebagai contoh menggunakan serial3
  nexInit();
  s1.attachPush(s1PushCallback);
  s2.attachPush(s2PushCallback);
  p1.attachPush(p1PushCallback);
  p2.attachPush(p2PushCallback);
  t1.attachPush(t1PushCallback);
  t2.attachPush(t2PushCallback);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - samplingTime_ds18b20 >= interval_ds18b20) {
    DS18B20.requestTemperatures();
    value_temperature = DS18B20.getTempCByIndex(0);
    String command = "displaysuhu.txt=\"" + String(value_temperature + Offset_temperature) + "\"";
    Serial.print(command);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    samplingTime_ds18b20 = currentTime;
  }
  if (currentTime - samplingTime_ph > interval_ph) {
    for (int i = 0; i < 800; i++) {
      voltage_ph += ((float)analogRead(ph_pin) / 1024.0) * 5000;
    }
    voltage_ph = voltage_ph / 800;
    voltage_ph = round_to_dp(voltage_ph, 1);
    float slope = (7.0 - 4.0) / ((neutral_voltage - 1500) / 3.0 - (acid_voltage - 1500) / 3.0);
    float intercept = 7.0 - slope * (neutral_voltage - 1500) / 3.0;
    value_ph = slope * (voltage_ph - 1500) / 3.0 + intercept ;
    String command = "displayph.txt=\"" + String(value_ph + Offset_ph) + "\"";
    Serial.print(command);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    samplingTime_ph = currentTime;
  }
  if (currentTime - samplingTime_turbidity >= interval_turbidity) {
    voltage_turbidity = 0;
    for (int i = 0; i < 800; i++) {
      voltage_turbidity += ((float)analogRead(turbidity_pin) / 1023) * 5;
    }
    voltage_turbidity = voltage_turbidity / 800;
    voltage_turbidity = round_to_dp(voltage_turbidity, 1);
    if (voltage_turbidity > 4.5) {
      value_tss = 0;
    } else {
      value_tss = 225 * square(voltage_turbidity) - 2920.5 * voltage_turbidity + 8591; //akhir
      String command = "displaytss.txt=\"" + String(tss + Offset_tss) + "\"";
      Serial.print(command);
      Serial.write(0xff);
      Serial.write(0xff);
      Serial.write(0xff);
      samplingTime_turbidity = currentTime;
    }
  }
  nexLoop(nex_listen_list);
}
