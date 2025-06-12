// MUSTAFA ALTIPARMAK 21100011032
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qtimer.h>
#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <karpuz.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void olustur();
    void hareketettir();
    void sureyiAyarla();
    void mousePressEvent(QMouseEvent *);
    void silinecekkontrol();
    int enbuyukBul();
    void bombaolustur();
    void sil(QLabel * a,QLabel *b,QTimer * zamanlayici);
    void animasyon();
    void animasyonhareket(QLabel * a,QTimer *b);

private:
    Ui::MainWindow *ui;
    QList<karpuz*> buttonlar;
    int sayac=0;
    int kesilensayaci;
    int sureSayaci;
    karpuz *surerenk;
    karpuz *backgroundLabel ;
    karpuz *sure;
    karpuz * kesilenrakkam;
    karpuz * kacirilanrakkam;
    karpuz * durduroynat;
    QTimer *zamanlayici;
    QTimer *zamanlayici2;
    QTimer *zamanlayici3;
    QTimer *zamanlayici4 ;
    int sayac10 =0;
    int sayac11=3;
};
#endif // MAINWINDOW_H
