//#include <Servo.h>

#define echoPin 13 //Ultrasonik sensörün echo pini Arduino'nun 12.pinine
#define trigPin 12

#define S_Sol 8
#define S_Orta 11
#define S_Sag 2

#define MotorR1 7
#define MotorR2 6
#define MotorRE 9

#define MotorL1 4
#define MotorL2 5
#define MotorLE 3

int data = 0;
long sure, uzaklik;
//Servo myservo;

void setup() {
  
  //myservo.attach(10);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(S_Sol, INPUT);
  #pinMode(S_Orta, INPUT);
  pinMode(S_Sag, INPUT);

  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT);

  Serial.begin(9600);
  Serial.println("BT Uygulaması");
  //myservo.write(90);
}

void loop() {
  ////////////////BT HABERLEŞMESİ//////////////////
  if (Serial.available() >= 1 ) {
    data = Serial.read();     //  2 byte lık bir sayı olduğundan yüksek değerlikli bitlere kaydırıldı.
    Serial.println(data);
  }
  
  
  if (data == 11 || data == 59) {
    engeldenkac();
  }

  if (data == 12 || data == 60) {
    cizgiIzle();
  }

  if (data == 13 || data == 61) { 
    dur();
  }


  if (data == 1 || data == 49 ) {
    ileri();
    delay(10);
    Serial.println("ileri gitti");
  }
  if (data == 4 || data == 52) {
    sol();
    delay(10);
    Serial.println("sola gitti");
  }
  if (data == 2 || data == 50) {
    geri();
    delay(10);
    Serial.println("geri gitti");
  }
  if (data == 3 || data == 51) {
    sag();
    delay(10);
    Serial.println("saga gitti");
  }
  if (data == 0 || data == 48) {
    dur();
    delay(10);
    Serial.println("durdu");

  }
  ////////////////////////////////////////////////////////////////
}


void ileri() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 100);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 100);

}

void geri() {
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, 100);

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  analogWrite(MotorLE, 100);

}

void sag() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, LOW);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 100);

}
void sol() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 100);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, LOW);

}
void dur() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 0);
}

void engeldenkac() {
  digitalWrite(trigPin, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

  sure = pulseIn(echoPin, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = sure / 29.1 / 2; //ölçülen süre uzaklığa çevriliyor

  Serial.println(uzaklik);

  if (uzaklik < 15)
  {
    geri();  // 150 ms geri git
    delay(150);
    sag();  // 250 ms sağa dön
    delay(250);
    
    /* for (int i = 0 ; i <= 180 ; i += 90) {
      //myservo.write(i);
      if (uzaklik > 15) {
        if (i = 0) {
          geri();
          delay(150);
          sol();
          delay(250);
        }
        if (i = 180) {
          geri();
          delay(150);
          sag();
          delay(250);
        }
      }
      */

      
    }
    //myservo.write(90);
    
  else {  // değil ise,
    ileri(); // ileri git
  }
}

void cizgiIzle() {
/*
  digitalWrite(trigPin, LOW); //sensör pasif hale getirildi
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

  sure = pulseIn(echoPin, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = sure / 29.1 / 2; //ölçülen süre uzaklığa çevriliyor

  Serial.println(uzaklik);

  Serial.print(digitalRead(S_Sol));
  Serial.print(",");
  Serial.print(digitalRead(S_Orta));
  Serial.print(",");
  Serial.print(digitalRead(S_Sag));
  Serial.println("------------------");
  
  if (digitalRead(S_Sol) == 0 && digitalRead(S_Orta) == 1 && digitalRead(S_Sag) == 0) {
    ileri();
  }
  if (digitalRead(S_Sol) == 1 && digitalRead(S_Orta) == 0 && digitalRead(S_Sag) == 0) {
    sol();
  }
  if (digitalRead(S_Sol) == 0 && digitalRead(S_Orta) == 0 && digitalRead(S_Sag) == 1) {
    sag();
  }
  delay(25);
  dur();
  delay(25);
  */
  
  if(digitalRead(S_Sol) == 1 && digitalRead(S_Sag) ==1){  // Orta sensör çizgiyi gördüğünde robot ileri gitsin.
    ileri();
  }
   
  if(digitalRead(S_Sol) == 1  && digitalRead(S_Sag) == 0){  // Sağ sensör çizgiyi gördüğünde robot sağa dönsün.
    sag();
  }
  if(digitalRead(S_Sol) == 0  && digitalRead(S_Sag) == 1){  // Sol sensör çizgiyi gördüğünde robot sola dönsün.
    sol();
  }

  delay(25);
  dur();
  delay(25);
  
  /*if (uzaklik < 15) {
    sag();
    delay(50);
    dur();
    delay(50);

  }
  */
}

