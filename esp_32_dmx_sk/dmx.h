#include <stdint.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"

#ifndef DMX_h
#define DMX_h

class DMX
{
    public:
        static void Initialize();                           // initialize library

        static uint8_t Read(uint16_t channel);              // returns the dmx value for the givven address (values from 1 to 512)

        static uint8_t IsHealthy();                         // returns true, when a valid DMX signal was received within the last 500ms

        static bool HasChanged();                           // returns true oncy after an Update has been received

    private:
        DMX();                                              // hide constructor

        static QueueHandle_t dmx_rx_queue;                  // queue for uart rx events
        
        static SemaphoreHandle_t sync_dmx;                  // semaphore for syncronising access to dmx array

        static uint8_t dmx_state;                           // status, in which recevied state we are

        static uint16_t current_rx_addr;                    // last received dmx channel

        static long last_dmx_packet;                        // timestamp for the last received packet

        static uint8_t dmx_data[513];                       // stores the received dmx data

        static void uart_event_task(void *pvParameters);    // Event task

        static bool changed_state;                          // state for hasChanged

};

#endif
