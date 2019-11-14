
#include "include/config.h"
#include "include/util.h"
#include <include/dataio.h>
#include <include/endoveinous.h>

const int DIGITAl_POTENTIOMETER_VALUE[] =
{
255, 245, 244, 237, 232, 225, 219, 212, 205, 198, 190, 182, 173, 162, 153, 144, 132, 122, 111, 96, 84, 67, 53, 33, 17, 0
};



int Endoveinous::pedal_read()
{
#if defined(_GPIO_) && ( _GPIO_PEDAL_ == 1 )
    return dio->get_pedal();
#else
    return this->debug_pedal;
#endif
}

/*
int Endoveinous::catheter_read()
{
#ifdef _GPIO_
    dio->set_3m_sturing(1);
    delay(10);
    int ret = dio->get_3m_result();
    dio->set_3m_sturing(0);
    return ret;
#else
    return this->debug_cath;
#endif
}

int Endoveinous::pad_read()
{
#ifdef _GPIO_
    dio->set_mc_sturing(1);
    delay(10);
    int ret = dio->get_mc_result();
    dio->set_mc_sturing(0);
    return ret;
#else
    return this->debug_pad;
#endif
}
*/

int Endoveinous::catheter_read()
{
#ifdef _GPIO_
    // dio->set_mc_sturing(1);
    delay(10);
    int ret = dio->get_mc_result();
    // dio->set_mc_sturing(0);
    return ret;
#else
    return this->debug_cath;
#endif
}

int Endoveinous::pad_read()
{
#ifdef _GPIO_
    dio->set_3m_sturing(1);
    delay(10);
    int ret = dio->get_3m_result();
    dio->set_3m_sturing(0);
    return ret;
#else
    return this->debug_pad;
#endif
}

void Endoveinous::ht_program(int type, int val)
{
#ifdef _GPIO_
    if ( type == 0 )
    {
        dio->spi_pot_write(255);
        dio->set_hv_en(0);
        dio->set_hf_en(0);
        // dio-> spi_pot_write(255);
        delay(10);
    }
    else
    {
        dio->spi_pot_write(DIGITAl_POTENTIOMETER_VALUE[val]);
        delay(1);
        dio->set_hv_en(1);
        delay(1);
        dio->set_hf_en(1);
        delay(1);
    }
#else
    printf("Program HT\n");
#endif
}


void Endoveinous::catheter_status_enable(int val)
{
#ifdef _GPIO_
    if ( val == 1 )
    {
        delay(50);
    }
    dio->set_mc_sturing(val);
    if ( val == 0 )
    {
       delay(50);
    }
#else
    printf("Program HT\n");
#endif
}




void Endoveinous::valid_hf(int val)
{
#ifdef _GPIO_
    dio->set_hf_en(val);
#else
    printf("valid hf %d\n", val);
#endif
}

void Endoveinous::set_buzzer(int val, int boost)
{
    dio->set_cmp(boost);
    dio->set_buzzer(val);
}

void Endoveinous::set_buzzer_delay(int boost, int d)
{
    dio->set_cmp(boost);
    dio->set_buzzer_delay(d);
}


// =========================================================================================
void Endoveinous::showTime()
{
    switch ( this->treatment_type )
    {
       case ENDOVENOUS:
        switch ( this->treatment )
        {
          case RUN_CR45i: timer_cr45i(); break;
          case RUN_CR40i: timer_cr40i(); break;
          case RUN_CR30i: timer_cr30i(); break;
        }
        break;

       case TRANSCUTANEOUS:
          timer_transcutaneous();
          break;

       case PROCTOLOGY:
        switch ( this->treatment )
        {
          case RUN_HPR45i: timer_hpr45i(); break;
          case RUN_FISTULA: timer_fistula(); break;
        }
        break;
    }
}
