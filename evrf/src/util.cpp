
#include <QDate>
#include <QTime>
// #include <QString>

#include <stdio.h>
#include <string.h>
#include <include/config.h>
#include <include/util.h>

bool file_exist(char *filename)
{
    FILE *pFile;
    pFile = fopen(filename, "r");
    if ( pFile != NULL_PTR )
    {
        fclose(pFile);
        return true;
    }
    return false;
}

void char_return_suppress(char *p)
{
    int N = strlen(p);
    if ( N == 0 ) return;
    if ( p[N-1] == '\n' ) p[N-1] = 0;
}

void hsv2rgb(double h, double s, double v, double *r, double *g, double *b)
{
    double      hh, p, q, t, ff;
    long        i;

    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        *r = v;
        *g = v;
        *b = v;
        return;
    }
    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        *r = v;
        *g = t;
        *b = p;
        break;
    case 1:
        *r = q;
        *g = v;
        *b = p;
        break;
    case 2:
        *r = p;
        *g = v;
        *b = t;
        break;

    case 3:
        *r = p;
        *g = q;
        *b = v;
        break;
    case 4:
        *r = t;
        *g = p;
        *b = v;
        break;
    case 5:
    default:
        *r = v;
        *g = p;
        *b = q;
        break;
    }
}

void seconds_to_hhmmss(int sec, int*hh, int *mm, int *ss)
{
    *ss = sec % 60;
    *mm = (sec / 60 ) % 60;
    *hh = sec / 3600;
}


long get_compact_date_yyyymmdd()
{
    QDate date = QDate::currentDate();
    long ret;

    int yy, mm, dd;
    date.getDate (&yy, &mm, &dd);
    ret = 10000 * yy + 100 * mm + dd;
    return ret;
}

long get_compact_time_hhmm()
{
    QTime time = QTime::currentTime();
    long ret;

    int hh = time.hour();
    int mm = time.minute();
    ret = 100 * hh + mm ;
    return ret;
}

QString get_date_yyyy_mm_dd_from_compactdate(long d)
{
    char tmp[20];
    long yy = d/10000;
    long mm = (d - yy*10000) / 100;
    long dd = d - yy * 10000 - mm * 100;
    sprintf(tmp, "%.4d/%.2d/%.2d", yy, mm, dd);
    return QString(tmp);
}

QString get_time_hh_mm_from_compactdate(long d)
{
    char tmp[20];
    long hh = d/100;
    long mm = (d - hh*100);
    sprintf(tmp, "%.2d:%.2d", hh, mm);
    return QString(tmp);
}


/*
QDate date = QDate::currentDate();
QTime time = QTime::currentTime();

int yy, mm, dd, hh, min, ss;
date.getDate (&yy, &mm, &dd);
hh = time.hour();
min = time.minute();
*/
