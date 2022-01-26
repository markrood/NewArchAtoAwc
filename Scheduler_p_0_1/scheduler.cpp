#include "scheduler.h"

Scheduler::Scheduler(Doser *doser, Notification *notification, AtoAwc *atoAwc){
  _notification = notification;
  _atoAwc = atoAwc;
  _doser = doser;
  
  Serial.println("Starting setup...");
  dateTime___ = new Datetime(-21600,false);
  dateTime___->updateTime();
  Serial.print("Hourrrrrrrrrrr is: ");
  Serial.println(dateTime___->getCurrentHour());
  int myHour = dateTime___->getCurrentHour();
  int myMin = dateTime___->getCurrentMinute();
  int myMo = dateTime___->getCurrentMonth();
  int myDay = dateTime___->getCurrentDay();
  int myYear = dateTime___->getCurrentYear();

  setTime(myHour,myMin,0,myMo,myDay,myYear); // set time to Saturday 8:29:00am Jan 1 2011

  // create the alarms, to trigger at specific times
//  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
//  Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day
//  Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday

  // create timers, to trigger relative to when they're created
//  Alarm.timerRepeat(15, Repeats);           // timer for every 15 seconds
//  id = Alarm.timerRepeat(2, Repeats2);      // timer for every 2 seconds
//Alarm.timerOnce(10, OnceOnly);            // called once after 10 seconds
  Alarm.timerRepeat(0,15,0,fifteenMinTimer);
 // Alarm.timerRepeat(23,59,59,newDay);
  Alarm.timerRepeat(0,30,0,thirtyMinTimer);
  Alarm.timerRepeat(1,0,0,oneHour);
  Alarm.timerRepeat(2,0,0,twoHour);
  Alarm.timerRepeat(3,0,0,threeHour);
  Alarm.timerRepeat(4,0,0,fourHour);
  Alarm.alarmRepeat(23,59,59,Midnight);
  Alarm.alarmRepeat(1,0,0,OneAm);
  Alarm.alarmRepeat(2,0,0,TwoAm);
  Alarm.alarmRepeat(3,0,0,ThreeAm);
  Alarm.alarmRepeat(4,0,0,FourAm);
  Alarm.alarmRepeat(5,0,0,FiveAm);
  Alarm.alarmRepeat(6,0,0,SixAm);
  Alarm.alarmRepeat(7,0,0,SevenAm);
  Alarm.alarmRepeat(8,0,0,EightAm);
  Alarm.alarmRepeat(9,0,0,NineAm);
  Alarm.alarmRepeat(10,0,0,TenAm);
  Alarm.alarmRepeat(11,0,0,ElevenAm);
  Alarm.alarmRepeat(12,0,0,Noon);
  Alarm.alarmRepeat(13,0,0,OnePm);
  Alarm.alarmRepeat(14,0,0,TwoPm);
  Alarm.alarmRepeat(15,0,0,ThreePm);
  Alarm.alarmRepeat(16,0,0,FourPm);
  Alarm.alarmRepeat(17,0,0,FivePm);
  Alarm.alarmRepeat(18,0,0,SixPm);
  Alarm.alarmRepeat(19,0,0,SevenPm);
  Alarm.alarmRepeat(20,0,0,EightPm);
  Alarm.alarmRepeat(21,0,0,NinePm);
  Alarm.alarmRepeat(22,0,0,TenPm);
  Alarm.alarmRepeat(23,0,0,ElevenPm);

}


/*void newDay(){
  Serial.println("New Day");
  dateTime = new Datetime(-21600,false);
  dateTime->updateTime();
  Serial.println(dateTime->getCurrentHour());
  int myHour = dateTime->getCurrentHour();
  int myMin = dateTime->getCurrentMinute();
  int myMo = dateTime->getCurrentMonth();
  int myDay = dateTime->getCurrentDay();
  int myYear = dateTime->getCurrentYear();
  setTime(myHour,myMin,0,myMo,myDay,myYear); // set time to Saturday 8:29:00am Jan 1 2011
  //digitalClockDisplay();
}*/
void Scheduler::fifteenMinTimer(){
  String what = "lw";  //TODO need to determin what is scheduled
  //notificaton hw,lw,hb, leak
  Serial.println("Fifteen Minute Timer in Scheduler");
  if(_doser != NULL){
    executeDoser();
  }
  if(_notification !=NULL){
    executeNotification(what);
  }
  if(_atoAwc != NULL){
    executeAtoAwc(what);
  }
}
void Scheduler::thirtyMinTimer(){
  Serial.println("Thirty Minute Timer");
  //digitalClockDisplay();
}
void Scheduler::oneHour(){
  Serial.println("One Hour Timer");
  //digitalClockDisplay();
}
void Scheduler::twoHour(){
  Serial.println("Two Hour Timer");
  //digitalClockDisplay();
}
void Scheduler::threeHour(){
  Serial.println("Three Hour Timer");
  //digitalClockDisplay();
}
void Scheduler::fourHour(){
  Serial.println("Four Hour Timer");
  //digitalClockDisplay();
}
void Scheduler::eightHour(){
  Serial.println("Eight Hour Timer");
  //digitalClockDisplay();
}

  void Scheduler::Midnight() {
  Serial.println("Midnight timer");
  Serial.println("New Day");
  dateTime___ = new Datetime(-21600,false);
  dateTime___->updateTime();
  Serial.println(dateTime___->getCurrentHour());
  int myHour = dateTime___->getCurrentHour();
  int myMin = dateTime___->getCurrentMinute();
  int myMo = dateTime___->getCurrentMonth();
  int myDay = dateTime___->getCurrentDay();
  int myYear = dateTime___->getCurrentYear();
  setTime(myHour,myMin,0,myMo,myDay,myYear); // set time to Saturday 8:29:00am Jan 1 2011
  //digitalClockDisplay();
}
  void Scheduler::OneAm() {
  Serial.println("1 am timer");
  //digitalClockDisplay();
}
  void Scheduler::TwoAm() {
  Serial.println("2 am timer");
  //digitalClockDisplay();
}
  void Scheduler::ThreeAm() {
  Serial.println("3 am timer");
  //digitalClockDisplay();
}
  void Scheduler::FourAm() {
  Serial.println("4 am timer");
  //digitalClockDisplay();
}
  void Scheduler::FiveAm() {
  Serial.println("5 am timer");
  //digitalClockDisplay();
}
  void Scheduler::SixAm() {
  Serial.println("6 am timer");
  //digitalClockDisplay();
}
  void Scheduler::SevenAm() {
  Serial.println("7 am timer");
  //digitalClockDisplay();
}
  void Scheduler::EightAm() {
  Serial.println("8 am timer");
  //digitalClockDisplay();
}
  void Scheduler::NineAm() {
  Serial.println("9 am timer");
  //digitalClockDisplay();
}
  void Scheduler::TenAm() {
  Serial.println("10 am timer");
  //digitalClockDisplay();
}
  void Scheduler::ElevenAm() {
  Serial.println("11 am timer");
  //digitalClockDisplay();
}
  void Scheduler::Noon() {
  Serial.println("Noon timer");
  //digitalClockDisplay();
}
  void Scheduler::OnePm() {
  Serial.println("1 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::TwoPm() {
  Serial.println("2 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::ThreePm() {
  Serial.println("3 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::FourPm() {
  Serial.println("4 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::FivePm() {
  Serial.println("5 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::SixPm() {
  Serial.println("6 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::SevenPm() {
  Serial.println("7 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::EightPm() {
  Serial.println("8 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::NinePm() {
  Serial.println("9 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::TenPm() {
  Serial.println("10 pm timer");
  //digitalClockDisplay();
}
  void Scheduler::ElevenPm() {
  Serial.println("11 pm timer");

  }

void Scheduler::executeDoser(){
  String blue = "blue";
  String green = "green";
  String yellow = "yellow";
  String purple = "purple";
  
   _doser->doDose(blue);
}

void Scheduler::executeNotification(String what){
   if(what == "lw"){
    _notification->lowWater();
   }
   if(what == "hw"){
    _notification->highWater();
   }
   if(what == "leak"){
    _notification->leak();
   }
   if(what == "heartBeat"){
    _notification->heartBeat();
   }
}

void Scheduler::executeAtoAwc(String what){
   if(what == "ato"){
      _atoAwc->doAto();
   }
   if(what == "awcEmpty"){
      _atoAwc->doAwcEmpty();
   }
   if(what == "awcFill"){
      _atoAwc->doAwcFill();
   }
}
