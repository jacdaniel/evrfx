
#include "include/config.h"
#include "include/dataio.h"

#ifndef _GPIO_
    void delay(int i)
    {
    }

    void delayMicroseconds (unsigned int howLong)
    {

    }
#endif


dataio::dataio()
{
#ifdef _GPIO_
    wiringPiSetup();
    // this->fd = wiringPiSPISetup(0, 500000);
    this->fd = wiringPiSPISetupMode(0, 500000, 0x02);
    pinMode(GPIO_HF_EN, OUTPUT);
    pinMode(GPIO_HV_EN, OUTPUT);
    pinMode(GPIO_3M_RESULT, INPUT);
    pinMode(GPIO_3M_STURING, OUTPUT);
    pinMode(GPIO_MC_RESULT, INPUT);
    pinMode(GPIO_MC_STURING, OUTPUT);

    pinMode(GPIO_HT_CS, OUTPUT);
    pinMode(GPIO_HT_MISO, INPUT);
    pinMode(GPIO_HT_SCLK, OUTPUT);
    digitalWrite(GPIO_HT_CS, HIGH);

    pinMode(GPIO_OUT_CS, OUTPUT);
    pinMode(GPIO_OUT_MISO, INPUT);
    pinMode(GPIO_OUT_SCLK, OUTPUT);
    digitalWrite(GPIO_OUT_CS, HIGH);

    pinMode(GPIO_BUZZ, OUTPUT);
    pinMode(GPIO_CPM1, OUTPUT);
    pinMode(GPIO_CPM1, OUTPUT);
    set_buzzer(0);
    set_cmp(CMP_BOOST0);
    button_beep();
#endif
}

void dataio::delay_spi1()
{
    delayMicroseconds (2);
}

void dataio::set_hf_en(int val)
{
#ifdef _GPIO_
    if ( val == 0 )
    {
        digitalWrite(GPIO_HF_EN, LOW);
        HF_EN_3V = 0;
    }
    else
    {
        digitalWrite(GPIO_HF_EN, HIGH);
        HF_EN_3V = 1;
    }
#endif
}

int dataio::get_hf_en()
{
    return HF_EN_3V;
}

void dataio::set_hv_en(int val)
{
#ifdef _GPIO_
    if ( val == 0 )
        digitalWrite(GPIO_HV_EN, LOW);
    else
        digitalWrite(GPIO_HV_EN, HIGH);    
#endif
}

int dataio::get_3m_result()
{
#ifdef _GPIO_
    return digitalRead(GPIO_3M_RESULT);
#else
    return 0;
#endif
}

void dataio::set_3m_sturing(int val)
{
#ifdef _GPIO_
    if ( val == 0 )
        digitalWrite(GPIO_3M_STURING, LOW);
    else
        digitalWrite(GPIO_3M_STURING, HIGH);
#endif
}

void dataio::set_mc_sturing(int val)
{
#ifdef _GPIO_
    if ( val == 0 )
        digitalWrite(GPIO_MC_STURING, LOW);
    else
        digitalWrite(GPIO_MC_STURING, HIGH);
#endif
}

int dataio::get_mc_result()
{
#ifdef _GPIO_
    return digitalRead(GPIO_MC_RESULT);
#else
    return 0;
#endif
}

int dataio::get_pedal()
{
#ifdef _GPIO_
    int temp = get_hf_en(), ret;
    set_hf_en(0);
    delay(1);
    ret = 1 - digitalRead(GPIO_PEDAL);
    set_hf_en(temp);
    return ret;
    // return 1 - digitalRead(GPIO_PEDAL);
#else
    return 0;
#endif
}


int dataio::serial_open()
{
#ifdef _GPIO_
    this->serial_fd = serialOpen("/dev/ttyAMA0", BAUDRATE);
    return serial_fd;
#else
    return 0;
#endif
}

int dataio::serial_write(int val)
{
#ifdef _GPIO_
    serialPutchar(this->serial_fd, val);
    return 1;
#else
    return 1;
#endif
}


unsigned char dataio::serial_read()
{
#ifdef _GPIO_
    return serialGetchar(this->serial_fd);
#else
    return 0;
#endif
}

int dataio::serial_queue_nbre()
{
#ifdef _GPIO_
    return serialDataAvail(this->serial_fd);
#else
    return 0;
#endif
}

void dataio::serial_close()
{
#ifdef _GPIO_
serialClose(this->serial_fd);
#endif
}


int dataio::spi_pot_write(int val)
{
#ifdef _GPIO_
    unsigned char buffer[100];
    buffer[0] = 0x13;
    buffer[1] = (unsigned char)val;
    wiringPiSPIDataRW(0, buffer, 2);
    delay(1);
#endif
    return 0;
}




//
const static int ARRAY_SPI_SCLK[] = {GPIO_HT_SCLK, GPIO_OUT_SCLK};
const static int ARRAY_SPI_CS[] =   {GPIO_HT_CS,   GPIO_OUT_CS};
const static int ARRAY_SPI_MISO[] = {GPIO_HT_MISO, GPIO_OUT_MISO};


int dataio::spi_read(int no)
{
#ifdef _GPIO_
    int sclk = ARRAY_SPI_SCLK[no],
        cs = ARRAY_SPI_CS[no],
        miso = ARRAY_SPI_MISO[no];

    int out = 0x0000;

    digitalWrite(sclk, HIGH);
    digitalWrite(cs, LOW);

    for (int i=0; i<6; i++)
    {
        digitalWrite(sclk, LOW);
        delay_spi1();
        digitalWrite(sclk, HIGH);
        delay_spi1();
    }

    for (int i=0; i<16; i++)
    {
        digitalWrite(sclk, LOW);
        delay_spi1();
        out = out << 1;
        if ( digitalRead(miso) == 1 )
        {
            out++;
        }

        digitalWrite(sclk, HIGH);
        delay_spi1();
    }
    digitalWrite(cs, HIGH);
    return out;
#else
    return 0;
#endif
}




int dataio::spi_read_v2(int no)
{
#ifdef _GPIO_
    int sclk = ARRAY_SPI_SCLK[no],
        cs = ARRAY_SPI_CS[no],
        miso = ARRAY_SPI_MISO[no];

    int out = 0x0000;
    // digitalWrite(sclk, LOW);
    // digitalWrite(cs, LOW);

    digitalWrite(cs, HIGH);
    digitalWrite(cs, LOW);
    digitalWrite(sclk, LOW);
    delay_spi1();

    for (int i=0; i<6; i++)
    {
        digitalWrite(sclk, HIGH);
        delay_spi1();
        digitalWrite(sclk, LOW);
        delay_spi1();
    }

    for (int i=0; i<16; i++)
    {
        out = out << 1;
        if ( digitalRead(miso) == 1 )
        {
            out++;
        }
        else
        {
        }
        digitalWrite(sclk, HIGH);
        delay_spi1();
        digitalWrite(sclk, LOW);
        delay_spi1();
    }
    digitalWrite(cs, HIGH);
    /*
    for (int i=0; i<2; i++)
    {
        digitalWrite(sclk, HIGH);
        delay_spi1();
        digitalWrite(sclk, LOW);
        delay_spi1();
    }
    */
    return out;
#else
    return 0;
#endif
}



/*
int dataio::spi_read(int no)
{
#ifdef _GPIO_
    int sclk = ARRAY_SPI_SCLK[no],
        cs = ARRAY_SPI_CS[no],
        miso = ARRAY_SPI_MISO[no];

    int out = 0x00;
    digitalWrite(sclk, LOW);
    digitalWrite(cs, LOW);
    delay(1);
    for (int i=0; i<5; i++)
    {
        digitalWrite(sclk, HIGH);
        delay(1);
        digitalWrite(sclk, LOW);
        delay(1);
    }
    // bit 0
    digitalWrite(sclk, HIGH);
    delay(1);
    digitalWrite(sclk, LOW);
    delay(1);

    for (int i=0; i<16; i++)
    {
        out = out << 1;
        if ( digitalRead(miso) == 1 )
        {
            out++;
        }
        else
        {

        }
        digitalWrite(sclk, HIGH);
        delay(1);
        // digitalWrite(GPIO_HT_CS, HIGH);
        digitalWrite(sclk, LOW);
        delay(1);
    }
    for (int i=0; i<3; i++)
    {
        digitalWrite(sclk, HIGH);
        delay(1);
        digitalWrite(sclk, LOW);
        delay(1);
    }
    digitalWrite(cs, HIGH);
    return out;
#else
    return 0;
#endif
}
*/




























int dataio::spi_adc_read(int no)
{
#ifdef _GPIO_
return 0;
#else
    return 0;
#endif
}



int dataio::spi_ht_read()
{
#ifdef _GPIO_
    int out = 0x00;

    digitalWrite(GPIO_HT_SCLK, LOW);
    digitalWrite(GPIO_HT_CS, LOW);
    delay(1);
    for (int i=0; i<5; i++)
    {
        digitalWrite(GPIO_HT_SCLK, HIGH);
        delay(1);
        digitalWrite(GPIO_HT_SCLK, LOW);
        delay(1);
    }
    // bit 0
    digitalWrite(GPIO_HT_SCLK, HIGH);
    delay(1);
    digitalWrite(GPIO_HT_SCLK, LOW);
    delay(1);

    for (int i=0; i<16; i++)
    {
        if ( digitalRead(GPIO_HT_MISO) == 1 )
        {
            out++;
        }
        else
        {

        }
        digitalWrite(GPIO_HT_SCLK, HIGH);
        delay(1);
        // digitalWrite(GPIO_HT_CS, HIGH);
        digitalWrite(GPIO_HT_SCLK, LOW);
        delay(1);
        if ( i != 15 )
            out = out<<1;
    }
    for (int i=0; i<3; i++)
    {
        digitalWrite(GPIO_HT_SCLK, HIGH);
        delay(1);
        digitalWrite(GPIO_HT_SCLK, LOW);
        delay(1);
    }
    digitalWrite(GPIO_HT_CS, HIGH);
    return out;
#else
    return 0;
#endif
}


int dataio::spi_out_read()
{
#ifdef _GPIO_
    int out = 0x00;

    digitalWrite(GPIO_OUT_SCLK, LOW);
    digitalWrite(GPIO_OUT_CS, LOW);
    delay(1);
    for (int i=0; i<5; i++)
    {
        digitalWrite(GPIO_OUT_SCLK, HIGH);
        delay(1);
        digitalWrite(GPIO_OUT_SCLK, LOW);
        delay(1);
    }
    // bit 0
    digitalWrite(GPIO_OUT_SCLK, HIGH);
    delay(1);
    digitalWrite(GPIO_OUT_SCLK, LOW);
    delay(1);

    for (int i=0; i<16; i++)
    {
        if ( digitalRead(GPIO_OUT_MISO) == 1 )
        {
            out++;
        }
        else
        {

        }
        digitalWrite(GPIO_OUT_SCLK, HIGH);
        delay(1);
        // digitalWrite(GPIO_OUT_CS, HIGH);
        digitalWrite(GPIO_OUT_SCLK, LOW);
        delay(1);
        if ( i != 15 )
            out = out<<1;
    }
    for (int i=0; i<3; i++)
    {
        digitalWrite(GPIO_OUT_SCLK, HIGH);
        delay(1);
        digitalWrite(GPIO_OUT_SCLK, LOW);
        delay(1);
    }
    digitalWrite(GPIO_OUT_CS, HIGH);
    return out;
#else
    return 0;
#endif
}




void dataio::set_buzzer(int val)
{
#ifdef _GPIO_
    if ( val == 0 )
    {
        digitalWrite(GPIO_BUZZ, LOW);
    }
    else
    {
        digitalWrite(GPIO_BUZZ, HIGH);
    }
#else
#endif
}

void dataio::set_buzzer_delay(int d)
{
    set_buzzer(1);
    delay(d);
    set_buzzer(0);
}

void dataio::button_beep()
{
  set_buzzer_delay(80);
}



void dataio::set_cmp(int val)
{
#ifdef _GPIO_
    switch ( val )
    {
    case CMP_BOOST0:
            digitalWrite(GPIO_CPM1, LOW);
            digitalWrite(GPIO_CPM2, LOW);
        break;
    case CMP_BOOST1:
        digitalWrite(GPIO_CPM1, HIGH);
        digitalWrite(GPIO_CPM2, LOW);
        break;
    case CMP_BOOST2:
        digitalWrite(GPIO_CPM1, LOW);
        digitalWrite(GPIO_CPM2, HIGH);
        break;
    case CMP_BOOST3:
        digitalWrite(GPIO_CPM1, HIGH);
        digitalWrite(GPIO_CPM2, HIGH);
        break;
    default:
        digitalWrite(GPIO_CPM1, LOW);
        digitalWrite(GPIO_CPM2, LOW);
    break;
    }
#else
#endif
}
