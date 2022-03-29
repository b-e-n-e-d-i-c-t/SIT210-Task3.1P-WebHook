//Including libraries
#include <JsonParserGeneratorRK.h>
#include <Grove_Temperature_And_Humidity_Sensor.h>



//Defining Pins
#define DHTPIN D6
#define DHTTYPE 11

DHT dht(DHTPIN);


//Our variables that will be used to store data in
double temperature;
double humidity;

//The payload function
void postEvent(double temperature, double humidity){
    JsonWriterStatic<256> jw;
    {
        JsonWriterAutoObject obj(&jw);
        jw.insertKeyValue("temperature", temperature);
        jw.insertKeyValue("humidity", humidity);
    }
    Particle.publish("dht11", jw.getBuffer(), PRIVATE);
}
int led = D7;

//DHT begin
void setup() {

    
    Serial.begin(9600);
    Serial.println("DHT TESTER");
    Particle.publish("state", "DHT test start");
    
    dht.begin();
    pinMode(DHTPIN, INPUT);
    

}
//Getting the data
//Posting the data as a payload
//Repeat every 30 seconds
void loop() {

    temperature = dht.getTempCelcius();
    humidity = dht.getHumidity();
    postEvent(temperature, humidity);
    delay(30000);
    
}