#include "Arduino.h"
/** @file pwm.h
 *
 */
#ifndef ESP32_PMW_H
#define ESP32_PWM_H

// todo think about adding security or splitting into led channels and then "PWM
// / GPIO Class as output only" namensgebung

/**
 * @brief Template class for hardware based PWM outputs
 * @param channel select a specific channel from 0-15 
 * @param frequency desired frequency in [Hz]
 * @param resolution in [bits] of the pwm signal 
 */
class PWM {
public:
  PWM(){};

  PWM(uint8_t channel, uint16_t frequency, uint8_t resolution = 8)
      : channel(channel), frequency(frequency),
        resolution(resolution) {
  };

  ~PWM(){};

  void init(){
    ledcSetup(this->channel, this->frequency, this->resolution);
  }

  void write(int duty) {
    ledcWrite(this->channel, duty);
  }; // todo think about correct datatype since resolution is a variable

  void setFrequency(uint16_t frequency) {
    this->frequency = frequency;
    ledcChangeFrequency(this->channel, this->frequency, this->resolution);
  };

  void setResolution(uint32_t resolution) {
    this->resolution = resolution;
    ledcChangeFrequency(this->channel, this->frequency, this->resolution);
  };

  uint16_t getFrequency() { return this->frequency; }
  uint32_t getResolution() { return this->resolution; }
  uint8_t getChannel() { return this->channel; }

  void detatchPin(uint8_t dPin) { ledcDetachPin(dPin); }
  void attachPin(uint8_t aPin) { ledcAttachPin(aPin,this->channel); }

  String print() {
    return "[PWM] - channel " + String(this->channel) + " - frequency " +
           String(this->frequency) + " - resolution " +
           String(this->resolution) + " - attached Pin " + String(this->pin);
  }

private:
  uint8_t channel;
  uint16_t frequency;
  uint8_t resolution;
  uint8_t pin;
};

#endif //ESP32_PWM_H
