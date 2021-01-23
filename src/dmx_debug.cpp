#include "dmx.h"
#include "utility.h"
#include "preferences.h"

#if DEBUG
#include "Arduino.h"

QueueHandle_t DMX::dmx_rx_queue;

SemaphoreHandle_t DMX::sync_dmx;

uint8_t DMX::dmx_state = 0;

bool DMX::changed_state = false;

uint16_t DMX::current_rx_addr = 0;

long DMX::last_dmx_packet = 0;

uint8_t DMX::dmx_data[513];

DMX::DMX(){}

void DMX::Initialize()
{
    // create receive task
    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL);
    // create mutex for syncronisation
    sync_dmx = xSemaphoreCreateMutex();
}

uint8_t DMX::Read(uint16_t channel)
{
    // restrict acces to dmx array to valid values
    std::clamp(channel, 1, 512);
    // take data threadsafe from array and return
    xSemaphoreTake(sync_dmx, portMAX_DELAY);
    uint8_t tmp_dmx = dmx_data[channel];
    xSemaphoreGive(sync_dmx);
    return tmp_dmx;
}

uint8_t DMX::IsHealthy() {return 1;}

bool DMX::HasChanged() {
  xSemaphoreTake(sync_dmx, portMAX_DELAY);
  bool local_copy = changed_state;
  changed_state = false;
  xSemaphoreGive(sync_dmx);
  return local_copy;
}

#define INPUT_SIZE 30

void DMX::uart_event_task(void *pvParameters)
{
    for(;;)
    {
      // wait for data in the dmx_queue, delay gives FreeRTOS threadcontrol back
      delay(1);
      if(Serial.available() > 0)
      {
        xSemaphoreTake(sync_dmx, portMAX_DELAY);
        // Calculate based on max input size expected for one command
        // Get next command from Serial (add 1 for final 0)
        char input[INPUT_SIZE + 1];
        byte size = Serial.readBytes(input, INPUT_SIZE);
        // Add the final 0 to end the C string
        input[size] = 0;
        
        // Read each command pair 
        char* command = strtok(input, ",");
        while (command != 0)
        {
            // Split the command in two values
            char* separator = strchr(command, ':');
            if (separator != 0)
            {
                // Actually split the string in 2: replace ':' with 0
                *separator = 0;
                int cmd_id = atoi(command);
                ++separator;
                int cmd_val = atoi(separator);
                
                if (dmx_data[cmd_id] != cmd_val) {
                  changed_state = true;
                }
                dmx_data[cmd_id] = cmd_val;
                //Serial.println("Received DMX Update " + String(cmd_id, DEC) + " : " + String(cmd_val, DEC));
            }
            // Find the next command in input string
            command = strtok(0, ",");
        }
        xSemaphoreGive(sync_dmx);
      }
    }
}
#endif
