#ifndef CARE_H
#define CARE_H

#include <./include/config.h>

static const int ARRAY_PROTOCOL_NAME[][4] = {
{0, IDX_CR45i, IDX_CR40i, IDX_CR30i},
    {IDX_TRANSCUTANEOUS0},
    {IDX_HPR45i, IDX_FISTULA0}
};

#define VEIN_DIAMETER_1 "4-6 mm"
#define VEIN_DIAMETER_2 "6-8 mm"
#define VEIN_DIAMETER_3 "8-10 mm"
#define VEIN_DIAMETER_4 "10-12 mm"
#define VEIN_DIAMETER_5 "12-14 mm"
#define VEIN_DIAMETER_6 "14-16 mm"
#define VEIN_DIAMETER_7 "16-18 mm"

static const char *ARRAY_VEIN_DIAMETER[] = {
    VEIN_DIAMETER_1, VEIN_DIAMETER_2, VEIN_DIAMETER_3, VEIN_DIAMETER_4, VEIN_DIAMETER_5, VEIN_DIAMETER_6, VEIN_DIAMETER_7
};


// Endovenous - Transcutaneous - Proctology
const int PROTOCOLES[][4][13] = {
    {
        // idle
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // cr45i
        { 0, 25, 20, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // cr40i
        { 1, 25, 20, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        // cr30i
        { 2, 16,  8, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
},
{    // Transcutaneous
    { 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
},
{
     // hpr45i
     { 4, 25, 20, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
     { 5, 25, 20, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
}
};

static const int ARRAY_TRANSCUTANEOUS_POWER[] =          { 8,  12};
static const int ARRAY_TRANSCUTANEOUS_POWER_MIN[] =      { 5,  8};
static const int ARRAY_TRANSCUTANEOUS_POWER_MAX[] =      {12, 16};
static const int ARRAY_TRANSCUTANEOUS_PULSEWIDTH[] =     { 2, 3};
static const int ARRAY_TRANSCUTANEOUS_PULSEWIDTH_MIN[] = { 1, 1};
static const int ARRAY_TRANSCUTANEOUS_PULSEWIDTH_MAX[] = { 8, 8};
static const int ARRAY_TRANSCUTANEOUS_DELAY[] =          { 13, 12};
static const int ARRAY_TRANSCUTANEOUS_DELAY_MIN[] =      { 5, 5};
static const int ARRAY_TRANSCUTANEOUS_DELAY_MAX[] =      { 30, 30};

static const int ARRAY_CYCLE_VS_VEINDIAMETER[][11] = {
  {6},                                /* manual */
  {12, 12, 6},                        /* 4 - 6 mm */
  {12, 12, 12, 12, 6},                /* 6 - 8 mm */
  {12,12,12,12,12,12,6},              /* 8 - 10 mm */
  {18,18,18,18,12,12,12,12,12,6},     /* 10 - 12 mm */
  {18,18,18,18,18,18,18,18,18,18,12}, /* 12 - 14 mm */
  {24,24,24,24,24,24,12},             /* 14 - 16 mm */
  {24}                                /* 16 - 18 mm */
};

static const int ARRAY_CYCLE_VS_VEINDIAMETER_LENGTH[]=
{
    1,3,5,7,10,11,7,1
};


#define care_no               0
#define care_power            1
#define care_powermin         2
#define care_powermax         3
#define care_pulsewidth       4
#define care_pulsewidth_min   5
#define care_pulsewidth_max   6
#define care_delay            7
#define care_delay_min        8
#define care_delay_max        9

#define care_veindiameter    10
#define care_manualpreset    11
#define care_faceleg         12

#define CARE_NBRE            13




class Care
{
public:
    Care();
    int val[CARE_NBRE];
    char *protocol_name;
};


/*
typedef struct _CARE_SAVE
{
    int val[CARE_NBRE], date, time, energy;
    char protocole_name[100];
}CARE_SAVE;
*/

#endif // CARE_H
