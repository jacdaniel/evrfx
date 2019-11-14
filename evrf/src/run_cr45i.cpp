
#include "include/config.h"
#include "include/util.h"
#include <include/endoveinous.h>

void Endoveinous::timer_cr45i()
{
    int cycle_time_max, cycle_lenght;
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
            // this->cycle_cpt = 0;
            // this->cycle_time = 0;
            // this->total_time0 = 0;
            time_display(this->total_time0);
            energy0 = 0;
            // energy_display(this->energy0);
            catheter_status_enable(0);
            ht_program(1, care->val[care_power]);            
            set_buzzer_delay(0, DELAY_BEEP_2S);
        }

        if ( care->val[care_manualpreset] == 0  )
        {
            cycle_time_max = ARRAY_CYCLE_VS_VEINDIAMETER[0][this->cycle_cpt];
            cycle_lenght = ARRAY_CYCLE_VS_VEINDIAMETER_LENGTH[0];
        }
        else
        {
            cycle_time_max = ARRAY_CYCLE_VS_VEINDIAMETER[this->veindiameter+1][this->cycle_cpt];
            cycle_lenght = ARRAY_CYCLE_VS_VEINDIAMETER_LENGTH[veindiameter+1];
        }

        total_time0++;
        if ( this->total_time0 % 10 == 0 )
            time_display(this->total_time0);
        cycle_time++;
        if ( cycle_time >= cycle_time_max*10 )
        {
            cycle_time = 0;
            this->cycle_cpt++;
            if ( this->cycle_cpt >= cycle_lenght )
                this->cycle_cpt = cycle_lenght-1;
            set_buzzer_delay(0, DELAY_BEEP_END_CYCLE);
        }
        power_progressbar_display(cycle_time*100/cycle_time_max/10);
        energy0 = (double)care->val[care_power] * total_time0 / 10.0;
        energy_display(this->energy0);
        if ( total_time0 % 20 == 0 && cycle_time != 0 )
        {
            set_buzzer_delay(0, DELAY_BEEP_2S);
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
        if ( progress == 1 && this->onoff == 0 )
        {
            progress = 0;
            total_time0 = 0;
            this->cycle_cpt = 0;
            this->cycle_time = 0;
            this->total_time0 = 0;
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
