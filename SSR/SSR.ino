int SSR1 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(SSR1, OUTPUT);
}

void loop() {
//Menyalakan SSR  
  digitalWrite(SSR1, HIGH);
  Serial.println("Relay ON ");
  delay(5000);

//Mematikan SSR  
  digitalWrite(SSR1, LOW);
  Serial.println("Relay OFF ");
  delay(2000);
}
 
