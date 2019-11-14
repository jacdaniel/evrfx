#ifndef DATAIO_H
#define DATAIO_H

// #define _GPIO_
#define _GPIO_PEDAL_ 0 // 0 --> pedal = button   1 --> pedal = hardware

#ifdef _GPIO_
#include "wiringPi.h"
#include "wiringSerial.h"
#include "wiringPiSPI.h"
#endif


// *********************************************************
// GPIO
//
// *********************************************************
#define GPIO_HF_EN      25
#define GPIO_HV_EN      24
#define GPIO_3M_RESULT  23
#define GPIO_3M_STURING 22
#define GPIO_MC_RESULT  21
#define GPIO_PEDAL       8
#define GPIO_MC_STURING 26

#define GPIO_HT_CS      27
#define GPIO_HT_MISO    28
#define GPIO_HT_SCLK    29

#define GPIO_OUT_CS      3
#define GPIO_OUT_MISO    0
#define GPIO_OUT_SCLK    2

#define GPIO_BUZZ       15
#define GPIO_CPM1        1
#define GPIO_CPM2       16

// #define GPIO_POT_CS      0
// #define GPIO_CLK_ADC1   29
// #define GPIO_MOSI_ADC1  28
// #define GPIO_CS_ADC1    27
// #define GPIO_CLK_ADC2    2
// #define GPIO_MOSI_ADC2   0
// #define GPIO_CS_ADC2     3
// #define GPIO_CS_ADC1    27
#define BAUDRATE 19200

#define ADC1 0
#define ADC2 1

#define CMP_BOOST0 0
#define CMP_BOOST1 1
#define CMP_BOOST2 2
#define CMP_BOOST3 3

class dataio
{
private:
    int serial_fd;
    int HF_EN_3V;
public:
    dataio();
    int fd;
    void set_hf_en(int val);
    int get_hf_en();
    void set_hv_en(int val);
    int get_3m_result();
    void set_3m_sturing(int val);
    void set_mc_sturing(int val);
    int get_mc_result();
    int get_pedal();

    int serial_open();
    int serial_write(int val);
    unsigned char serial_read();
    int serial_queue_nbre();
    void serial_close();

    int spi_setup();
    int spi_pot_write(int val);

    int spi_adc_read(int no);

    int spi_read(int no);
    int spi_read_v2(int no);


    int spi_ht_read();
    int spi_out_read();

    void set_buzzer(int val);
    void set_buzzer_delay(int d);
    void set_cmp(int val);
    void button_beep();

    void delay_spi1();

};

#ifndef _GPIO_
    void delay(int i);
#endif

#endif // DATAIO_H
