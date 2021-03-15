/*
    передатчик второй версии (на JDY-40)
    для сигналки на работе
    Author:     Andrew Mamohin
*/

const byte s = 15; // датчик движения на A1
const byte t0 = 11; // выход на передатчик OK
const byte t1 = 12; // выход на передатчик ARARM
const unsigned long tis = 15000; // задержка между передачами
const unsigned long tit = 1000; // продолжительность передачи при проверке
const unsigned long tia = 5000; // продолжительность передачи при тревоге

unsigned long ti0 = 0; // таймаут между передачами
unsigned long ti1 = 0; // таймаут передачи OK
unsigned long ti2 = 0; // таймаут передачи ALARM
unsigned long ti = 0; // время с запуска


void setup()
{
 delay(1000);
 pinMode(13, OUTPUT);
 digitalWrite(13, LOW);
 pinMode(s, INPUT);
 pinMode(t0, OUTPUT);
 digitalWrite(t0, LOW);
 pinMode(t1, OUTPUT);
 digitalWrite(t1, LOW);
}

void loop()
{
 ti = millis();

 if (ti0 < ti) {                // включаем передачу OK 
     if (ti2 == 0) { digitalWrite(t0, HIGH); }  // если нет ALARM
     ti0 = ti + tis;
     ti1 = ti + tit;
 }
 
 if ((ti1 > 0) && (ti1 < ti)) { // выключаем передачу OK 
     digitalWrite(t0, LOW);
     ti1 = 0;
 }

 if (analogRead(s) > 125) {     // опрашиваем датчик движения
     digitalWrite(t0, LOW);
     digitalWrite(t1, HIGH);
     ti0 = ti + tis + tia;
     ti1 = 0;
     ti2 = ti + tia;
 }
 
 if ((ti2 > 0) && (ti2 < ti)) { // выключаем передачу ALARM 
     digitalWrite(t1, LOW);
     ti2 = 0;
     ti0 = ti + tis;
 }

  delay(100);
}
