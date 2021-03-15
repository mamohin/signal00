/*
    ���������� ������ ������ (�� JDY-40)
    ��� �������� �� ������
    Author:     Andrew Mamohin
*/

const byte s = 15; // ������ �������� �� A1
const byte t0 = 11; // ����� �� ���������� OK
const byte t1 = 12; // ����� �� ���������� ARARM
const unsigned long tis = 15000; // �������� ����� ����������
const unsigned long tit = 1000; // ����������������� �������� ��� ��������
const unsigned long tia = 5000; // ����������������� �������� ��� �������

unsigned long ti0 = 0; // ������� ����� ����������
unsigned long ti1 = 0; // ������� �������� OK
unsigned long ti2 = 0; // ������� �������� ALARM
unsigned long ti = 0; // ����� � �������


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

 if (ti0 < ti) {                // �������� �������� OK 
     if (ti2 == 0) { digitalWrite(t0, HIGH); }  // ���� ��� ALARM
     ti0 = ti + tis;
     ti1 = ti + tit;
 }
 
 if ((ti1 > 0) && (ti1 < ti)) { // ��������� �������� OK 
     digitalWrite(t0, LOW);
     ti1 = 0;
 }

 if (analogRead(s) > 125) {     // ���������� ������ ��������
     digitalWrite(t0, LOW);
     digitalWrite(t1, HIGH);
     ti0 = ti + tis + tia;
     ti1 = 0;
     ti2 = ti + tia;
 }
 
 if ((ti2 > 0) && (ti2 < ti)) { // ��������� �������� ALARM 
     digitalWrite(t1, LOW);
     ti2 = 0;
     ti0 = ti + tis;
 }

  delay(100);
}
