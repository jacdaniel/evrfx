#ifndef PATIENT_H
#define PATIENT_H



typedef struct _PATIENT
{
    char name[20], age, ceap[10], remark[1000];
}PATIENT;

typedef struct _MASTER_DATABASE_PATIENT
{
    char name[20], age, ceap[10], remark[1000], treatment, treatment_type, pad_connectivity, vein_diameter;
    int date, time, energy, treatment_time;
}MASTER_DATABASE_PATIENT;


typedef struct _USER_DATABASE_PATIENT
{
    char name[20], age, ceap[10], remark[1000], treatment, treatment_type, vein_diameter, pad_connectivity;
    int date, time, treatment_time, energy;
}USER_DATABASE_PATIENT;


#endif // PATIENT_H
