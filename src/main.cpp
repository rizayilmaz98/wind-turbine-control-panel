#include <Arduino.h>
#include <LiquidCrystal.h>
#include <IRremote.h>
#include <math.h>

int RECV_PIN = 2;
decode_results results;
IRrecv irrecv(RECV_PIN);

#define BUTON1 0xFFA25D
#define BUTON2 0xFF629D
#define BUTON3 0xFFE21D
#define BUTON4 0xFF22DD
#define BUTON5 0xFF02FD
#define BUTON6 0xFFC23D
#define BUTON7 0xFFE01F
//#define BUTON8 0xFFA857
//#define BUTON9 0xFF906F
//#define BUTON0 0xFF9867
//#define BUTONY 0xFF6897
//#define BUTONK 0xFFB04F
//#define BUTONSO 0xFF10EF
//#define BUTONSA 0xFF5AA5
//#define BUTONA 0xFF4AB5
//#define BUTONY 0xFF18E7
#define BUTONOK 0xFF38C7

#define gerilim A0

int deger1 = 0;
int deger2 = 0;
float voltdeger = 0.00;
float akimdeger = 0.00;
float gucdeger = 0.00;
float ruzgarhiz1, ruzgarhiz2;

int rs = 13 , en = 12, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void menuEkrani() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DEGERLER MENUSU");
  lcd.setCursor(0, 1);
  lcd.print("1.Anlik Voltaj");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("2.Anlik Akim");
  lcd.setCursor(0, 1);
  lcd.print("3.Anlik Guc");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("4.Batarya Durum");
  lcd.setCursor(0, 1);
  lcd.print("5.Ruzgar Durum");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("6.Sistem Durum");
  lcd.setCursor(0, 1);
  lcd.print("7.Hakkimizda");
}

void anlikGerilim() {
  deger1 = analogRead(A0);
  voltdeger = ((5.00 / 1024.00) * deger1) * 11;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KERT Voltaj:");
  lcd.setCursor(0, 1);
  lcd.print(voltdeger);
  lcd.print("V");
}
void anlikAkim() {
  deger1 = analogRead(A0);
  akimdeger = (deger1 * (5.00 / 1024.00)) / 10;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KERT Akim:");
  lcd.setCursor(0, 1);
  lcd.print(akimdeger);
  lcd.print("mA");
}
void anlikGuc() {
  deger1 = analogRead(A0);
  voltdeger = ((5.00 / 1024.00) * deger1) * 11;
  akimdeger = voltdeger / 10;
  gucdeger = voltdeger * akimdeger;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KERT Guc:");
  lcd.setCursor(0, 1);
  lcd.print(gucdeger);
  lcd.print("mW");
}
void pilDurum() {
  deger1 = analogRead(A0);
  voltdeger = ((5.00 / 1024.00) * deger1) * 11;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Batarya Durum:");
  if (voltdeger >= 5) {
    lcd.setCursor(0, 1);
    lcd.print("Sarj oluyor");
  }
  if (voltdeger < 5) {
    lcd.setCursor(0, 1);
    lcd.print("Sarj olmuyor!!!");
  }
}
void ruzgarDurum() {
  deger1 = analogRead(A0);
  voltdeger = ((5.00 / 1024.00) * deger1) * 11;
  akimdeger = voltdeger / 10;
  gucdeger = voltdeger * akimdeger;
  ruzgarhiz1 = 2 * gucdeger / (1.225 * 0.59 * 0.85);
  ruzgarhiz2 = pow(ruzgarhiz1, 1 / 3);
  if (gucdeger == 0.00) {
    ruzgarhiz2 = 0.00;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R. Hizi:");
  lcd.print(ruzgarhiz2);
  lcd.print("m/s");
  if (ruzgarhiz2 < 2.53) {
    lcd.setCursor(0, 1);
    lcd.print("VERIMSIZ");
  }
  if (ruzgarhiz2 > 2.53) {
    lcd.setCursor(0, 1);
    lcd.print("VERIMLI");
  }
}
void sistemDurum() {
  deger1 = analogRead(A0);
  voltdeger = ((5.00 / 1024.00) * deger1) * 11;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistem Durum:");
  if (voltdeger ==  0.00) {
    lcd.setCursor(0, 1);
    lcd.print("Sistem Tuketiyor");
  }
  if (voltdeger > 0.00) {
    lcd.setCursor(0, 1);
    lcd.print("Sistem Uretiyor");
  };
}
void hakkimizda() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DONGEL AAES L.S.");
  lcd.setCursor(0, 1);
  lcd.print("KERT Projesi");
}

void setup() {
  Serial.begin(19200);
  lcd.begin(16, 2);
  irrecv.enableIRIn();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KERT 1.1 PROJESI");
  lcd.setCursor(0, 1);
  lcd.print("   HOSGELDIN!");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KERT 1.1 PROJESI");
  lcd.setCursor(0, 1);
  lcd.print(" MENU ICIN 'OK'");

  while (1) {
    if (irrecv.decode(&results)) {
      if (results.value == BUTON1) {
        anlikGerilim();
      }
      if (results.value == BUTON2) {
        anlikAkim();
      }
      if (results.value == BUTON3) {
        anlikGuc();
      }
      if (results.value == BUTON4) {
        pilDurum();
      }
      if (results.value == BUTON5) {
        ruzgarDurum();
      }
      if (results.value == BUTON6) {
        sistemDurum();
      }
      if (results.value == BUTON7) {
        hakkimizda();
      }
      if (results.value == BUTONOK) {
        menuEkrani();
      }
      irrecv.resume();
    }
  }
}
