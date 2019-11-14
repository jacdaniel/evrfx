
#include <math.h>

#include "include/config.h"
#include "include/util.h"
#include <include/endoveinous.h>

void Endoveinous::timer_fistula()
{
    int pedal = pedal_read();

    // catheterstatus_display(catheter_read());
    padstatus_display(pad_read());

    if ( pedal == 1 && this->onoff == 1 )
    {
        if ( progress == 0 )
        {
            // catheterstatus_display(catheter_read());
            // padstatus_display(pad_read());
            progress = 1;
            this->total_time0 = 0;
            this->cycle_time = 0;
            time_display(60-this->total_time0);
            energy0 = 0;
            energy_display(this->energy0);
            ht_program(1, care->val[care_power]);
            catheter_status_enable(0);
        }

        cycle_time++;
        total_time0++;
        if ( this->cycle_time >= 6*10 )
        {
            this->cycle_time = 0;
        }
        if ( this->cycle_time % 10 == 0 )
            time_display(60-this->cycle_time);
        power_progressbar_display(cycle_time*100/6/10);
        energy0 = (double)care->val[care_power] * total_time0 / 10.0;
        energy_display(this->energy0);        
        {
            int e = (int)floor(this->energy0);
            if ( e != 0 && e%500 == 0 )
            {
                set_buzzer_delay(0, 200);
            }

        }
    }
    else
    {
        /*
        if ( progress == 1 )
        {
            progress = 0;
            ht_program(0, 0);
            catheter_status_enable(1);
        }
        else
        {
            catheter_status_enable(1);
            catheterstatus_display(catheter_read());
        }
        */
    }
}
