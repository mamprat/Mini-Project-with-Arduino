//program sederhana HMI nextion menggunakan library untuk menyalakan LED

#include "Nextion.h"
const int led = 13;

//Deklarasi tombol yang digunakan
NexButton b0 = NexButton(0, 2, "b0");
NexButton b1 = NexButton(0, 3, "b1");
NexText t0 = NexText(0, 4, "t0");

char buffer[100] = {0};
NexTouch *nex_listen_list[] = {
  &b0, &b1,
  NULL
};

//Fungsi popcallback komponen tombol b0
//Saat tombol ON dilepas, LED menyala dan teks status berubah
void b0PopCallback(void *ptr) {
  t0.setText ("State:ON");
  digitalWrite(led, HIGH);
}

//Fungsi popcallback komponen tombol b1
//Saat tombol OFF dilepas, LED mati dan teks status berubah
void b1PopCallback(void *ptr) {
  t0.setText ("State:OFF");
  digitalWrite(led, LOW);
}

void setup() {
  nexInit();
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  nexLoop(nex_listen_list); 
}
