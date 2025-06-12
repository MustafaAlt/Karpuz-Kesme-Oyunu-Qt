
#include "karpuz.h"

karpuz::karpuz(QWidget *parent):QLabel(parent)
{
    kesildimi = false;
    saniyesi = 0;                         // kapruz kesildiğinde 3 sn ekranda durması için sayaç yaptım.
    bombaMi = false;                      // bomba drumuna göre resim ve silime drumunu farklı yaptım.
    connect(this,SIGNAL(clicked()),this,SLOT(tikla()));
}

void karpuz::tikla()
{
    kesildimi = !kesildimi;
}

void karpuz::artir()
{
    saniyesi += 1;
}
