#ifndef DATABASE_H
#define DATABASE_H

/*
typedef struct _MASTER_CARE_SAVE
{
    long date, time;
    int energy_or_pulse, total_time, vein_diameter;
    char name[100], age, catheter_type;
}MASTER_CARE_SAVE;
*/

/*
typedef struct _USER_CARE_SAVE
{
    long date, time;
    int energy_or_pulse, total_time, vein_diameter;
    char name[100], age, catheter_type;
}USER_CARE_SAVE;
*/

void database_master_write(char *filename, void *_data);
int database_master_read(char *filename, int no, void *_data);
long database_master_nbre(char *filename);

void database_user_write(char *filename, void *_data);
int database_user_read(char *filename, int idx, int nbre, void *_data);

long database_user_nbre(char *filename);



#endif // DATABASE_H
