// Sketch to take picture on button press
#include <Bridge.h>
#include <Process.h>

// Picture process
Process picture;

// Filename
String filename;

// Pin
int button_pin = 3;
int blue = 2;
int green = 3;
int red = 4;

// Path
String path = "/mnt/sda1/";

void setup() {
  
  // Bridge
  Bridge.begin();
  
  // Set pin mode
  pinMode(button_pin,INPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(red,OUTPUT);
}

void loop(void) 
{
  
  if (analogRead(button_pin) >= 800) {
    
    // Generate filename with timestamp
    filename = "";
    picture.runShellCommand("date +%s");
    while(picture.running());

    while (picture.available()>0) {
      char c = picture.read();
      filename += c;
    } 
    filename.trim();
    filename += ".png";
 
 digitalWrite(red,HIGH);
 delay(1000);
 digitalWrite(red,LOW);
 digitalWrite(blue,HIGH);
 delay(1000);
 digitalWrite(blue,LOW);
 digitalWrite(green,HIGH);
 delay(1000);
 digitalWrite(green,LOW);
 
    // Take picture
    picture.runShellCommand("fswebcam " + path + filename + " -r 1280x720");
    while(picture.running());

  }
}
