#include <SPI.h>
#include <SD.h>

const int rainSensorPin = A1; 

File myFile;

void setup() {
  Serial.begin(9600);

  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    while (1);
  }
  Serial.println("Initialization done.");
}

bool isRaining = false;

void loop() {
  myFile = SD.open("temp.txt", FILE_WRITE);

  if (myFile) {
    float temperatureF = analogRead(A0) * 500.0 / 1024.0;
    float temperatureC = (temperatureF - 32) * 5.0 / 9.0;

    int rainSensorValue = analogRead(rainSensorPin);
    
   
    if (rainSensorValue > 500) { 
      isRaining = true;
    } else {
      isRaining = false;
    }

    Serial.print("Writing temperature data to temp.txt...");
    Serial.print("Temp,");
    Serial.print(temperatureC);
    Serial.print(",Rain,");
    Serial.println(isRaining ? "true" : "false");

    myFile.print("Temp,");
    myFile.print(temperatureC);
    myFile.print(",Rain,");
    myFile.println(isRaining ? "true" : "false");

    myFile.close();
    Serial.println("Done.");
  } else {
    Serial.println("Error opening temp.txt");
  }

  delay(3600000);
}
