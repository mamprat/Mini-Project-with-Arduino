//ESP8266 ESP01
//cek terlebih dahulu bauderate
//dowgrade/rubah di AT
//jika di bawahnya tidak ada tulisan = 9600
//jika di bawahnya ada tulisan       = 115200
//contoh disini digunakan untuk mengirimkan ke speedsheet
//library : https://github.com/bportaluri/WiFiEsp
//https://www.youtube.com/watch?v=7Z5xzxSoXtE


#include "WiFiEsp.h"
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

char ssid[] = "Twim";            // SSID (wifi)
char pass[] = "12345678";        // password SSID (wifi)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "api.pushingbox.com"; //server untuk menyimpan data hasil pendeteksian

// Inisialisasi sebagai client
WiFiEspClient client;

void setup() {
  Serial.begin(115200);  //menampilkan pada serial monitor
  Serial1.begin(9600);  //komunikasi arduino dengan esp untuk dikirimkan ke WEB
  WiFi.init(&Serial1);

  // check mengecek keberadaan modul WiFi
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi Modul TIDAK TERDETEKSI");
    while (true);
  }
  while ( status != WL_CONNECTED) {
    Serial.print("Mencoba terhubung ke SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("WiFi Modul TERHUBUNG INTERNET");

  // Keterangan Koneksi 
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void loop() {
  //
  //koding sensor
  //
  if (client.connect(server, 80)) {
    Serial.println("Menghubungkan ke Server");

    //Proses Pengiriman
    client.println("GET /pushingbox?devid=v94A96D0208F7E16");

    //pengambilan data sensor dan diletakan dimana
//    client.println("&t= ");
//    client.println(String(t));
//    client.println("&x= ");
//    client.println(String(x));
//    client.println("&r= ");
//    client.println(String(r));
    //============================================
    client.println(" HTTP/1.1");
    client.println("Host: api.pushingbox.com");
    client.println();
  }

  //  // Data yang diterima server untuk di serial monitor
  //  while (client.available()) {
  //    char c = client.read();
  //    Serial.write(c);
  //  }
  //  // cek server's disconnected
  //  if (!client.connected()) {
  //    Serial.println();
  //    Serial.println("Disconnecting server...");
  //    client.stop();
  //    while (true);
  //  }
}
