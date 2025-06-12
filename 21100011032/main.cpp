// MUSTAFA ALTIPARMAK 21100011032
#include "girisekrani.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    girisEkrani w;
    w.show();

    return a.exec();
}
