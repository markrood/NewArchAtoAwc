#ifndef DOSER_H_
#define DOSER_H_

#include <Arduino.h>
#include "SPIFFS.h"


class Doser 
{
  public:
    void doDose(String pump);
    void doCalibration();
    String readFile(fs::FS &fs, const char * path);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void startSpiffs();
    int calculateDosingLength(int cal, int amount);
    void calibrate();
    void readCalButtons();
    bool checkButtonBounce(int button);
    Doser();
                
  private:
    void motor(String pump, int value);
    static void fifteenMinTimer(); 
    int pumpStartedTime = 0;
    int pumpNowTime = 0;
    int pumpElaspeTime = 0;
    int MAXPUMPRUN = 120000;
    int pingReturn = 0;
    bool dosePing = true; 
    bool ckBox1 = false;
    bool ckBox2 = false;
    bool ckBox3 = false;
    bool ckBox4 = false;
    bool blueStarted = false;
    bool greenStarted = false;
    bool yellowStarted = false;
    bool purpleStarted = false;
    bool blDoseStarted = false;
    bool grDoseStarted = false;
    bool ywDoseStarted = false;
    bool puDoseStarted = false;
    bool blueRan = false;
    bool greenRan = false;
    bool yellowRan = false;
    bool purpleRan = false;
    bool calibrating = false;
    // Variables will change:
    int chkBoxState = HIGH;         // the current state of the output pin
    int buttonState;             // the current reading from the input pin
    int lastButtonState = LOW;   // the previous reading from the input pin
    
    // the following variables are unsigned longs because the time, measured in
    // milliseconds, will quickly become a bigger number than can be stored in an int.
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
    bool firstCal = true;
    long beginCal = 0;
    bool firstDose = true;
    long beginDose = 0;
};

#endif
