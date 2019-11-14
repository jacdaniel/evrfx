#ifndef FILEIO_H
#define FILEIO_H




QString get_usb_drive(QString prefix);
QString get_usb_file(QString prefix, QString filename);

int exec_sh_cmd(QString cmd);
int exec_cmd(QString cmd);


#endif // FILEIO_H
