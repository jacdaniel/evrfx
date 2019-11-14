
#include "include/config.h"
#include "include/util.h"
#include <include/endoveinous.h>

void Endoveinous::timer_transcutaneous()
{
    int pedal = pedal_read();

    if ( ( pedal == 1 && this->onoff == 1 ) || ( this->cycle_cpt < care->val[care_pulsewidth] && pedal == 0 && progress == 1 ) )
    {
        if ( progress == 0 )
        {
            progress = 1;
            // this->total_time0 = 0;
            this->cycle_cpt = 0;
            // catheterstatus_display(catheter_read());
            // padstatus_display(pad_read());
            catheter_status_enable(0);
            ht_program(1, care->val[care_power]);
        }
        else
        {
            if ( this->cycle_cpt < care->val[care_pulsewidth] )
            {
                valid_hf(1);
                set_buzzer(1, 0);

            }
            else if ( this->cycle_cpt < care->val[care_pulsewidth]+care->val[care_delay] )
            {
                valid_hf(0);
                set_buzzer(0, 0);
            }
            this->cycle_cpt++;
            if ( this->cycle_cpt >  care->val[care_pulsewidth]+care->val[care_delay] )
            {
                this->cycle_cpt = 0;
                this->cycle_count++;
                cycle_count_display(this->cycle_count);
            }

            total_time0++;
            if ( this->total_time0 % 10 == 0 )
                time_display(this->total_time0);
        }
    }
    else
    {
        if ( progress == 1 )
        {
            progress = 0;
            // total_time0 = 0;
             ht_program(0, 0);
             set_buzzer(0, 0);
        }
    }
}

