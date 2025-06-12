
/*Ek özellik olarak ilk olarak bir menü ekranı tasarladım. Bu ekranda oyuncular oyunun zorluk derecesini seçerek yeni oyuna giriş yapabilir veya çıkış yapabilirler. Ayrıca bu ekranda, şu ana kadar ki en yüksek skor ile birlikte oyun süresi bilgisi de veriliyor.

Kolay ve zor mod : zor modda nesneler daha hızlı hareket ediyor..

OYUN 3 SANİYE SAYARAK BAŞLIYOR ANİMASYON ŞEKLİNDE 3 RESMİ 1 SANİYE BOYUNCA BÜYÜYOR MESELA BU ŞEKİLDE EKLEDİM.

Diğer ek özellik ise durdur-oynat butonu. Bu buton ile birlikte oyun içerisinde duraklatma tuşuna basıldığında oyun tamamen duruyor ve ekranda bir simge oluşuyor. Bu ekrandaki simgeye tıklayınca 3'ten geriye sayarak oyunu başlatıyor.

Oyun içerisinde ise bir bomba ekledim. Bomba, normal karpuzlara göre daha hızlı hareket ediyor ve eğer kesilebilirse etrafındaki bütün karpuzları kesiyor. BUNU EKRANIN SAĞ TARAFINDA TOPLAM KAÇ KARPUZ KESİLDİĞİNİ YAZIYOR VE SOL TARAFTA DA BİR RESİM İLE OYUNCU TEBRİK EDİLİYOR. */

#include "girisekrani.h"
#include "ui_girisekrani.h"
#include "mainwindow.h"
#include <qfile.h>
#include <qpixmap.h>
#include <qmessagebox.h>

girisEkrani::girisEkrani(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::girisEkrani)
{
    ui->setupUi(this);
    ui->label_4->setText(QString::number(enbuyukBul()));
    ui->label_5->setText("30");
    QPixmap  background("C:\\Users\\Mustafa\\Documents\\odev\\images\\back.jpg");
    ui->label->setPixmap(background);


}

girisEkrani::~girisEkrani()
{
    delete ui;
}

void girisEkrani::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked() || ui->radioButton_2->isChecked()){
        if(ui->radioButton->isChecked()){
            QFile dosya("C:\\Users\\Mustafa\\Documents\\odev\\kolayzor.txt");
            if (dosya.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream out(&dosya);
                out << "\nZor" <<"";
                dosya.close();
                qDebug() << "Dosyaya metin başarıyla eklendi.";
            }
            else
            {
                qDebug() << "Dosya açılamadı!";
            }

        }



        else{

        QFile dosya("C:\\Users\\Mustafa\\Documents\\odev\\kolayzor.txt");
        if (dosya.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&dosya);
            out << "\nKolay" <<"";
            dosya.close();
            qDebug() << "Dosyaya metin başarıyla eklendi.";
        }
        else
        {
            qDebug() << "Dosya açılamadı!";
        }

    }


        MainWindow * oyun = new MainWindow();
        oyun->show();
        window()->close();
    }
    else{
        QMessageBox::warning(this,"hatalı seçim","Lütfen oyunun zorluk derecesini girin!");
    }


}


void girisEkrani::on_pushButton_2_clicked()
{
    exit(0);
}

int girisEkrani::enbuyukBul(){
    QFile file("C:\\Users\\Mustafa\\Documents\\odev\\skorlar.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Dosya açılamadı!";

    }
    QTextStream in(&file);

    int maxeleman = -1;
    while (!in.atEnd())
    {
        QString a = in.readLine();
        int b = a.toInt();
        if(b > maxeleman){
            maxeleman = b;
        }



    }
    return maxeleman;
}




