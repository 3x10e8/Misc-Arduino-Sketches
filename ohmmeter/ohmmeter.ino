/* Simple Ohmmeter Based On Voltage Divider
 *  Tested on Adalogger (SAMD21)
 *  Should work on other boards through the Arduino IDE
 *  
 *  Idea from http://www.circuitbasics.com/arduino-ohm-meter/
 *  
 *  Schematic and Equations:
 *  SUPP    R1 = unknown
 *    ^---/\/\/\---o----------<ADC|     Vadc =  3.3 *R2/(R1+R2)
 *                 |                 R1*Vadc = (3.3 -Vadc)*R2
 *                 |    R2 = 1kohms       R1 = (3.3 -Vadc)*R2/Vadc
 *                 o--/\/\/\--o                         
 *                            |                        
 *                            |
 *                            GND
 */
 
#define AVERAGE 100 // how many samples for running average
#define READ_PIN 4  // ADC input AIN4

float const R2 = 1000; // reference resistor
float const Vsupply = 3.3; // could change to 5V 
int Vread[AVERAGE]; // array for storing ADC samples
int ndx = 0, tmp = 0, tndx = 0;

void setup() {
  pinMode(13, OUTPUT); // LED pin
  Serial.begin(9600); while (!Serial);
  Serial.println("~~Ohmmeter~~");
  digitalWrite(13, HIGH); // lights up
}

void loop() {
  Vread[ndx] = analogRead(READ_PIN);

  // running average
  for (tmp = 0, tndx = 0; tndx < AVERAGE; tndx++) { 
    tmp += Vread[tndx];
  }
  float Vadc = ((float)tmp) / AVERAGE / 1024.0 * V3v3;
  
  // change ADC ref for higher res
    // make equivalent: https://www.arduino.cc/en/Reference/AnalogReference

  // print results to serial
  Serial.print(Vread[ndx]);
  Serial.print("\t");
  Serial.print(Vadc);
  Serial.print("\t");
  Serial.println((Vsupply -Vadc)*R2/Vadc);

  ndx++;
  if (ndx == AVERAGE) ndx = 0; // re-index the buffer

}
