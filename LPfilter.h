/*-------------------
  Author: Xiang He
  Date created: 07-20-2018
  Usage:
  initialization:
    LPfilter filter(A, dt, [initial input], [initial output]) [optional]
  update:
    filter.update(input, [dt]) [optional]
  get output:
    filter.output
  ------------------*/
#ifndef LPFILTER_H_
#define LPFILTER_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <time.h>
#include <ctime>
#include <unistd.h>

using namespace std;

class LPfilter {
  float LP_A = 0, LP_last_out = 1, LP_last_in = 0, LP_DT = 0;
  float output = 0;
 public:
  LPfilter (float amplitude, float DT, float initial_input, float initial_output);
  LPfilter (float amplitude, float DT, float initial_input);
  LPfilter (float amplitude, float DT);
  float update (float input);
  float update (float input, float DT);
  void setLP_A(float amplitude);
};

LPfilter::LPfilter (float amplitude, float DT, float initial_input, float initial_output){
  LPfilter::LP_A = amplitude;
  LPfilter::LP_DT = DT;
  LPfilter::LP_last_in = initial_input;
  LPfilter::LP_last_out = initial_output;
}

LPfilter::LPfilter (float amplitude, float DT, float initial_input){
  LPfilter::LP_A = amplitude;
  LPfilter::LP_DT = DT;
  LPfilter::LP_last_in = initial_input;
  LPfilter::LP_last_out = initial_input;
}

LPfilter::LPfilter(float amplitude, float DT){
  LPfilter::LP_A = amplitude;
  LPfilter::LP_DT = DT;
  LPfilter::LP_last_in = 0;
  LPfilter::LP_last_out = 0;
}

float LPfilter::update(float input){
  float filtered_out = ((2.0f-LP_A*LP_DT)*LP_last_out + LP_A*LP_DT*(input+LP_last_in))/(LP_A*LP_DT+2.0f);
  LPfilter::LP_last_in = input;
  LPfilter::LP_last_out = filtered_out;
  return filtered_out;
}

float LPfilter::update(float input, float DT){
  LPfilter::LP_DT = DT;
  float filtered_out = ((2.0f-LP_A*LP_DT)*LP_last_out + LP_A*LP_DT*(input+LP_last_in))/(LP_A*LP_DT+2.0f);
  LPfilter::LP_last_in = input;
  LPfilter::LP_last_out = filtered_out;
  return filtered_out;
}

void LPfilter::setLP_A(float amplitude){
  LPfilter::LP_A = amplitude;
}
#endif
