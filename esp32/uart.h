/** @file uart.h
 *
 */
#ifndef ESP32_UART_H
#define ESP32_UART_H


/**
 * @brief Template class for hardware based UART derivations
 */
class HardwareUART {
public:
    /**
     * Initialize the peripheral
     *
     *
     * @param dUsart definition of used UART
     * @param iBaudRate baud rate
     */
    HardwareUART(uint8_t iPort, uint32_t iBaudRate) {

        this->uart_num = (uart_port_t) iPort;
        this->uart_config = {
            .baud_rate = iBaudRate,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
            .rx_flow_ctrl_thresh = 122,
        };

        // Configure UART parameters
        ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
        // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
       // ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 4, 5, 18, 19));
    }

    /*
     *  Basic example how to get the data from the uart with the generic esp header not tested yet
     */
    void read(){
        // Read data from UART.
        uint8_t data[128];
        int length = 0;
        ESP_ERROR_CHECK(uart_get_buffered_data_len(this->uart_num, (size_t*)&length));
        length = uart_read_bytes(this->uart_num, data, length, 100);
    }


    const uart_port_t uart_num;
    uart_config_t uart_config = {};
};

#endif //ESP32_UART_H

