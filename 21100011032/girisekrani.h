
#ifndef GIRISEKRANI_H
#define GIRISEKRANI_H

#include <QWidget>

namespace Ui {
class girisEkrani;
}

class girisEkrani : public QWidget
{
    Q_OBJECT

public:
    explicit girisEkrani(QWidget *parent = nullptr);
    ~girisEkrani();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    int    enbuyukBul();

private:
    Ui::girisEkrani *ui;
};

#endif // GIRISEKRANI_H
