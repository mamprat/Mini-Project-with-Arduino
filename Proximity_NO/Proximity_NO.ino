//Inductive Proximity = sensor yang ketika mendeteksi logam maka akan aktif.
//Jenis yang digunakan adalah jenis Proximity NPN *(NO)(6-24VDC)
//Jika mendeteksi logam = logika 1

int sensor = 8; //inisialisasi pin digital D8
int buzzer = 10;//inisialisasi pin digital D10

int logam;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  logam = digitalRead(sensor);
  delay(1000);
  {
    if (logam == 1) {
      Serial.print("Terdeteksi : Logam");
      digitalWrite(buzzer, HIGH);
    }
    if (logam == 0) {
      Serial.print("Terdeteksi : Non-Logam");
      digitalWrite(buzzer, LOW);
    }
  }
}
