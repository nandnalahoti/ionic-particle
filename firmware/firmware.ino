// This #include statement was automatically added by the Particle IDE.
#include <codetacc-wearables.h>



Adafruit_SI1145 uv = Adafruit_SI1145();

bool init = false;
double ultraviolet;
int infrared;
int visible;
int led2 = D7;

void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit SI1145 test");

  if (uv.begin()) {
      Particle.publish("Ultraviolet sensor found!");
      Particle.variable("uv", ultraviolet);
      Particle.variable("ir", infrared);
      Particle.variable("vis", visible);
      init = true;
  } else {
      Particle.publish("Ultraviolet sensor couldn't be found!");
  }


   // Here's the pin configuration, same as last time
   //pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);

   // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("led",ledToggle);
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

   // For good measure, let's also make sure both LEDs are off when we start:
   //digitalWrite(led1, LOW);
   digitalWrite(led2, LOW);



}

void loop() {
    if (init) {
        ultraviolet = uv.readUV() / 100.0;
        infrared = uv.readIR();
        visible = uv.readVisible();

        if (ultraviolet >=  8.0 && ultraviolet <= 10.0) {
            digitalWrite(led2,HIGH);
        }
        else if (ultraviolet >= 11.0) {
            digitalWrite(led2, HIGH);
        }
        else {
            digitalWrite(led2, LOW);

    }
    delay(1000);





    }
}

//LED INFO!

// -----------------------------------
// Controlling LEDs over the Internet
// -----------------------------------

// First, let's create our "shorthand" for the pins
// Same as in the Blink an LED example:
// led1 is D0, led2 is D7

//int led1 = D0;


// Last time, we only needed to declare pins in the setup function.
// This time, we are also going to register our Particle function



// Last time, we wanted to continously blink the LED on and off
// Since we're waiting for input through the cloud this time,
// we don't actually need to put anything in the loop

//there was a loop here before
   // Nothing to do here


// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Particle.function earlier.


int ledToggle(String command) {
    /* Particle.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */

    if (command=="on") {
        //digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        return 1;
    }
    else if (command=="off") {
        //digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        return 0;
    }
    else {
        return -1;
    }
}