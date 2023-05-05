/*
 Making a thermometer with lcd screen that shows temperature in Celsius
 * VSS->5v
 * VDD->GND
 * V0->GND
 * RS->12
 * RW->GND
 * E->11
 * D4->3
 * D5->4
 * D6->5
 * D7->6
 * A->5v with 220 ohm
 * K->GND
 * DS18B20 temp yellow with 4.7k ohm -> 7
  */

//Include the required Arduino libraries
#include <DallasTemperature.h>
//this library supports DS18B20,
// documentation can be found in https://www.arduinolibraries.info/libraries/dallas-temperature

#include <LiquidCrystal.h>
//this library allows communication with LCDs.
// documentation can be found in https://www.arduino.cc/reference/en/libraries/liquidcrystal/ 

#include <OneWire.h>
//this library allows the access to 1-wire temperature sensor
// documentation can be found in https://www.arduinolibraries.info/libraries/one-wire 

//Define to which pin of the Arduino the DQ pin is connected
//DQ pin means data pin
//the bus refers to the family of integrated circuits we are communicating between
#define ONE_WIRE_BUS 7

//Create a new instance of the oneWire class to communitecate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

//Pass the onwWire reference to DallassTemperature library
DallasTemperature sensors(&oneWire);

//Show which lcd pins are using
LiquidCrystal lcd(12,11,5,4,3,2);

//Degree symbol
byte degree[8] =
{
  0b00011,
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup(void) 
{
  //Begin lcd screen (2 rows and 16 columnns)
  lcd.begin(16, 2);
  //create the custom character on the first row of the lcd screen
  lcd.createChar(0, degree);
  //Start up the library of sensor
  sensors.begin();
  Serial.begin(9600);
}

void loop(void) 
{
  //Send the command for all devices on the bus 
  sensors.requestTemperatures();
  //Index means a guide, list or sign, or a number used to measure change
  //Index 0 refers to the first device 
  //Float means floating-point number that has a decimal point
  //Read temperature in Celscius
  float tempC = sensors.getTempCByIndex(0);
  //Start to print at the first row
  lcd.setCursor(0,0);
  //Print the letter "Temperature:"
  lcd.print("Temperature:");
  //Start to print at the second row
  lcd.setCursor(0,1);
  //Print the temperature which is given in number
  lcd.print(tempC);
  //Print the custom character
  lcd.write(byte(0));
  //Print the figure of Celscius
  lcd.print("C");
  Serial.println(tempC);
  //Wait for 1 second
  delay(2000);
}