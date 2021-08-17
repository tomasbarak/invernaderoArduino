#include <Adafruit_Sensor.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#define ventiluz 3
#define ventilador 10
#define botonesDisplay A0
#define sensorHumedadTierra A0
#define bomba 11
#define calefaccion 12
#define sensorLuz 4
#define sensorTemp 2
DHT dht(sensorTemp, DHT11);

Servo motorVentiluz;

void setup() {
  pinMode(12, OUTPUT);
  motorVentiluz.attach(ventiluz);
  Serial.begin(9600);
  pinMode(sensorLuz, INPUT);
  dht.begin();
}

void loop(){
  // put your main code here, to run repeatedly:
  int displayButtonPressed;
  int humedadTierra = analogRead(sensorHumedadTierra);

  int seccionDePrograma;
  // 0 = No mostrar nada
  // 1 = Mostrar Humedad y temperatura ambiente
  // Leemos la humedad relativa
  float humedadAmbiente = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float temperatura = dht.readTemperature();
 
  int luz = analogRead(sensorLuz);
  humedadTierra = map(humedadTierra, 1023, 0, 0, 100);
  luz = map(luz, 1023, 0, 0, 100);
  
  Serial.println("Humedad: " + String(humedadAmbiente));
  Serial.println("Temperatura: " + String(temperatura));
  Serial.println("Humedad tierra: " + String(humedadTierra));
  Serial.println("Luz: " + String(luz) + "%");
  
  Serial.println(temperatura);
  if(seccionDePrograma != 0){
    delay(1000);
  }

  if(temperatura > 23.50){
      digitalWrite(12, LOW);   
      Serial.println("Temp Alta");
  }else{
      Serial.println("Temp Baja");
      digitalWrite(12, HIGH);  
  }
  delay(1000);
}
