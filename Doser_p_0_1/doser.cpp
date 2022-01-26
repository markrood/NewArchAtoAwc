#include "doser.h"

Doser::Doser(){
  pinMode(2,OUTPUT);
  digitalWrite(2, LOW);
  pinMode(14,OUTPUT);
  digitalWrite(14,LOW);
  pinMode(18,OUTPUT);
  digitalWrite(18,LOW);
  pinMode(19,OUTPUT);
  digitalWrite(19,LOW);
  pinMode(21,OUTPUT);
  digitalWrite(21,LOW);
  pinMode(27,INPUT);
  pinMode(26,INPUT);
  pinMode(13,INPUT);
  pinMode(25,INPUT);
}

void Doser::doDose(String pump){
   String blueCalibration = "";
  String greenCalibration = "";
  String yellowCalibration = "";
  String purpleCalibration = "";
  int blueCal = 0;
  int greenCal =0;
  int yellowCal = 0;
  int purpleCal = 0;
  int blueDosingAmount = 0;
  int greenDosingAmount = 0;
  int yellowDosingAmount = 0;
  int purpleDosingAmount = 0;

  if(pump == "blue" || blDoseStarted){
    blueCalibration = readFile(SPIFFS, "/blcal.txt");
    blueCal = blueCalibration.toInt();
    String blDosingAmount = readFile(SPIFFS, "/slider1.txt");
    blueDosingAmount = blDosingAmount.toInt();
    int bluePumpDuration = calculateDosingLength(blueCal, blueDosingAmount);
    int bluePumpDurMs = bluePumpDuration*1000;
    if(firstDose){
      blDoseStarted = true;
      beginDose = millis();
      firstDose = false;
    }
    Serial.print("Blue pump duration is ");
    Serial.println(bluePumpDuration);
      motor("blue", 1);
    Serial.println("Blue motor running");
    if( (millis() - beginDose) >= bluePumpDurMs ){
      motor("blue", 0);  
      Serial.println("Blue motor stopped");
      blDoseStarted = false;
      firstDose = true;
      beginDose = 0;
    }
  }
  if(pump == "green" || grDoseStarted){
    greenCalibration = readFile(SPIFFS, "/grcal.txt");
    greenCal = greenCalibration.toInt();
    String grDosingAmount = readFile(SPIFFS, "/slider2.txt");
    greenDosingAmount = grDosingAmount.toInt();
    int greenPumpDuration = calculateDosingLength(greenCal, greenDosingAmount);
    int greenPumpDurMs = greenPumpDuration*1000;
    if(firstDose){
      grDoseStarted = true;
      beginDose = millis();
      firstDose = false;
    }
    Serial.print("Green pump duration is ");
    Serial.println(greenPumpDuration);
      motor("green", 1);
    Serial.println("green motor running");
    if( (millis() - beginDose) >= greenPumpDurMs ){
      motor("green", 0);  
      Serial.println("Green motor stopped");
      grDoseStarted = false;
      firstDose = true;
      beginDose = 0;
    }
  }
  if(pump == "yellow" || ywDoseStarted){
    yellowCalibration = readFile(SPIFFS, "/ywcal.txt");
    yellowCal = yellowCalibration.toInt();
    String ywDosingAmount = readFile(SPIFFS, "/slider3.txt");
    yellowDosingAmount = ywDosingAmount.toInt();
    int yellowPumpDuration = calculateDosingLength(yellowCal, yellowDosingAmount);
    int yellowPumpDurMs = yellowPumpDuration*1000;
    if(firstDose){
      ywDoseStarted = true;
      beginDose = millis();
      firstDose = false;
    }
    Serial.print("yellow pump duration is ");
    Serial.println(yellowPumpDuration);
      motor("yellow", 1);
    Serial.println("Yellow motor running");
    if( (millis() - beginDose) >= yellowPumpDurMs ){
      motor("yellow", 0);  
      Serial.println("Yellow motor stopped");
      ywDoseStarted = false;
      firstDose = true;
      beginDose = 0;
    }
  }
  if(pump == "purple" || puDoseStarted){
    purpleCalibration = readFile(SPIFFS, "/pucal.txt");
    purpleCal = purpleCalibration.toInt();
    String puDosingAmount = readFile(SPIFFS, "/slider4.txt");
    purpleDosingAmount = puDosingAmount.toInt();
    int purplePumpDuration = calculateDosingLength(purpleCal, purpleDosingAmount);
    int purplePumpDurMs = purplePumpDuration*1000;
    if(firstDose){
      puDoseStarted = true;
      beginDose = millis();
      firstDose = false;
    }
    Serial.print("purple pump duration is ");
    Serial.println(purplePumpDuration);
      motor("purple", 1);
    Serial.println("Purple motor running");
    if( (millis() - beginDose) >= purplePumpDurMs ){
      motor("purple", 0);  
      Serial.println("Purple motor stopped");
      puDoseStarted = false;
      firstDose = true;
      beginDose = 0;
    }
  }

}



void Doser::motor(String pump, int value){
  bool pumpRunning = false;
  if(pump == "blue"){
    digitalWrite(19,value);
  }else if(pump == "green"){
    digitalWrite(21, value);
  }else if(pump == "yellow"){
    digitalWrite(18, value);
  }else if(pump == "purple"){
    digitalWrite(14, value);
  }
  
  if(value == 1){
    pumpRunning = true;
    pumpStartedTime = millis();
  }else{
    pumpRunning == false;
  }
  if(pumpRunning){
    pumpNowTime = millis();
    pumpElaspeTime = pumpNowTime - pumpStartedTime;
    if(pumpElaspeTime >= MAXPUMPRUN){
      digitalWrite(14,0);  //pumps can only run as long as MAXPUMPRUN
      digitalWrite(18,0);
      digitalWrite(19,0);
      digitalWrite(21,0);
      pumpRunning = false;
      pumpNowTime = 0;
      pumpElaspeTime = 0;
    }
  }
}

////////////////////////////////////////////////////////////////////
//
//  Fuction: readFile
//
//  Input:  SPIFFS,
//          char[]  filename path i.e. "/String.txt"
//
//  Output:  String of what was strored
//
//  Discription:  Stores a string in the /path in SPIFFS
//
/////////////////////////////////////////////////////////////////////
String Doser::readFile(fs::FS &fs, const char * path) {
  //Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    //Serial.println("- empty file or failed to open file");
    return String();
  }
  //Serial.println("- read from file:");
  String fileContent;
  while (file.available()) {
    fileContent += String((char)file.read());
  }
  //Serial.println(fileContent);
  file.close();
  return fileContent;
}

////////////////////////////////////////////////////////////////////
//
//  Fuction: writeFile
//
//  Input:  SPIFFS,
//          char[] filename path i.e. "/String.txt"
//          String to store
//
//  Output:  String of what was strored
//
//  Discription:  Stores a string in the /path in SPIFFS
//
/////////////////////////////////////////////////////////////////////
void Doser::writeFile(fs::FS &fs, const char * path, const char * message) {
  //Serial.printf("Writing file: %s\r\n", path);
  //Serial.print("path is : ");
  //Serial.println(path);
  //fs.remove(path);
  File file = fs.open(path, "w");
  if (!file) {
    Serial.println("- failed to open file for writing");
    //WebSerial.println("?EW"); //TODO change to right code
    return;
  }
  
  if (file.print(message)) {
    //Serial.println("- file written");
    if ((strcmp(path, "/timezone.txt") == 0)) {
      //Serial.println("Timezone changed!!!!!!!!11");
    }

  } else {
    Serial.println("- write failed");
  }
}



//////////////////////////////////////////////////////////////
//                                                          //
//   startSpiffs                                            //
//                                                          //
//   input: none                                            //
//                                                          //
//   output: none                                           //
//                                                          //
//   description:  starts of the file disk system.          //
//                                                          //
//////////////////////////////////////////////////////////////
void Doser::startSpiffs() {
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}

/////////////////////////////////////////////////
//
/////////////////////////////////////////////////////
int Doser::calculateDosingLength(int cal, int amount){
  return (amount*cal)/100;
}
//NOTE!!!!!!!!!!! type has to be captital (i.e. ATO,) maybe
/* String Dosing::getYearMonthJson(String yr, String mo, String type){
  //String myStr = "/october";
  //jsonAto = //_atoAwcUtil->readFile(SPIFFS, myStr.c_str());
  String filename = "/"+mo+type+"Arr.txt";
  String yrMoTypeJson = //_atoAwcUtil->readFile(SPIFFS, filename.c_str());
  return yrMoTypeJson;
}*/


////////////////////////////////////////////////////////////////////
//
//  Fuction: calibrate
//
//  Input:  node
//
//  Output:  none
//
//  Discription:  if chBox for calibrate is checked start and stop.
//                for calibration amount.  IF IT RUNS LESS THAN 10 SECONDS
//                THIS WAS JUST PRIMING PUMP NOT A TRUE CALIBRATION
//                DOESN'T really call recordRun to record the run it 
//                uses recordRun to see if it ran falsely or real calibrate.
//                Real calibration are stored in Spiffs for a 100ml run.
//
//  Calls:  recordRun, sendJson 
//
//  SPIFFS  "/hundredMlBlue.txt", "/hundredMlGreen.txt", "/hundredMlYellow.txt"
//
/////////////////////////////////////////////////////////////////////
void Doser::calibrate(){ 
  //Serial.println("in the calibration function"); 
  bool startIt = true;
  bool stopIt = false;
 
  if(ckBox1 && !blueStarted){//start blue calibrate
    calibrating = true;
    blueStarted = true;
    if(firstCal){
      beginCal = millis();
      firstCal = false;
    }
      motor("blue",1);  //Blue moter started
    Serial.println("Blue motor running");
   }else if(!ckBox1 && blueStarted){// blue stopped
    motor("blue", 0);  //Blue motor off
    long blueCal = millis() - beginCal;
    calibrating = false;
    blueStarted = false;
    firstCal = true;
    beginCal = 0;
    if(blueCal/1000 <= 10){
      return;  ////////////button pressed inadvertantly
    }
    String blStr = String(blueCal/1000);
    writeFile(SPIFFS, "/blcal.txt", blStr.c_str());
  }
  if(ckBox2 && !greenStarted){//start blue calibrate
    calibrating = true;
    greenStarted = true;
    if(firstCal){
      beginCal = millis();
      firstCal = false;
    }
      motor("green",1);  //Green moter started
    Serial.println("Green motor running");
   }else if(!ckBox1 && greenStarted){// blue stopped
    motor("green", 0);  //Green motor off
    long greenCal = millis() - beginCal;
    calibrating = false;
    greenStarted = false;
    firstCal = true;
    beginCal = 0;
    if(greenCal/1000 <= 10){
      return;  ////////////button pressed inadvertantly
    }
    String grStr = String(greenCal/1000);
    writeFile(SPIFFS, "/grcal.txt", grStr.c_str());
  }
  if(ckBox3 && !yellowStarted){//start yellow calibrate
    calibrating = true;
    yellowStarted = true;
    if(firstCal){
      beginCal = millis();
      firstCal = false;
    }
      motor("yellow",1);  //Yellow moter started
    Serial.println("Yellow motor running");
   }else if(!ckBox3 && yellowStarted){// yellow stopped
    motor("yellow", 0);  //Blue motor off
    long yellowCal = millis() - beginCal;
    calibrating = false;
    yellowStarted = false;
    firstCal = true;
    beginCal = 0;
    if(yellowCal/1000 <= 10){
      return;  ////////////button pressed inadvertantly
    }
    String ywStr = String(yellowCal/1000);    
    writeFile(SPIFFS, "/ywcal.txt", ywStr.c_str());
  }
  if(ckBox4 && !purpleStarted){//start purple calibrate
    calibrating = true;
    purpleStarted = true;
    if(firstCal){
      beginCal = millis();
      firstCal = false;
    }
      motor("purple",1);  //Purple moter started
    Serial.println("Purple motor running");
   }else if(!ckBox4 && purpleStarted){// blue stopped
    motor("purple", 0);  //Purple motor off
    long purpleCal = millis() - beginCal;
    calibrating = false;
    blueStarted = false;
    firstCal = true;
    beginCal = 0;
    if(purpleCal/1000 <= 10){
      return;  ////////////button pressed inadvertantly
    }
    String purStr = String(purpleCal/1000);
    writeFile(SPIFFS, "/pucal.txt", purStr.c_str());
  }
  
}

void Doser::readCalButtons(){
  if(digitalRead(27) == 1){
    checkButtonBounce(27);  //blue calc button
  }
  if(digitalRead(26) == 1){
    checkButtonBounce(26);  //green calc button
  }
  if(digitalRead(13) == 1){
    checkButtonBounce(13);  //yellow calc button
  }
  if(digitalRead(25) == 1){
    checkButtonBounce(25);  //purple calc button
  }
  
}

bool Doser::checkButtonBounce(int button){
    // read the state of the switch into a local variable:
  int reading = digitalRead(button);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
          if(button == 27){
            ckBox1 = !ckBox1;
          }else if(button == 26){
            ckBox2 = !ckBox2;
          }else if(button == 13){
            ckBox3 = !ckBox3;
          }else if(button == 25){
            ckBox4 = !ckBox4;
          }
      }
    }
  }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
