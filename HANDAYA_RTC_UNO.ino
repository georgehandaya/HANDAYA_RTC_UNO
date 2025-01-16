#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

// Inisialisasi RTC
RTC_DS3231 rtc;

// Inisialisasi LCD (opsional)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin untuk sensor kecepatan
const int speedSensorPin = 2;

// Variabel untuk menghitung kecepatan
volatile unsigned long lastTime = 0;
volatile unsigned long currentTime;
volatile float speed;

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);

  // Inisialisasi RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // Set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Inisialisasi LCD (opsional)
  lcd.begin(16, 2);
  lcd.print("Speed: ");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  // Inisialisasi sensor kecepatan
  pinMode(speedSensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(speedSensorPin), calculateSpeed, RISING);
}

void loop() {
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();

  // Tampilkan waktu dan kecepatan di Serial Monitor
  Serial.print("Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.print(" Speed: ");
  Serial.print(speed);
  Serial.println(" km/h");

  // Tampilkan waktu dan kecepatan di LCD (opsional)
  lcd.setCursor(6, 1);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());
  lcd.setCursor(7, 0);
  lcd.print(speed);
  lcd.print(" km/h");

  delay(1000); // Perbarui setiap 1 detik
}

void calculateSpeed() {
  currentTime = millis();
  unsigned long timeDifference = currentTime - lastTime;
  
  // Misalkan keliling roda adalah 1 meter
  float wheelCircumference = 1.0; // meter
  
  // Hitung kecepatan dalam km/h
  speed = (wheelCircumference / timeDifference) * 3600.0;
  
  lastTime = currentTime;
}