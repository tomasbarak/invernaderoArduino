#include <stdio.h>
#include <string.h>
void setup() {
  Serial.begin(9600);

}

char **parseData(String rawData){

}

void loop() {
    char str[] = "40,50,1000,15";
    char *strP[] = {"", "", "", ""};
    // Returns first token
    char* token = strtok(str, ",");

    int contador = 0;
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL) {
        strP[contador] = token;
        //Serial.println(strP[contador]);
        token = strtok(NULL, ",");
        contador++;
    }

    for(int i = 0; i < 4; i++){
      Serial.println(strP[i]);
    }

}
