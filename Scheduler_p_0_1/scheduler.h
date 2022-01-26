#ifndef   SCHED__h
#define SCHED__h

#include <TimeLib.h>
#include <TimeAlarms.h>
#include "datetime.h"
#include "doser.h"
#include "notification.h"
#include "atoAwc.h"

//AlarmId id;
static Datetime *dateTime___;
static Notification *_notification;
static AtoAwc *_atoAwc;
static Doser *_doser;//const char* ssid     = "RoodRouter";
//const char* password = "";

class Scheduler
{
  private:

    

  public:
    Scheduler(Doser *doser, Notification *notification, AtoAwc *atoAwc);
    void digitalClockDisplay();
    void printDigits(int digits);
    static void fifteenMinTimer();
    static void thirtyMinTimer();
    static void oneHour();
    static void twoHour();
    static void threeHour();
    static void fourHour();
    static void eightHour();
    static void Midnight();
    static void OneAm();
    static void TwoAm();
    static void ThreeAm();
    static void FourAm();
    static void FiveAm();
    static void SixAm();
    static void SevenAm();
    static void EightAm();
    static void NineAm();
    static void TenAm();
    static void ElevenAm();
    static void Noon();
    static void OnePm();
    static void TwoPm();
    static void ThreePm();
    static void FourPm();
    static void FivePm();
    static void SixPm();
    static void SevenPm();
    static void EightPm();
    static void NinePm();
    static void TenPm();
    static void ElevenPm(); 
    static void executeDoser();
    static void executeNotification(String what);
    static void executeAtoAwc(String what);

    
};
#endif
