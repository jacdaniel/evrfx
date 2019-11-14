#include <QDir>
#include <QString>

#include <stdio.h>
#include <util.h>
#include <fileio.h>

/*
 *
 * QString fileName("./sample.txt");
QFile file(fileName);
qDebug () << file.exists();
*/

QString get_usb_drive(QString prefix)
{
    QString out = QString();
    QDir currentDir(prefix);
    currentDir.setFilter(QDir::Dirs);
    QStringList entries = currentDir.entryList();
    for( QStringList::ConstIterator entry=entries.begin(); entry!=entries.end(); ++entry )
    {
        //std::cout << *entry << std::endl;
        QString dirname = *entry;
        if ( dirname.compare(QString(".")) != 0 && dirname.compare(QString("..")) != 0 )
        {
            out = prefix + "/" + dirname;
         }
     }
    return out;
}

QString get_usb_file(QString prefix, QString filename)
{
    QString drive = get_usb_drive(prefix);
    if ( drive.isNull() )
    {
        return QString();
    }
    QString full_filename = drive + QString("/") + filename;
    if ( QFile::exists(full_filename) )
    {
        return full_filename;
    }
    else
    {
        return QString();
    }
}

int exec_sh_cmd(QString cmd)
{
    if ( cmd.isNull() || cmd.isEmpty() )
    {
        return 0;
    }
    QString sh_cmd = QString("sh \"") + cmd +"\" &";
    return exec_cmd((sh_cmd));
}

int exec_cmd(QString cmd)
{
    if ( cmd.isNull() || cmd.isEmpty() )
    {
        return 0;
    }

    system(cmd.toStdString().c_str());
    return 1;
}



/*
char* ConfigWindow::get_update_masterfile()
{
    char *out = NULL_PTR;
    FILE *pFile = NULL_PTR;
    QDir currentDir("/media/pi");
    currentDir.setFilter(QDir::Dirs);
    QStringList entries = currentDir.entryList();
    for( QStringList::ConstIterator entry=entries.begin(); entry!=entries.end(); ++entry )
    {
        //std::cout << *entry << std::endl;
        QString dirname = *entry;
        if(dirname != tr(".") && dirname != tr(".."))
        {
            QString f = "/media/pi/" + dirname + "/evrf_update/update_run.sh";
            pFile = fopen(f.toStdString().c_str(), "r");
            if ( pFile )
            {
                fclose(pFile);
                out = (char*)calloc(1000, sizeof(char));
                sprintf(out, "sh \"/media/pi/%s/evrf_update/update_run.sh\" &", dirname.toStdString().c_str());
            }
         }
     }
    return out;
}
*/
