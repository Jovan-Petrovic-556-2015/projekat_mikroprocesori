/*
* Projekat iz mikroprocesorskih sistema:
* Kontrola servo motora preko ultrazvucnog senzora
*
* Rad servo motora se odvija dok ultrazvucni senzor ne detektuje objekat u svojoj blizini  
* Kada se objekat detektuje, rad motora se prekida
* 
* Jovan Petrovic
*/

#include <Servo.h>                 // Ubacivanje servo biblioteke
const int trigPin = 9;             // Ubacivanje pozicije pinova za ultrazvucni senzor u konstante
const int echoPin = 10;

long trajanje;                     // Postavljanje promenljivih
int daljina;

Servo mojservo;                    // Postavljanje servo motora
int pozicija = 0;                  // Promenjljiva za diktiranje pozicije servo motoru

void ultrazvuk(){                  // Funkcija koja obavlja akviziciju i racunanje daljine

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
trajanje = pulseIn(echoPin, HIGH); 
daljina= trajanje*0.034/2;         // Racunanje daljine za nepromenjljivu vlaznost i temperaturu vazduha
Serial.print("Daljina: ");
Serial.println(daljina);
}

void setup() {                     // Definisanje smerova pinova (ulaz/izlaz)

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);      // Definise se ugradjena svetleca dioda da svetli ako je objekat u dometu
mojservo.attach(6);                // Servo pin na poziciji 6
}

void servoPisi(){                  // Servo se dovodi u -pozicija- stepeni
  mojservo.write(pozicija);
  delay(100);
}

void loop() {                      // Glavna petlja
  ultrazvuk();                     // Odredjivanje daljine objekta
  if (daljina < 10){
  digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
    pozicija += 5;                 // Servo se okrece samo u slucaju da objekat nije u dometu
    if (pozicija == 355){
    pozicija = 0;
  }
  servoPisi();
  }
}
