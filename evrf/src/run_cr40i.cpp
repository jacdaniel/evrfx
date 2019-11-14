
#include "include/config.h"
#include "include/util.h"
#include <include/endoveinous.h>

void Endoveinous::timer_cr40i()
{
     int pedal = pedal_read();

     padstatus_display(pad_read());

    if ( pedal == 1 && this->onoff == 1 )
    {
        if ( progress == 0 )
        {
            progress = 1;
            // total_time0 = 0;
            // catheterstatus_display(catheter_read());
            // padstatus_display(pad_read());
            catheter_status_enable(0);
            ht_program(1, care->val[care_power]);
            set_buzzer_delay(0, DELAY_BEEP_2S);
        }
        else
        {
            int cycle_time_max = 6;
            total_time0++;
            if ( this->total_time0 % 10 == 0 )
                time_display(this->total_time0);
            cycle_time++;
            if ( cycle_time >= 6*10 )
            {
                cycle_time = 0;
                this->cycle_cpt++;
                if ( this->cycle_cpt > 0 )
                    this->cycle_cpt = 0;
                set_buzzer_delay(0, DELAY_BEEP_END_CYCLE);
            }
            // if ( cycle_time % 10 == 0 )
                power_progressbar_display(cycle_time*100/cycle_time_max/10);
            energy0 = (double)care->val[care_power] * total_time0 / 10.0;
            energy_display(this->energy0);
            if ( total_time0 % 20 == 0 && cycle_time != 0 )
            {
                set_buzzer_delay(0, DELAY_BEEP_2S);
            }
        }
    }
    else
    {
        /*
        if ( progress == 1 )
        {
            progress = 0;
            total_time0 = 0;
             ht_program(0, 0);
             catheter_status_enable(1);
        }
        else
        {
            catheter_status_enable(1);
            catheterstatus_display(catheter_read());
        }
        */
        if ( progress == 1 && this->onoff == 0 )
        {
            progress = 0;
            total_time0 = 0;
            ht_program(0, 0);
        }
        else if ( progress == 1 && pedal == 0 )
        {
            progress = 0;
            // total_time0 = 0;
            ht_program(0, 0);
            catheter_status_enable(1);
        }
        else
        {
            ht_program(0, 0);
            catheter_status_enable(1);
            catheterstatus_display(catheter_read());
        }
    }
 }
