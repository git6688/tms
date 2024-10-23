// Copyright (c) 2023, AgiBot Inc.
// All rights reserved.
#pragma once
#include <chrono>
#include "rl_control_module/types.h"

using namespace std::chrono;

bool Throttler(const time_point<high_resolution_clock> now, time_point<high_resolution_clock> &last,
               const milliseconds interval);

template <typename T>
class filter {
 public:
  filter(void) {}
  virtual ~filter(void) {}
  virtual void input(T input_value) = 0;
  virtual T output(void) = 0;
  virtual void clear(void) = 0;
};

template <typename T>
class digital_lp_filter : public filter<T> {
 public:
  digital_lp_filter(T w_c, T t_s);
  virtual ~digital_lp_filter(void);
  virtual void input(T input_value);
  virtual T output(void);
  virtual void update(void);
  virtual void set_wc(T w_c);
  virtual void set_ts(T t_s);
  virtual void clear(void);
  virtual void init(T init_data);

 private:
  T Lpf_in_prev[2];
  T Lpf_out_prev[2];
  T Lpf_in1, Lpf_in2, Lpf_in3, Lpf_out1, Lpf_out2;
  T lpf_out;
  T wc;
  T ts;
};