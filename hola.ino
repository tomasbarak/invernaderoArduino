#include <Adafruit_Sensor.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#define ventiluz 46
#define ventilador 10
#define botonesDisplay A0
#define sensorHumedadTierra A15
#define bomba 11
#define calefaccion 12
#define sensorLuz 51
#define sensorTemp 31
DHT dht(31, DHT11);
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

Servo motorVentiluz;

void setup() {

  motorVentiluz.attach(ventiluz);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.clear();
  dht.begin();
}

void loop(){
  // put your main code here, to run repeatedly:
  int displayButtonPressed;
  float temperatura;
  float humedadAmbiente;
  int humedadTierra = analogRead(sensorHumedadTierra);
  int luz;
 
  int seccionDePrograma;
  // 0 = No mostrar nada
  // 1 = Mostrar Humedad y temperatura ambiente
  // Leemos la humedad relativa
  humedadAmbiente = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  temperatura = dht.readTemperature();
 
  displayButtonPressed = analogRead(botonesDisplay);
  if(displayButtonPressed < 50){
    //derecha
    seccionDePrograma = 1;
  }else if(displayButtonPressed < 150){
    //Arriba
    seccionDePrograma = 2;
  }else if(displayButtonPressed < 270){
    //Abajo
    lcd.print("Abajo");
  }else if(displayButtonPressed < 600){
    //Izquierda
    lcd.print("Izquierda");
  }else if(displayButtonPressed < 800){
    //Select
    seccionDePrograma = 0;
  }
  
  humedadTierra = map(humedadTierra, 1023, 0, 0, 100);
  if(seccionDePrograma == 1){
    lcd.print("T: " + String(temperatura) + " H: " + String(humedadAmbiente));
  }else if(seccionDePrograma == 2){
    lcd.print("HT: " + String(humedadTierra));
  }
  //Serial.println(displayButtonPressed);
  Serial.println(humedadTierra);
  if(seccionDePrograma != 0){
    delay(1000);
  }
  lcd.clear();
}
