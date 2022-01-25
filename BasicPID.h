/*-------------------
  Author: Xiang He
  Date created: 07-20-2018
  Usage:
  initialization:
    BasicPID Controller(KP, KI, KD, [usefilter], [filter cutoff freq]) [optional]
  update:
    Controller.update(desired, input, Dt)
  get output:
    Controller.output
  ------------------*/
#ifndef BASICPID_H_
#define BASICPID_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <time.h>
#include <ctime>
#include <unistd.h>
#include "LPfilter.h"

using namespace std;

class BasicPID {
  bool enableFilter = true, controllerFirstRun = true;
  float KP = 0, KI = 0, KD = 0;
  float LP_A = 0;
  LPfilter error_filter;
 private:
  float last_error = 0, integral_limit = 0;
 public:
  float output = 0;
  float integrate_error = 0, derror = 0, error = 0;
  BasicPID (float Gain_P, float Gain_I, float Gain_D);
  BasicPID (float Gain_P, float Gain_I, float Gain_D, bool useFilter);
  BasicPID (float Gain_P, float Gain_I, float Gain_D, bool useFilter, float A);
  void update(float desired, float input, float DT);
  void resetIntegral(void);
  void setKP(float Gain_P);
  void setKI(float Gain_I);
  void setKD(float Gain_D);
  void setGainPID(float Gain_P, float Gain_I, float Gain_D);
  void limitIntegral(float limit);
};

BasicPID::BasicPID (float Gain_P, float Gain_I, float Gain_D) : error_filter(0,0){
  KP = Gain_P;
  KI = Gain_I;
  KD = Gain_D;
}

BasicPID::BasicPID (float Gain_P, float Gain_I, float Gain_D, bool useFilter) : error_filter(0,0){
  KP = Gain_P;
  KI = Gain_I;
  KD = Gain_D;
  enableFilter = useFilter;
}

BasicPID::BasicPID (float Gain_P, float Gain_I, float Gain_D, bool useFilter, float A) : error_filter(0,0){
  KP = Gain_P;
  KI = Gain_I;
  KD = Gain_D;
  enableFilter = useFilter;
  LP_A = A;
  BasicPID::error_filter.setLP_A(A);
}

void BasicPID::update(float desired, float input, float DT){
  error = desired - input;
  if(enableFilter){
    if(LP_A == 0){
      // Default filtering cut-off frequency to be half the input frequency
      LP_A = (1.0f / DT) / 2.0f;
      BasicPID::error_filter.setLP_A(LP_A);
    }
    if(controllerFirstRun == false)
      BasicPID::derror = BasicPID::error_filter.update((BasicPID::error - BasicPID::last_error) / DT, DT);
  }
  else
    BasicPID::derror = (BasicPID::error - BasicPID::last_error) / DT;
  integrate_error += error * DT;
  if(integral_limit != 0)
    // Limit integral when the limit is nonzero
    integrate_error = integrate_error>integral_limit?integral_limit:
      (integrate_error<-integral_limit?-integral_limit:integrate_error);
  float P = KP * error;
  float D = KD * derror;
  float I = KI * integrate_error;
  last_error = error;
  output = P + I + D;
  controllerFirstRun = false;
}

void BasicPID::resetIntegral(void){
  integrate_error = 0;
}

void BasicPID::setKP(float Gain_P){
  KP = Gain_P;
}

void BasicPID::setKD(float Gain_D){
  KD = Gain_D;
}

void BasicPID::setKI(float Gain_I){
  KI = Gain_I;
}

void BasicPID::setGainPID(float Gain_P, float Gain_I, float Gain_D){
  KP = Gain_P;
  KI = Gain_I;
  KD = Gain_D;
}

void BasicPID::limitIntegral(float limit){
  // The limit can only be positive
  integral_limit = fabs(limit);
}
#endif
