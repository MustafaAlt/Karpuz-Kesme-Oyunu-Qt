// MUSTAFA ALTIPARMAK 21100011032
#ifndef KARPUZ_H
#define KARPUZ_H

#include <QPushButton>
#include <qlabel.h>

class karpuz : public QLabel
{
    Q_OBJECT
public:
    karpuz(QWidget *parent = nullptr);
    bool kesildimi;
    int saniyesi;
    bool bombaMi;
public slots:
    void tikla();
    void artir();
};

#endif // KARPUZ_H
