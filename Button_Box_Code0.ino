/*

  Biyoloj Button Box Yarışma Kodu

  Buton kutusu için yazılmış yarışma kodlarından birisidir
  Diğer kodlar için https://github.com/rutkay22/Button_Box

  Açıldıktan sonra yarışmacılardan birinin cevap verdiği, cevap veren yarışmacının
  puanı ile sadece bir kere oynanabildiği ve tekrar cevap vermek için moderatör
  izni gerektiren 3 aşamalı basit kod

  Açılış
    Açılış animasyonu
    Ekranın gelmesi
    Puanlar default olarak 0'dır

  1. aşama
     Yarışmacılardan birinin cevap vermesi 
     İlgili led(ler)in yanması
     Buzzer aktivitesi
     Sadece ilgili yarışmacının butonu işler
     Ekranda "C" harfi ve bir Blink gözükür

  2.aşama
     Moderatör puan ile sadece bir kere oynayabilir.
     Ledler söner, ekran yenilenir ve temizlenir
     Yarışmacı butonları işlemez

  3. aşama
     Moderatör önündeki butonlardan biri ile soru sorma izni verir
      => 1. aşama

   Pinler değişken tanımlamalarda belirtilmiştir.

   25 Kasım 2017'de
   Arda Rutkay Var tarafından
   düzenlendi. 
 */

#include <LiquidCrystal.h> //Liquid Crystal kütüphanesi eklendi

LiquidCrystal lcd(22, 23, 24, 26, 28, 30, 32, 34, 36, 38, 40); //Lcd tanıtıldı


const int P1 = 8; // Oyuncu 1 cevap verme buton pini
const int P1arti = 7; // Oyuncu 1 puan arttırma buton pini
const int P1eksi = 6; // Oyuncu 1 puan azaltma buton pini
const int P1R = 5; // Oyuncu 1 puan resetleme buton pini
const int P2 = 9; // Oyuncu 2 cevap verme buton pini
const int P2arti = 2; // Oyuncu 2 puan arttırma buton pini
const int P2eksi = 3; // Oyuncu 2 puan azaltma buton pini
const int P2R = 4; // Oyuncu 2 puan resetleme buton pini
const int led1 = 44; // Oyuncu 1 led pini
const int led2 = 46; // Oyuncu 2 led pini 
const int buzzer = 42; // Ortak buzzer pini

int p1d = 0; // Oyuncu 1 puan değişkeni def == 10
int p2d = 0; // Oyuncu 2 puan değişkeni def == 10

int p1s; // Oyuncu 1 puan arttırma buton değişkeni
int p2s; // Oyuncu 2 puan arttırma buton değişkeni

int p1arti; // Oyuncu 1 puan arttırma buton değişkeni
int p2arti; // Oyuncu 2 puan arttırma buton değişkeni

int p1eksi; // Oyuncu 1 puan azaltma buton değişkeni
int p2eksi; // Oyuncu 2 puan azaltma buton değişkeni

int p1R; // Oyuncu 1 puan resetleme buton değişkeni
int p2R; // Oyuncu 2 puan resetleme buton değişkeni


int sayac1; // 2. oyuncu bastığında 1 değerini alacak sayaç
int sayac2; // 2. oyuncu bastığında 1 değerini alacak sayaç
int soru_sayaci; // 2. kademede yarışmacı butonlarını deaktif edecek sayaç

void bekletme() { // Yarışmacılardan birinin puanı değiştirildiğinde ledleri kapatacak fonksiyon
  digitalWrite(led1, LOW); // Oyuncu ledleri kapatıldı
  digitalWrite(led2, LOW); 
  sayac1 = 0; // Oyuncu sayaçları sıfırlandı
  sayac2 = 0;
  soru_sayaci = -1; //Soru sayacı yarışmacı butonları deaktif etti
}

void baslama() { //Başlama animasyonu
  lcd.clear();
  lcd.print("Welcome to box");
  delay(1500);
  lcd.clear();
  lcd.print("Box will ready");
  lcd.setCursor(0, 1);
  lcd.print("in 5 sc");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 4 sc");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 3 sc");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 2 sc");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 1 sc");
  delay(150);
  lcd.clear();
  delay(175);
  digitalWrite(buzzer, HIGH);
  lcd.print("Ready");
  delay(425);
  lcd.clear();
  digitalWrite(buzzer, LOW);
}

void neutral_ekran() { //Ekranda puanların yazdırılacağı temiz ekran
  lcd.clear();
  lcd.print("P1 point: ");
  lcd.setCursor(10, 0);
  lcd.print(p1d);
  lcd.setCursor(0, 1);
  lcd.print("P2 point: ");
  lcd.setCursor(10, 1);
  lcd.print(p2d);
  lcd.noBlink();
}

void cevap_ekran() { //İkinci aşama ekranı
  lcd.setCursor(15, 0);
  lcd.print("C");
  lcd.setCursor(15, 1);
  lcd.blink();
}

void soru_ekran() { //Üçüncü aşama ekranı
  lcd.clear();
  lcd.print("P1 point: ");
  lcd.setCursor(10, 0);
  lcd.print(p1d);
  lcd.setCursor(0, 1);
  lcd.print("P2 point: ");
  lcd.setCursor(10, 1);
  lcd.print(p2d);
  lcd.setCursor(15, 0);
  lcd.print("S");
  lcd.setCursor(15, 1);
  lcd.blink();
}



void player2() { //Player 2 ile ilgili işlemleri yapan fonksiyon bloğu
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  sayac1 = 0;
  sayac2 = 1;
}

void player1() { //Player 1 ile ilgili işlemleri yapan fonksiyon bloğu
  digitalWrite(led2, LOW);
  digitalWrite(led1, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  sayac1 = 1;
  sayac2 = 0;
}


void setup() {
  pinMode(P1, INPUT); //Pinmode tanıtma
  pinMode(P1arti, INPUT);
  pinMode(P1eksi, INPUT);
  pinMode(P2R, INPUT);
  pinMode(P2, INPUT);
  pinMode(P2arti, INPUT);
  pinMode(P2eksi, INPUT);
  pinMode(P2R, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2); //Lcd ekran başlatma
  baslama(); //Başlama animasyonu
  Serial.begin(9600); //Debug için seri ekran
  neutral_ekran(); //Ekranın nötral konuma geçmesi
}

void loop() {

  p1s = digitalRead(P1); //Butonların okunması
  p2s = digitalRead(P2);
  p1arti = digitalRead(P1arti);
  p2arti = digitalRead(P2arti);
  p1eksi = digitalRead(P1eksi);
  p2eksi = digitalRead(P2eksi);
  p1R = digitalRead(P1R);
  p2R = digitalRead(P2R);


  if (p2s == HIGH and soru_sayaci == 0 and sayac1 == 0) //1. oyuncu soru sayaci 0 ve diğer oyuncu basmadan basar ise
    player2(); // Player 2 fonksiyonu

  if (p1s == HIGH and soru_sayaci == 0 and sayac2 == 0) //2. oyuncu soru sayaci 0 ve diğer oyuncu basmadan basar ise
    player1(); // Player 1 fonksiyonu


  while (sayac1 == 1) { //döngüye girildi
    Serial.println("Birinci oyuncu dongusu"); //debug işlemi başlatıldı
    p1arti = digitalRead(P1arti); //1. oyuncu arttırma butonu okundu %okunmadığı halde...
    p1eksi = digitalRead(P1eksi); //1. oyuncu eksiltme butonu okundu % ... dongu sonsuz ...
    p1R = digitalRead(P1R); //1. oyuncu reset butonu okundu %... donguye girer
    cevap_ekran();
    if (p1arti == HIGH) { //eğer 1. oyuncu arttırma butonu high oldu ise
      p1d = p1d + 10; // oyuncu puanı 10 arttırıldı
      bekletme(); // bekletme fonksiyonu ile ledler söndürüldü ve sayaç sıfırlandı
      Serial.println("if dongusu"); //debug işlemi
      neutral_ekran(); //ekrandaki yazı yenilendi
      while (p1arti == HIGH) { //buton döngüsü devam etti
        Serial.println("Ikincil while dongusu"); //debug işlemi
        p1arti = digitalRead(P1arti); //1. oyuncu arttırma butonu tekrar okundu (yoksa sonsuz dongu)
        if (p1arti == LOW) //butondan el çekildiği anda
          break; //butona basılma ile ilgili döngü kırıldı
      }
    }
    if (p1eksi == HIGH) { //eğer eksiltme butonuna basıldı ise
      p1d = p1d - 10; //oyuncu puanı 10 azaltıldı
      bekletme(); //bekletme fonksiyonu ile ledler söndürüldü
      Serial.println("Eksiltme while dongusu"); //debug işlemi gerçekleştirildi
      neutral_ekran(); //ekrandaki yazı yenilendi
      while (p1eksi == HIGH) { //buton döngüsü devam etti
        Serial.println("Eksiltme while dongusu"); //debug  işlemi
        p1eksi = digitalRead(P1eksi); //buton sonsuz döngüye girmemek için okundu
        if (p1eksi == LOW) //eğer butondan el çekilirse
          break; //döngü kırıldı
      }
    }
    if (p1R == HIGH) { //eğer resetleme butonuna basıldı ise
      p1d = 0; //oyuncu puanı sıfırlandı
      bekletme(); //bekletme fonc.ile ledler söndürüldü
      Serial.println("Neutral while"); //debug işlemi gerçekleştirildi
      neutral_ekran(); //ekrandaki yazı yenilendi
      while (p1R == HIGH) { //döngü devam etti
        Serial.println("2nd neutral while"); //debug işlemi
        p1R = digitalRead(P1R); //buton tekrar okundu
        if (p1R == LOW) //butondan el çekilirse
          break; //döngü kırılsın
      }
    }
  }



  while (sayac2 == 1) { //döngüye girildi
    Serial.println("İkinci oyuncu dongusu"); //debug işlemi başlatıldı
    p2arti = digitalRead(P2arti); //2. oyuncu arttırma butonu okundu %okunmadığı halde...
    p2eksi = digitalRead(P2eksi); //2. oyuncu eksiltme butonu okundu % ... dongu sonsuz ...
    p2R = digitalRead(P2R); //2. oyuncu reset butonu okundu %... donguye girer
    cevap_ekran();
    if (p2arti == HIGH) { //eğer 2. oyuncu arttırma butonu high oldu ise
      p2d = p2d + 10; // oyuncu puanı 10 arttırıldı
      bekletme(); // bekletme fonksiyonu ile ledler söndürüldü
      Serial.println("if dongusu"); //debug işlemi
      neutral_ekran(); //ekrandaki yazı yenilendi
      while (p2arti == HIGH) { //buton döngüsü devam etti
        Serial.println("Ikincil while dongusu"); //debug işlemi
        p2arti = digitalRead(P2arti); //1. oyuncu arttırma butonu tekrar okundu (yoksa sonsuz dongu)
        if (p2arti == LOW) //butondan el çekildiği anda
          break; //butona basılma ile ilgili döngü kırıldı
      }
    }
    if (p2eksi == HIGH) { //eğer eksiltme butonuna basıldı ise
      p2d = p2d - 10; //oyuncu puanı 10 azaltıldı
      bekletme(); //bekletme fonksiyonu ile ledler söndürüldü
      Serial.println("Eksiltme while dongusu"); //debug işlemi gerçekleştirildi
      neutral_ekran(); //ekrandaki yazı yenilendi
      while (p2eksi == HIGH) { //buton döngüsü devam etti
        Serial.println("Eksiltme while dongusu"); //debug  işlemi
        p2eksi = digitalRead(P2eksi); //buton sonsuz döngüye girmemek için okundu
        if (p2eksi == LOW) //eğer butondan el çekilirse
          break; //döngü kırıldı
      }
    }
    if (p2R == HIGH) { //eğer resetleme butonuna basıldı ise
      p2d = 0; //oyuncu puanı sıfırlandı
      bekletme(); //bekletme fonc.ile ledler söndürüldü
      Serial.println("Neutral while"); //debug işlemi gerçekleştirildi
      neutral_ekran(); //ekrandaki yazı yenilendi
      while (p2R == HIGH) { //döngü devam etti
        Serial.println("2nd neutral while"); //debug işlemi
        p2R = digitalRead(P2R); //buton tekrar okundu
        if (p2R == LOW) //butondan el çekilirse
          break; //döngü kırılsın
      }
    }
  }




  while (soru_sayaci == -1) { // Soru sayacı -1 ise
    p1arti = digitalRead(P1arti); //Buton okuması
    p2arti = digitalRead(P2arti);
    p1eksi = digitalRead(P1eksi);
    p2eksi = digitalRead(P2eksi);
    p1R = digitalRead(P1R);
    p2R = digitalRead(P2R);
    if (p1arti == HIGH or p1eksi == HIGH or p1R == HIGH or p2arti == HIGH or p2eksi == HIGH or p2R == HIGH) { //eğer herhangi bir butona basılırsa
      soru_ekran(); //ekranı yenileme
      soru_sayaci = 0; //sayacı değiştirme
      break;
    }
  }
}
