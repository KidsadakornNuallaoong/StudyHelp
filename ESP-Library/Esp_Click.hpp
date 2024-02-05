// *********************** Credit ***********************
// * Name : Kidsadakorn Nuallaoong
// * Version : 1.0.0
// * Date : 2021. 10. 14
// * Description : This is a library for Click N Time use with arduino code
// * Open Source : True √
// ******************************************************

#if !defined(ESP_CLICK_HPP)
#define ESP_CLICK_HPP

#include <Arduino.h>
#include <esp32-hal-gpio.h>
#include <HardwareSerial.h>

class ClickNTime {
  private:
    // * Important Variables
    u_int8_t Pin;
    u_int8_t N; 
    bool Verbose = false;
    
    // * Internal Variables
    u_int8_t Cout = 0;
    u_int8_t bounce = 0;
    u_int8_t lastBounce = 0;
    bool Status = 0;

    // * Time Variables
    unsigned long timeset = 500;

  public:  
    void PinConfig(u_int8_t pin, u_int8_t n = 1, bool verbose = false);

    void SetTime(unsigned long time);
    bool Click_N_Time();
    bool GetClickStatus();
};

void ClickNTime::PinConfig(u_int8_t pin, u_int8_t n, bool verbose){
  pinMode(Pin, INPUT);
  Pin = pin;
  N = n;
  Verbose = verbose;
}

void ClickNTime::SetTime(unsigned long time){
  timeset = time;
}

bool ClickNTime::Click_N_Time(){
  bool nState = !digitalRead(Pin);
  static unsigned long ntime = 0;

  if(nState != lastBounce){
      if(nState == 1){
        bounce = !bounce;
        // * set time
        ntime = millis();
        Cout++;
      }
    delay(50);
  }

  lastBounce = nState;

    if(millis() - ntime > timeset){
      Cout = 0;
      ntime = 0;
    }

    if(Cout >= N){
      Cout = 0;
      Status = !Status;
    }

  if(Verbose){
    Serial.printf("Cout : %d | LastBounce : %d | Bounce : %d | Status : %d\n", Cout, lastBounce, bounce, Status);
    Serial.printf("NState : %d | NTime : %d | TimeSet : %d\n", nState, ntime, timeset);
  }
  return Status;
}

bool ClickNTime::GetClickStatus(){
  Click_N_Time();
  return Status;
}

#endif // ESP_CLICK_HPP
