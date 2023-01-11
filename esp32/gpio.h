#include "Arduino.h"
/** @file gpio.h
 *
 */
#ifndef ESP32_GPIO_H
#define ESP32_GPIO_H


/**
 * Wrapper class for simple digital input/output pin
 */
class DIO {
private:
    ///\cond false
    uint32_t iPin;
    uint_32_t pinMode;
    bool state = false;
    ///\endcond
public:

    DIO(uint32_t pin, uint_32t pinMode) {
        this->iPin = pin;
        this->pinMode = pinMode;

        // set pin mode via Arduino.h
        // TODO: change to direct ports with registers
        pinMode(this->iPin,this->pinMode);
        digitalWrite(this->iPin, state);

    }

    ~DIO(){}

    /**
     * set digital output level
     * @param high true/false
     */
    void set(bool high) {
        digitalWrite(this->iPin, high);
    }

    /**
     * read digital input level
     * @return high/low
     */
    bool get() {
        return digitalRead(this->iPin);
    }

    /**
     * toggle digital output level
     */
    void toggle() {
        digitalWrite(this->iPin, !state);
    }
};


/**
 * Wrapper class for simple digital input/output pin
 */
class AI {
private:
    ///\cond false
    uint32_t iPin;
    ///\endcond
public:

    AI(uint32_t pin, DIO_PinMode pinMode ) {
        this->iPin = pin;
        this->pinMode = pinMode;
        pinMode(this->iPin,ANALOG_INPUT);
    }

    ~AI(){}

    /**
     * read analog input level
     * @return bits
     */
    bool get() {
        return analogRead(this->iPin);
    }
};



/**
 * Wrapper class for generic ADC
 * ESP 32 has two ADCS with 9 channels each
 * The Arduino Functions seem to set the ClockDivider and Resolution
 * for both ADCs since there is no way to specify which one
 * TODO: will may be changed with direct register acess
 */
class ADC {
private:
    ///\cond false
    uint8_t iResolution;           ///< Range 9-12 Bits | Default : 12 bits
    uint8_t iCycles;               ///< Range 1-255 | Default : 8
    uint8_t iClockDiv;             ///< Range 1-255 | Default : 1

    ///\endcond
public:

    ADC(){}

    ~ADC(){}

    /**
     * set new Resolution
     * Range:  9 (0-511) - 12 bits (0-4095)
     * Default : 12 bit
     */
    void setResolution(uint8_t iResolution) {
        this->iResolution = iResolution;
        analogReadResolution(iResolution);
    }

    /**
     * set current number of cycles per sample
     * Range:  1 - 255
     * Default : 8

     */
    void setCycles(uint8_t iCycles) {
        this->iCycles = iCycles;
        analogSetCycles(iCycles);
    }

    /**
     * set current ClockDivider for the ADC clock
     * Range: 1 - 255
     * Default: 1
     */
    void setClockDiv(uint8_t iClockDiv) {
        this->iClockDiv = iClockDiv;
        analogSetClockDiv(iClockDiv);
    }

    /**
     * get current Resolution
     * @return bits
     */
    bool getResolution() {
        return iResolution;
    }

    /**
     * get current Cycles
     * @return
     */
    bool getCycles() {
        return iCycles;
    }

    /**
     * get current Samples
     * @return
     */
    bool getSamples() {
        return iSamples;
    }
};


#endif //STM_GPIO_H
