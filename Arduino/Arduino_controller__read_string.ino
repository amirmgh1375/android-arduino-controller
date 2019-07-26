#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 16

bool doSendAnalog = true;

void setup()
{
  Serial.begin(38400);
  for (int i = 1; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
}

void loop()
{
  // Receiving Data
  if (Serial.available())
  {
    int pin, value = 0;

    String input = Serial.readString();
    // Looping over input-string lines
    while (input.length()) {
      // Extracting a line
      int lineIndex = input.indexOf('\n');
      String line = input.substring(0, lineIndex);

      if (line == 'DisableAnalog') doSendAnalog = false;
      
      // Processing the line
      String pinValue = line.substring(3);
      pinValue.trim();
      value = pinValue.substring(pinValue.indexOf(',') + 1).toInt();
      String _pin = pinValue.substring(0, pinValue.indexOf(','));
      if (_pin == "ALL") {
        for (int i = 2; i < 14; i++) {
          digitalWrite(i, value);
        }
      }
      else {
        pin = _pin.toInt();
        digitalWrite(pin, value);
      }



      // Remove Processed line from input string
      input.remove(0, lineIndex + 1);
    }
  }
  sendAndroidValues();
}

void sendAndroidValues()
{
    float voltageValues [6] = {0}; 
    // Getting Voltage Values
    for (int x = 0; x < 6; x++)
    {
      Serial.println(String("PORT"+String(x)+","+String(((float) analogRead(x))*5/1023)));
    }
  
    delay(200);
}
