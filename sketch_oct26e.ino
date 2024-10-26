#include <SoftwareSerial.h>  
#define rx 5                              
#define tx 4        
int count = 0;
String id;
String lastId = "";  // Store the last processed ID
char input[13];
SoftwareSerial myserial(rx, tx);
                         
void setup()
{
  Serial.begin(9600);   // Start serial communication with Arduino  
  myserial.begin(9600);  // Start software serial communication (RFID reader)
}

void loop()
{
   if(myserial.available())
   {
      count = 0;
      while(myserial.available() && count < 12)  // Read 12 characters from RFID
      {
         input[count] = myserial.read();
         count++;
         delay(5);
      }

      id = String(input);  // Convert the input array to a string
   }

   // Only process if the current ID is different from the last processed one
   if(id != "" && id != lastId)
   {
      if(id == "4C003D07F781")  // Example RFID tag
      {
         Serial.print("CYCLE_1");  // Send command to Arduino to rotate
      }
      else if(id == "4C003D13A2C0")
      {
         Serial.print("CYCLE_2");
      }
      else if(id == "4C003D055226")
      {
         Serial.print("CYCLE_3");
      }

      lastId = id;  // Store the last processed ID
   }

   delay(500);  // Avoid rapid looping
}