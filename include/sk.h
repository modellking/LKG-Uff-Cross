#ifndef SK_H
#define SK_H 1

#include "driver/rmt.h"

// Use RMT for a strip of SK6812 RGBW leds

class sk{
public:
    sk() = default;
    ~sk() {
       free(_skStrip);
       rmt_driver_uninstall(skConfig.channel);
    }


    /*-------------------------------------------------------------------------*/
    int begin( int pin, int count){
        _bitCount = count * 32;
        _ledPin = pin;
        _ledCount = count;

        int rc;
        _skStrip = (rmt_item32_t *)calloc(_bitCount, sizeof( rmt_item32_t ) );

        skConfig.rmt_mode = RMT_MODE_TX;
        skConfig.channel = RMT_CHANNEL_7;
        skConfig.gpio_num = (gpio_num_t)_ledPin;
        skConfig.mem_block_num = 1;
        skConfig.tx_config.loop_en = false;
        skConfig.tx_config.carrier_en = false;
        skConfig.tx_config.idle_output_en = true;
        skConfig.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
        skConfig.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH;
        skConfig.clk_div = 8; // 80MHx / 8 = 10MHz translates to  0,1 us = 100 ns per count

        rmt_config( &skConfig);
        rc = rmt_driver_install(skConfig.channel, 0, 0);  //  rmt_driver_install(rmt_channel_t channel, size_t rx_buf_size, int rmt_intr_num)

        return(rc);
    }

    /*-------------------------------------------------------------------------*/
    static uint32_t getColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w ){
        uint32_t  kleur=0;

        kleur |= ((uint32_t)g<<24);
        kleur |= ((uint32_t)r<<16);
        kleur |= ((uint32_t)b<<8);
        kleur |= (uint32_t)w;

        return( kleur );
    }

    /*-------------------------------------------------------------------------*/

    static uint32_t breakColor(uint32_t kleur, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *w ){
        *g = (kleur >> 24 )&0xff;
        *r = (kleur >> 16 )&0xff;
        *b = (kleur >> 8 )&0xff;
        *w = kleur&0xff;

        return( kleur );
    }


    /*-------------------------------------------------------------------------*/
    void color32( int led, uint32_t kleur){
        int       i,bit;

        if ( led < 0 || led >= ledCount() ) return;

        // sk6812 has around 600us/600us 1, 300/900us 0

        for (i=(led*32),bit=0; bit<32; bit++){

            if ( (kleur & (1<<(31-bit)))  ) {
               _skStrip[i].level0 = 1;
               _skStrip[i].duration0 = 6;
               _skStrip[i].level1 = 0;
               _skStrip[i].duration1 = 6;
            } else {
               _skStrip[i].level0 = 1;
               _skStrip[i].duration0 = 3;
               _skStrip[i].level1 = 0;
               _skStrip[i].duration1 = 9;
            }
            //if ( bit == 31 )  _skStrip[i].duration1 += 60;
        ++i;
        }
    }

    /*-------------------------------------------------------------------------*/
    void color( int led, uint8_t r,uint8_t g,uint8_t b,uint8_t w){
        color32(led, getColor(r, g, b, w));
    }


    /*-------------------------------------------------------------------------*/
    void show(){
        // esp_err_t rmt_write_items(rmt_channel_t channel, rmt_item32_t *rmt_item, int item_num, bool wait_tx_done)
        rmt_write_items(skConfig.channel, _skStrip, _bitCount, true);
        delay(2);
    }

    /*-------------------------------------------------------------------------*/

    void clear( ){
        for (int i =0; i < _ledCount; ++i ) {
            color(i,0,0,0,0);
        }
        show();
        delay(10);
    }

    /*-------------------------------------------------------------------------*/

    int ledCount(){
        return( _ledCount);
    }

    /*-------------------------------------------------------------------------*/

private:
    int   _ledCount{};
    int   _bitCount{};
    int   _ledPin{};
    rmt_item32_t* _skStrip = nullptr;
    rmt_config_t skConfig{};

};

#endif
