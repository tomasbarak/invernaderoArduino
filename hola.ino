#include <Adafruit_Sensor.h>
#include <Servo.h>
#include <DHT.h>

#define RGB_green 9
#define RGB_red 10
#define RGB_blue 11
#define ventiluz 6
#define ventilador 10
#define sensorHumedadTierra A0
#define bomba 11
#define calefaccion 12
#define sensorLuz 4
#define sensorTemp 2
DHT dht(sensorTemp, DHT11);

Servo motorVentiluz;

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  motorVentiluz.attach(ventiluz);
  Serial.begin(9600);
  pinMode(sensorLuz, INPUT);
  dht.begin();
}

void loop(){
  // put your main code here, to run repeatedly:
  int humedadTierra = analogRead(sensorHumedadTierra);
  
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

  if(temperatura > 24.00){
    motorVentiluz.write(90);
  }else motorVentiluz.write(0);
  
  if(temperatura > 26.00){
      digitalWrite(12, LOW);   
      Serial.println("Temp Alta");
  }else{
      Serial.println("Temp Baja");
      digitalWrite(12, HIGH);  
  }

  if(luz < 17.00){
    digitalWrite(RGB_green, LOW);
    digitalWrite(RGB_blue, LOW);
    digitalWrite(RGB_red, LOW);
  }else{
    digitalWrite(RGB_green, HIGH);
    digitalWrite(RGB_blue, HIGH);
    digitalWrite(RGB_red, HIGH);
  }
  delay(1000);
}
