int relay1 = 8;
int relay2 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
}

void loop() {
//pemasangan pada kondisi NO
    digitalWrite(relay1, HIGH); //Menyala
    delay(5000);
    
    digitalWrite(relay1, LOW); //Mati
    delay(2000);
    
//pemasangan pada kondisi NC
    digitalWrite(relay2, LOW); //Mati
    delay(5000);
    
    digitalWrite(relay2, HIGH); //Menyala
    delay(2000);
}
 
