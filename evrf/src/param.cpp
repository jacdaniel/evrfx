

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QDir>

#include <include/config.h>
#include <include/util.h>

#include <include/param.h>

Param::Param(char *filename)
{
    if ( file_exist(filename) )
    {
        FILE *pFile = NULL_PTR;
        // char *out = NULL;

        pFile = fopen(filename, "r");
        /*out = */fgets(this->label_filename, 255, pFile);
        this->label_filename[strlen(this->label_filename)-1] = '\0';
        fclose(pFile);
        label_read(this->label_filename);
        strcpy(base_directory, (QDir::currentPath()).toStdString().c_str());
    }
    else
    {

    }
}

Param::~ Param(){
    for (int i=0; i<this->label_nbre; i++)
        FREE(this->text[i])
    FREE(this->text)
}


void Param::label_read(char *filename)
{
    FILE *pFile = NULL_PTR;
    bool cont = true;
    char tmp[100], *out = NULL_PTR;
    int i;

    pFile = fopen(filename, "r");
    if ( pFile == NULL_PTR )
    {
        return;
    }

    out = fgets(tmp, 10, pFile);
    label_nbre = atoi(tmp);
    out = fgets(tmp, 10, pFile);
    label_size = atoi(tmp);

    this->text = (char**)calloc(label_nbre, sizeof(char*));
    for (i=0; i<label_nbre; i++)
        this->text[i] = (char*)calloc(label_size, sizeof(char*));

    i = 0;
    while ( cont )
    {
        if ( i < label_nbre )
            out = fgets(this->text[i], label_size, pFile);
        if ( out == NULL_PTR )
            cont = false;
        else
        {
            this->text[i][strlen(this->text[i])-1] = '\0';
            i++;
            if ( i >= this->label_nbre )
                cont = false;
        }
    }
    fclose(pFile);
}

char *Param::get_label(int idx)
{
    if ( this->text == NULL_PTR ) return NULL_PTR;
    if ( idx < 0 || idx >= this->label_nbre ) return NULL_PTR;
    return this->text[idx];
}


// QString::fromUtf8("éèçà")

char *Param::get_base_directory()
{
    return this->base_directory;
}


