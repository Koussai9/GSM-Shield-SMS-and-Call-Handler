#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include "call.h"
SMSGSM sms;
CallGSM callGSM;
 
int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];
 
void setup()
{
     //Serial connection. 
     Serial.begin(9600);
     Serial.println("GSM Shield testing.");
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.
     if (gsm.begin(2400)) {
          Serial.println("\nstatus=READY");
          started=true;
     } else Serial.println("\nstatus=IDLE");
 
     if(started) {
          if (sms.SendSMS("********", "Arduino SMS"))
          Serial.println("\nSMS sent OK");
          callGSM.Call("********");
     }
 
};
 
void loop()
{
     if(started) {
          //Read if there are messages on SIM card and print them.
        //deprecated method
        if(gsm.readSMS(smsbuffer, 160, n, 20)) {
               Serial.println(n);
               Serial.println(smsbuffer);
          }
         
          //get 1st sms
          sms.GetSMS(1,n,20,smsbuffer,160);
          Serial.println(n);
          Serial.println(smsbuffer);
          
          delay(1000);
     }
};