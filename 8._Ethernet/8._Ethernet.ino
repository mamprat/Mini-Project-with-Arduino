#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ethernet.h>

OneWire ds18b20_pin(2);
DallasTemperature DS18B20(&ds18b20_pin);

float value_temperature;

//Contoh jaringan lokal dengan alamat = IP 192.168.10.0
byte mac[]         = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Mac Address Default
byte ip[]          = { 192, 168, 10, 2 }; // Ip untuk Ethernet shield / alamat arduino
byte dnsserver[]   = { 8, 8, 8, 8 }; // DNS Server untuk Ethernet shield
byte gateway[]     = { 192, 168, 10, 1 }; // Gateway untuk Ethernet shield / alamat router
byte subnet[]      = { 255, 255, 255, 0 }; // Subnet untuk Ethernet shield

unsigned long samplingTime_ds18b20;
unsigned long samplingTime_kirim;
unsigned long samplingTime_serial;
const unsigned long interval_ds18b20 = 1000;
const unsigned long interval_kirim = 1000;
const unsigned long interval_serial = 1000;

EthernetClient client;
void setup() {
  Serial.begin(9600);

  Ethernet.begin(mac, ip, dnsserver, gateway, subnet);
  Serial.println(Ethernet.localIP());
  Serial.println(Ethernet.subnetMask());
  Serial.println(Ethernet.gatewayIP());
  Serial.println(Ethernet.dnsServerIP());

  DS18B20.begin();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - samplingTime_ds18b20 >= interval_ds18b20) {
    DS18B20.requestTemperatures();
    value_temperature = DS18B20.getTempCByIndex(0);
    samplingTime_ds18b20 = currentTime;
  }

  if (currentTime - samplingTime_serial >= interval_kirim) {
    if (client.connect("192.168.10.1", 80)) {
      Serial.println("Connected");
      client.print("GET /???/???=");
      client.print(value_temperature);
      client.println("HTTP/1.1");
      client.print("Host:192.168.10.1");
      client.println("Connection:close");
      client.stop();
      Serial.println("Close");
    }
    else {
      Serial.println("Disconnected");
    }
    samplingTime_kirim = currentTime;
  }

  if (currentTime - samplingTime_serial >= interval_serial) {
    Serial.println(value_temperature);
    samplingTime_serial = currentTime;
  }
}
