#include "Arduino.h"
/** @file gpio.h
 *
 */
#ifndef ESP32_GPIO_H
#define ESP32_GPIO_H



// TODO: fix pinMode to correctly work with gpio driver 
/**
 * Wrapper class for simple digital input/output pin
 */
class DIO {
private:
    ///\cond false
    uint8_t iPin;
    uint8_t iPinMode;
    bool bState = false;
    ///\endcond
public:

    DIO(uint8_t pin, uint8_t iPinMode = 0) {
        this->iPin = pin;
        this->iPinMode = iPinMode;

        gpio_set_direction((gpio_num_t) pin, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) pin, this->bState);

    }

    ~DIO(){}

    /**
     * set digital output level
     * @param high true/false
     */
    void set(bool high) {
        this->bState = high;
        gpio_set_level((gpio_num_t)this->iPin, this->bState);
    }

    /**
     * read digital input level
     * @return high/low
     */
    bool get() {
        this->bState = gpio_get_level((gpio_num_t) this->iPin);
        return this->bState;
    }

    /**
     * toggle digital output level
     */
    void toggle() {
        this->bState = !this->bState;
        gpio_set_level((gpio_num_t)this->iPin, this->bState);
    }
};


/**
 * Wrapper class for simple digital input/output pin
 */
class AI {
private:
    ///\cond false
    uint8_t iPin;
    ///\endcond
public:

    AI(uint8_t pin) {
        this->iPin = pin;
    }

    ~AI(){}

    /**
     * read analog input level
     * @return bits
     */
    uint16_t get() {
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
class HardwareADC {
private:
    ///\cond false
    uint8_t iResolution = 12;           ///< Range 9-12 Bits | Default : 12 bits
    uint8_t iCycles = 8;               ///< Range 1-255 | Default : 8
    uint8_t iClockDiv = 1;             ///< Range 1-255 | Default : 1

    ///\endcond
public:

    HardwareADC(){}

    ~HardwareADC(){}

    /**
     * set new Resolution
     * Range:  9 (0-511) - 12 bits (0-4095)
     * Default : 12 bit
     */
    void setResolution(uint8_t iResolution) {
        this->iResolution = iResolution;
        Serial.println("setResolution");
        //analogReadResolution(iResolution);
    }

    /**
     * set current number of cycles per sample
     * Range:  1 - 255
     * Default : 8

     */
    void setCycles(uint8_t iCycles) {
        this->iCycles = iCycles;
        //analogSetCycles(iCycles);
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
    uint8_t getResolution() {
        return iResolution;
    }

    /**
     * get current Cycles
     * @return
     */
    uint8_t getCycles() {
        return iCycles;
    }

    /**
     * get current ClockDivider
     * @return
     */
    uint8_t getClockDiv() {
        return iClockDiv;
    }
};


#endif //ESP32_GPIO_H
