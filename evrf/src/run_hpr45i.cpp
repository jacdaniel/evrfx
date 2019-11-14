#include <math.h>

#include "include/config.h"
#include "include/util.h"
#include <include/endoveinous.h>

void Endoveinous::timer_hpr45i()
{
    int pedal = pedal_read();

    padstatus_display(pad_read());

    if ( pedal == 1 && this->onoff == 1 )
    {
        if ( progress == 0 )
        {
            progress = 1;
            catheter_status_enable(0);
            ht_program(1, care->val[care_power]);
            set_buzzer_delay(0, DELAY_BEEP_2S);
            this->next_beep = NEXT_BEEP_500J;            
        }
        else
        {
            double pmax = 1500;
            total_time0++;
            if ( this->total_time0 % 10 == 0 )
            {
                time_display(this->total_time0);
            }
            cycle_time++;
            if ( cycle_time >= 6*10 )
            {
                cycle_time = 0;
                this->cycle_cpt++;
                if ( this->cycle_cpt > 0 )
                    this->cycle_cpt = 0;
            }

            // if ( cycle_time % 10 == 0 )
            double power = care->val[care_power] * total_time0 / 10.;
            int power_modulo = (int)((int)(floor(power*100./pmax))%1500);
            power_progressbar_display((int)(floor(power*100./pmax))%100);
            energy0 = (double)care->val[care_power] * total_time0 / 10.0;
            energy_display(this->energy0);
            // int e = (int)floor(this->energy0);

            int just_beep = 0;
            if ( power_modulo >= 500 && this->next_beep == NEXT_BEEP_500J )
            {
                this->next_beep = NEXT_BEEP_1000J;
                set_buzzer_delay(0, DELAY_BEEP_500J);
                just_beep = 1;
            }
            else if ( power_modulo >= 1000 && this->next_beep == NEXT_BEEP_1000J )
            {
                this->next_beep = NEXT_BEEP_1500J;
                set_buzzer_delay(0, DELAY_BEEP_1500J);
                just_beep = 1;
            }
            else if ( ( power_modulo >= 1500 || power_modulo < 500 ) && this->next_beep == NEXT_BEEP_1500J )
            {
                this->next_beep = NEXT_BEEP_500J;
                set_buzzer_delay(0, DELAY_BEEP_1500J);
                just_beep = 1;
            }
            if ( total_time0 % 20 == 0 && just_beep == 0 )
            {
                set_buzzer_delay(0, DELAY_BEEP_2S);
            }

            /*

            if ( e % 1500 == 0 )
            {
                // this->onoff = 0;
                // onoff_display(this->onoff);
                set_buzzer_delay(0, DELAY_BEEP_1500J);
            }
            else
            {
                // int e = (int)floor(this->energy0);
                if ( e % 500 || e % 1000 )
                {
                    set_buzzer_delay(0, DELAY_BEEP_500J);
                }
                if ( this->total_time0 % 20 == 0 && (e % 500 != 0) && (e % 1000 != 0) && (e % 1500 != 0) )
                {
                    set_buzzer_delay(0, DELAY_BEEP_2S);
                }
            }
            */
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
            // set_buzzer_delay(0, 600);
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
