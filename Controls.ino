#include <PS2X_lib.h>
#include <AccelStepper.h>
#include <Servo.h>

PS2X ps2x;
AccelStepper stepper1(AccelStepper::DRIVER,41,37); // pin 53 >PUL-, pin 49 DIR-
AccelStepper stepper2(AccelStepper::DRIVER,33,29); // pin 45 >PUL-, pin 41 DIR-
AccelStepper stepper3(AccelStepper::DRIVER,26,23); // pin 37 >PUL-, pin 33 DIR-  //base
AccelStepper stepper4(AccelStepper::DRIVER,19,18); // pin 29 >PUL-, pin 24 DIR-
AccelStepper stepper5(AccelStepper::DRIVER,8,10); // pin 8 >PUL-, pin 10 DIR-
Servo gripperServo;

const byte gripperPin = 12;
//const int openGripper = 90; // *OPEN ANGLE*
//const int closeGripper = 180; // *CLOSE ANGLE*

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int curPos = 90;
const int dist = 500; 

int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
//Serial.begin(57600);
error = ps2x.config_gamepad(52,51,53,50, true, true);   //GamePad(clock, command, attention, data, Pressures?, Rumble?) 
//error = ps2x.config_gamepad(13,11,10,12, true, true);
/*
if(error == 0){
  Serial.println("Found Controller, configured successful");
  Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
 Serial.println("holding L1 or R1 will print out the analog stick values.");
 Serial.println("Go to www.billporter.info for updates and to report bugs.");
}
 else if(error == 1)
  Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
 else if(error == 2)
  Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
 else if(error == 3)
  Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  type = ps2x.readType(); 
    switch(type) {
      case 0:
       Serial.println("Unknown Controller type");
      break;
      case 1:
       Serial.println("DualShock Controller Found");
      break;
      case 2:
        Serial.println("GuitarHero Controller Found");
      break;
    }*/

    stepper1.setMaxSpeed(200);
    stepper1.setAcceleration(80);
    stepper1.moveTo(1000);

    stepper2.setMaxSpeed(900);
    stepper2.setAcceleration(90);
    stepper2.moveTo(1000);
    
    stepper3.setMaxSpeed(900);
    stepper3.setAcceleration(90);
    stepper3.moveTo(100);

    stepper4.setMaxSpeed(900);
    stepper4.setAcceleration(90);
    stepper4.moveTo(1000);

    stepper5.setMaxSpeed(900);
    stepper5.setAcceleration(90);
    stepper5.moveTo(1000);

    gripperServo.attach(gripperPin);
    gripperServo.write(openGripper); // *gripper open position*
}

void loop(){
  /* You must Read Gamepad to get new values
  Read GamePad and set vibration values
  ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
  if you don't enable the rumble, use ps2x.read_gamepad(); with no values
  you should call this at least once a second
  */
if(error == 1) 
 return; 
if(type == 2){ 
  ps2x.read_gamepad();          //read controller 
}
else { //DualShock Controller
   ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

   /*
   if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
        Serial.println("Start is being held");
   if(ps2x.Button(PSB_SELECT))
        Serial.println("Select is being held");
    if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
     }
     if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
     }
     if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
     }
     if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
     }   
     vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                             //how hard you press the blue (X) button    
   if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
   {   
       if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
       if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
       if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
       if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
       if(ps2x.Button(PSB_GREEN))
        Serial.println("Triangle pressed");
   }   
   if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
        Serial.println("Circle just pressed");
   if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
        Serial.println("Square just released");     
   if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
        Serial.println("X just changed");    
   if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
   {
       Serial.print("Stick Values:");
       Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_LX), DEC); 
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_RY), DEC); 
       Serial.print(",");
       Serial.println(ps2x.Analog(PSS_RX), DEC); 
   } 
}
*/

// Set positions:
// Base motor:
if(ps2x.Button(PSB_L1)){
  //Serial.println("Turn Base Left  <-");
  pos1 = stepper1.currentPosition() - dist;
 
}
else if(ps2x.Button(PSB_R1)){
  //Serial.println("Turn Base Right ->");
  pos1 = stepper1.currentPosition() + dist;
}
else{
  pos1 = stepper1.currentPosition();
}

// Shoulder:
if(ps2x.Analog(PSS_LX)>155){
  //Serial.println("Turn shoulder up ^ ");
  pos2 = stepper2.currentPosition() + dist;
}
else if(ps2x.Analog(PSS_LX)<100){
  //Serial.println("Turn shoulder down ");
  pos2 = stepper2.currentPosition() - dist;
}
else{
  pos2 = stepper2.currentPosition();
}

// Elbow:
if(ps2x.Analog(PSS_LY)>160){
  //Serial.println("Turn elbow down");
  pos3 = stepper3.currentPosition() - dist;
}
else if(ps2x.Analog(PSS_LY)<100){
  //Serial.println("Turn elbow up ^");
  pos3 = stepper3.currentPosition() + dist;
}
else{
  pos3 = stepper3.currentPosition();
}

//Wrist:
if(ps2x.Analog(PSS_RY)>160){
  //Serial.println("Turn wrist down");
  pos4 = stepper4.currentPosition() - dist;
}
else if(ps2x.Analog(PSS_RY)<100){
  //Serial.println("Turn wrist up ^");
  pos4 = stepper4.currentPosition() + dist;
}
else{
  pos4 = stepper4.currentPosition();
}

if(ps2x.Analog(PSS_RX)>160){
  //Serial.println("Turn wrist CW");
  pos5 = stepper5.currentPosition() - dist;
}
else if(ps2x.Analog(PSS_RX)<100){
  //Serial.println("Turn wrist CCW");
  pos5 = stepper5.currentPosition() + dist;
}
else{
  pos5 = stepper5.currentPosition();
}

// Gripper servo:
if(ps2x.Analog(PSAB_PAD_RIGHT)>180){
  //Serial.println("Gripper opening... <   >");
  curPos = curPos + 2;
}
else if(ps2x.Analog(PSAB_PAD_LEFT)>180){
  //Serial.println("Gripper closing...  > <");
  curPos = curPos - 2;
}
gripperServo.write(curPos);

// Vibrate:

delay(10);

// Run motors to positions:
stepper1.moveTo(pos1);
stepper1.run();
stepper2.moveTo(pos2);
stepper2.run();
stepper3.moveTo(pos3);
stepper3.run();
stepper4.moveTo(pos4);
stepper4.run();
stepper5.moveTo(pos5);
stepper5.run();

delay(10);

}
}
