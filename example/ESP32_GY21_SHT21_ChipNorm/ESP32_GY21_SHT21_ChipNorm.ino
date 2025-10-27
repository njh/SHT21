#include <ChipNorm_SHT21.h>

#define SCL 22 //SCL mit D22 verbinden
#define SDA 21 //SDA mit D21 verbinden

ChipNorm_SHT21 sht21(SCL, SDA); //Initialisiert den Sensor (Objekt sht21 der Klasse ChipNorm_SHT21 erstellt) 

void setup() {
  Serial.begin(9600); // Serielle Kommunikation initialisieren - 9600 bits pro Sekunde
  
  // Initialisiert den SHT21-Sensor
  if (!sht21.begin()) {
    Serial.println("Fehler beim Initialisieren des SHT21-Sensors!");
    delay(1000);
    while (true); // Stoppt das Programm bei einem Fehler.
  }
  Serial.println("SHT21 Sensor initialisiert.");
}

void loop() {
  float temperature = sht21.readTemperature(); // Auslesen der Temperatur
  float humidity = sht21.readHumidity(); // Auslesen der Feuchtigkeit

  // Prüft auf Lesefehler (falls NAN zurückgegeben wurde).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Fehler beim Lesen der Sensorwerte!");
  } else {
    // Ausgabe der Messwerte
    Serial.print("Temperature: ");
    Serial.print(temperature, 1); // Ausgabe Temperautur mit einer Dezimalstelle
    Serial.println("°C");
    Serial.print("Humidity: ");
    Serial.print(humidity, 1); // Ausgabe Feuchtigkeit mit einer Dezimalstelle
    Serial.println("%");
    Serial.println("");
  }
  
  delay(1000);  // Wartet 1 Sekunde
}
