#include "Sensor.h"
#include "can.h"
#include "UART.h"
UART uart;
bool isValid(uint8_t distance_1, uint8_t distance_2)
{
    if(distance_1 >= distance_2)
        return (distance_1 - distance_2) < DISTANCE_TOLERANCE;
    else
        return (distance_2 - distance_1) < DISTANCE_TOLERANCE;
}

Sensor::Sensor(volatile uint8_t &port, uint8_t pin) : Component(port, pin, IN)
{
}
// read 1 value and return most accurate
uint8_t Sensor::getDistance()
{
    CAN can;
    uint16_t lecture = can.lecture(getPin()); //We ignore the 2 least significant bits
    float voltage = lecture * (5.0f / 1023.0f);                          //remap to voltage limits
    if (voltage <= 0.1f)
        return 80; //if the voltage is near 0 return max distance
    if (voltage == 0.23)
		voltage = 0.23001;                                   //to avoid divison by 0
    uint8_t distance = static_cast<uint8_t>(20.4f / (voltage - 0.23));
    return distance; //20.4 is the slope of curve on the datasheet, 0.23 corresponds to x=0 of the curve
}
// read many values and return most accurate
uint8_t Sensor::getAverageDistance()
{
    uint16_t sum = 0;
    for (uint8_t i = 0; i < SENSOR_REPETITION; i++)
    {
        sum += getDistance();   //calculate sum of entries
        if (getDistance() >= 80){
			return 80;
		}
    }
    return sum / SENSOR_REPETITION; //average of entries
}

uint8_t Sensor::getPin()
{
    return LSP_;
}
uint8_t Sensor::getStableDistance(){
    uint8_t d1 = getAverageDistance();
    uint8_t d2 = getAverageDistance();
    while(!isValid(d1, d2)){
        d1 = getAverageDistance();
        d2 = getAverageDistance();
    }
    return d1;
}
