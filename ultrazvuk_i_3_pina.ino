/* kod uspesno cita sa ultrazvucnog senzora i
*  ocitava daljinu za fiksnu vlaznost i temperaturu vazduha
*  const brzina zvuka
*  stampa daljinu
*  odradjene granice za min i max odredjivanje - 2cm do 400cm
*  
*  
*  radi se realizacija drajvera za servomotor sa tri pina: PLS,ENA i DIR
*  pls radi na digitalni pwm
*/

const int trig = 9;
const int echo = 10;

const int PLS = 3;
const int DIR = 2;
const int ENA = 4;

long trajanje;
int daljina;
byte pls;

void ultrazvuk(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  trajanje = pulseIn(echo, HIGH);
  daljina = trajanje*0.034/2;
  daljina = constrain(daljina, 2 , 400);

  Serial.print("Daljina od senzora: ");
  Serial.println(daljina);
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(DIR,HIGH);
  ultrazvuk();
  if (daljina < 10){
  digitalWrite(ENA, LOW);
}
else{
  digitalWrite(ENA, HIGH);
}
  pls = map(daljina,2,400,0,255);
  analogWrite(PLS,pls);
}
