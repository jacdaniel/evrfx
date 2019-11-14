
#include <stdio.h>

#include <./include/util.h>
#include <./include/patient.h>
#include <./include/database.h>

void database_master_write(char *filename, void *_data)
{
    FILE *pFile = NULL_PTR;
    MASTER_DATABASE_PATIENT *data = (MASTER_DATABASE_PATIENT*)_data;
    if ( data == NULL_PTR || filename == NULL_PTR ) return;
    pFile = fopen(filename, "a");
    if ( pFile != NULL_PTR )
    {
        fwrite(data, 1, sizeof(MASTER_DATABASE_PATIENT), pFile);
        fclose(pFile);
    }
}

int database_master_read(char *filename, int no, void *_data)
{
    FILE *pFile = NULL_PTR;
    MASTER_DATABASE_PATIENT *data = (MASTER_DATABASE_PATIENT*)_data;

    if ( data == NULL_PTR || filename == NULL_PTR) return 0;
    pFile = fopen(filename, "r");
    if ( pFile == NULL_PTR ) return 0;
    fseek(pFile, (long)no*sizeof(MASTER_DATABASE_PATIENT), SEEK_SET);
    fread(data, 1, sizeof(MASTER_DATABASE_PATIENT), pFile);
    fclose(pFile);
    return 1;
}


long database_master_nbre(char *filename)
{
    FILE *pFile;
    long size;

    pFile = fopen(filename, "rb");
    if ( pFile == NULL_PTR ) return 0;
    fseek(pFile, 0, SEEK_END);
    size = ftell(pFile);
    fclose(pFile);
    return size/sizeof(MASTER_DATABASE_PATIENT);
}

void database_user_write(char *filename, void *_data)
{
    FILE *pFile = NULL_PTR;

    USER_DATABASE_PATIENT *data = (USER_DATABASE_PATIENT*)_data;
    if ( data == NULL_PTR || filename == NULL_PTR ) return;
    pFile = fopen(filename, "a");
    if ( pFile != NULL_PTR )
    {
        fwrite(data, 1, sizeof(USER_DATABASE_PATIENT), pFile);
        fclose(pFile);
    }
}

int database_user_read(char *filename, int idx, int nbre, void *_data)
{
    FILE *pFile = NULL_PTR;
    USER_DATABASE_PATIENT *data = (USER_DATABASE_PATIENT*)_data;

    if ( data == NULL_PTR || filename == NULL_PTR ) return 0;
    pFile = fopen(filename, "r");
    if ( pFile == NULL_PTR ) return 0;
    fseek(pFile, (long)idx*sizeof(USER_DATABASE_PATIENT), SEEK_SET);
    fread(data, nbre, sizeof(USER_DATABASE_PATIENT), pFile);
    fclose(pFile);
    return 1;
}

long database_user_nbre(char *filename)
{
    FILE *pFile;
    long size;

    pFile = fopen(filename, "rb");
    if ( pFile == NULL_PTR ) return 0;
    fseek(pFile, 0, SEEK_END);
    size = ftell(pFile);
    fclose(pFile);
    return size/sizeof(USER_DATABASE_PATIENT);
}


/*
void Endoveinous::read_user_info(PATIENT0 *p)
{
    if ( p == NULL_PTR ) return;

    QString filename = this->directory + "test.dat";
    QFile file(filename);
    bool ret = file.open(QIODevice::ReadOnly);
    if ( !ret )
    {
        p->name = "";
        p->firstname = "";
        p->gender = 0;
        p->address.no = "";
        p->address.address = "";
        p->address.address2 = "";
        p->address.zip = "";
        p->address.town = "";
        p->ceap = "";
        p->remark = "";
        p->age = 30;
    }
    else
    {
        char buf[500];
        file.readLine(buf, sizeof(buf));

    }
}
*/

/*

void Endoveinous::test0()
{
    QString filename = this->directory + "test.dat";
    QFile file(filename);

    file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);
    file.write("abcd", 4);
    file.write("efgh\n", 5);
    file.write("abcd", 4);
}
*/
