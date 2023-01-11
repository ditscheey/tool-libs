/** @file timer.h
 *
 */
#include <Arduino.h> 

#ifndef ESP32_TIMER_H
#define ESP32_TIMER_H


/**
 * @brief Template class for hardware based Timers
 * 4 x 64 bit Timers fors ESP32 with 16 bit prescalar
 */
class HardwareTimer {
public:
    /**
     * Initialize Timer Hardware
     *
     * @param dTim Timer instance (0 - 3)
     * @param prescaler value to write into prescaler register (2 - 65536) 
     * @param period value to write into period register
     */
    HardwareTimer(uint8_t iTim, uint16_t prescaler, uint32_t period, bool bReload = true) {
        this->hTim = timerBegin(iTim, prescaler, true);
        timerAlarmWrite(this->hTim, period, bReload);
    }

    /**
     * return HAL handle to timer object
     */
    hw_timer_t *handle() {
        return hTim;
    }

    /**
     * configure callback on PERIOD ELAPSED event
     * @param callback function to be called
     */
    void setCallback(void (*callback)()) {
        timerAttachInterrupt(this->hTim, callback, true);
    }

    /**
     * start timer in interrupt mode
     */
    void start() {
        timerAlarmEnable(this->hTim);
    }

private:
    //\cond false
    hw_timer_t * hTim = NULL;

    //\endcond
};

#endif //STM_TIMER_H
