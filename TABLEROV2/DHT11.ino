#include "header.h"

DHT dht(6, DHT11);

uint8_t DHT_humedad, DHT_temperatura;
float DHT_sensacion;

void DHT_init()
{
    dht.begin();
}
/*
uint8_t DHT_get_humedad()
{
    return DHT_humedad;
}
*/
uint8_t DHT_get_temperatura()
{
    return DHT_temperatura;
}
/*
float DHT_get_sensacion()
{
    return DHT_sensacion;
}*/
void readDHT()    //~300 mS
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    //DHT_humedad = dht.readHumidity();
    // Read temperature as Celsius (the default)
    DHT_temperatura = dht.readTemperature();
    // Compute heat index in Celsius
    //DHT_sensacion = dht.computeHeatIndex(DHT_temperatura, DHT_humedad, false);
}
