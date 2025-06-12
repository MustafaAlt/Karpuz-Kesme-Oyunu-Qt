// MUSTAFA ALTIPARMAK 21100011032
// MUSTAFA-ALTIPARMAK-21100011032
/* Hocam, ek özellik olarak ilk olarak bir menü ekranı tasarladım. Bu ekranda oyuncular oyunun zorluk derecesini seçerek yeni oyuna giriş yapabilir veya çıkış yapabilirler. Ayrıca bu ekranda, şu ana kadar ki en yüksek skor ile birlikte oyun süresi bilgisi de veriliyor.

Kolay ve zor mod : zor modda nesneler daha hızlı hareket ediyor..

OYUN 3 SANİYE SAYARAK BAŞLIYOR ANİMASYON ŞEKLİNDE 3 RESMİ 1 SANİYE BOYUNCA BÜYÜYOR MESELA BU ŞEKİLDE EKLEDİM.

Diğer ek özellik ise durdur-oynat butonu. Bu buton ile birlikte oyun içerisinde duraklatma tuşuna basıldığında oyun tamamen duruyor ve ekranda bir simge oluşuyor. Bu ekrandaki simgeye tıklayınca 3'ten geriye sayarak oyunu başlatıyor.

Oyun içerisinde ise bir bomba ekledim. Bomba, normal karpuzlara göre daha hızlı hareket ediyor ve eğer kesilebilirse etrafındaki bütün karpuzları kesiyor. BUNU EKRANIN SAĞ TARAFINDA TOPLAM KAÇ KARPUZ KESİLDİĞİNİ YAZIYOR VE SOL TARAFTA DA BİR RESİM İLE OYUNCU TEBRİK EDİLİYOR. */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qlabel.h>
#include <qmessagebox.h>
#include <QThread>
#include <girisekrani.h>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <qfont.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QScreen *ekran = QGuiApplication::primaryScreen();
    QRect ekranBoyutu = ekran->availableGeometry();

    // Pencerenin boyutunu ayarla
    resize(ekranBoyutu.width(), ekranBoyutu.height()); // hocam tam ekranı netten buldum yapamadım.

    kesilensayaci =0;
    sureSayaci =0;
    QPixmap backgroundImage("C:\\Users\\Mustafa\\Documents\\odev\\images\\back.jpg");


    backgroundLabel = new karpuz(this);
    backgroundLabel->setPixmap(backgroundImage);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 100, ekranBoyutu.width(),ekranBoyutu.height()); // arka planı ayarı .

    QFont font;                                    // burdan sonrası yazılacak olan yazıların boyutu fontu rengi ayarladım.
    font.setPointSize(15);

   QLabel *sure = new karpuz(this);
    sure->setText("Süre : ");
    sure->setFont(font);
    sure->setGeometry(10, 50 ,80, 50);

    surerenk = new karpuz(this);
    surerenk->setText("30");
    surerenk->setFont(font);
    surerenk->setGeometry(90, 50 ,80, 50);
    surerenk->setStyleSheet("color: blue;");



    QLabel *kacirilansayisi = new karpuz(this);
    kacirilansayisi->setFont(font);
    kacirilansayisi->setGeometry(this->width() - 280,0,200,50);
    kacirilansayisi->setText("Kacirilan karpuz sayisi:");

    QLabel * kesilensayisi = new karpuz(this);
    kesilensayisi->setFont(font);
    kesilensayisi->setGeometry(this->width() - 280,50,200,50);
    kesilensayisi->setText("Kesilen karpuz sayisi:");

    kesilenrakkam = new karpuz(this);
    kesilenrakkam->setFont(font);
    kesilenrakkam->setGeometry(this->width() - 80,50,200,50);
    kesilenrakkam->setText("0");
    kesilenrakkam->setStyleSheet("color: green;");

    kacirilanrakkam = new karpuz(this);
    kacirilanrakkam->setFont(font);
    kacirilanrakkam->setGeometry(this->width() - 80,0,200,50);
    kacirilanrakkam->setText("0");
    kacirilanrakkam->setStyleSheet("color: red;");

    durduroynat = new karpuz (this);
    QPixmap backgroundImage2("C:\\Users\\Mustafa\\Downloads\\Microsoft-Fluentui-Emoji-3d-Play-Or-Pause-Button-3d.512.png");
    durduroynat->setPixmap(backgroundImage2);
    durduroynat->setScaledContents(true);
    durduroynat->setGeometry(backgroundLabel->width()-50,50,50,50);
    durduroynat->show();

    QFile file("C:\\Users\\Mustafa\\Documents\\odev\\kolayzor.txt");           // Dosyadaki en büyük elemanı buldum.
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Dosya açılamadı!";

    }
    QTextStream in(&file);

    QString a;
    while (!in.atEnd())
    {
         a = in.readLine();
    }
    zamanlayici=new QTimer(this);                                          // zamanlayıcalarla sıgnal slot bağlantıları.
    zamanlayici2=new QTimer(this);
    zamanlayici3 = new QTimer(this);
    zamanlayici4 = new QTimer(this);


    if(a=="Kolay"){
        zamanlayici->start(1000);
        zamanlayici2->start(10);
        zamanlayici3->start(5000);
        zamanlayici4->start(400);
        zamanlayici->stop();
        zamanlayici2->stop();
        zamanlayici3->stop();
        zamanlayici4->stop();
    }
    else{
        zamanlayici->start(1000);
        zamanlayici2->start(5);
        zamanlayici3->start(7000);
        zamanlayici4->start(600);
        zamanlayici->stop();
        zamanlayici2->stop();
        zamanlayici3->stop();
        zamanlayici4->stop();

    }
    animasyon();

    connect(zamanlayici4,SIGNAL(timeout()),this,SLOT(olustur()));
    connect(zamanlayici,SIGNAL(timeout()),this,SLOT(sureyiAyarla()));
    connect(zamanlayici2,SIGNAL(timeout()),this,SLOT(hareketettir()));
    connect(zamanlayici,SIGNAL(timeout()),this,SLOT(silinecekkontrol()));
    connect(zamanlayici3,SIGNAL(timeout()),this,SLOT(bombaolustur()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::enbuyukBul(){
    QFile file("C:\\Users\\Mustafa\\Documents\\odev\\skorlar.txt");           // Dosyadaki en büyük elemanı buldum.
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





void MainWindow::sureyiAyarla()
{                                                    // oyunun suresi 30 sn olarak yaptım sayac sayıyor. Bu fonksiyon connect fonksiyonuyla 1 sn de bir çalışıyor.
    sureSayaci += 1;


    surerenk->setText(QString::number(30-sureSayaci));
    if(sureSayaci == 30){
        zamanlayici->stop();
        zamanlayici2->stop();
        zamanlayici3->stop();
        zamanlayici4->stop();

        if(enbuyukBul() > kesilensayaci){
            QMessageBox::information(this,"oyunun süresi bitti","En yüksek skoru geçemediniz! \n Kesilen karpuz sayısı : "+QString::number(kesilensayaci)+"\nkaçırılan sayısı"+QString::number(sayac) + "\nen yüksek skor : " +QString::number(enbuyukBul()));
            // hocam açıkçası skoru geçemediyse dosyada olmasının bi anlamaı yok bence o yüzden burda dosyaya yazmadım sadece geçenleri yazdım dosyaya maks skor önemli sadece.
        }
        else{
            QMessageBox::information(this,"OYUNUN SÜRESİ BİTTİ","Tebrikler en yüksek skora sahipsiniz !! \n  Kesilen karpuz sayısı : "+QString::number(kesilensayaci)+"\nkaçırılan sayısı"+QString::number(sayac) + "\nen yüksek skor : " +QString::number(enbuyukBul()));
            QFile dosya("C:\\Users\\Mustafa\\Documents\\odev\\skorlar.txt");
            if (dosya.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream out(&dosya);
                out << "\n"+QString::number(kesilensayaci) <<"";
                dosya.close();
                qDebug() << "Dosyaya metin başarıyla eklendi.";
            }
            else
            {
                qDebug() << "Dosya açılamadı!";
            }


    }
    window()->close();
    girisEkrani * yeni = new girisEkrani();
    yeni->show();


}

}
void MainWindow::olustur(){                                  // burda dosyadan rastgele konum alarak label oluşturdum.


    QFile file("C:\\Users\\Mustafa\\Documents\\odev\\konumlar.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Dosya açılamadı!";

    }

    QTextStream in(&file);


    int satirSayisi = 0;
    while (!in.atEnd())
    {
        in.readLine();
        satirSayisi++;
    }


    int rastgeleSatirNo = rand()%(satirSayisi)+1;

    file.seek(0);


    for(int i = 0; i < rastgeleSatirNo - 1; i++)
    {
        in.readLine();
    }

    QString rastgeleSatir = in.readLine();

    file.close();
    QStringList a = rastgeleSatir.split(' ');
    int x =a[0].toInt();
    int y = a[1].toInt();



    karpuz * yenisi = new karpuz(this);
    yenisi->setGeometry(x,y,35,35);
    yenisi->setStyleSheet("background-color: transparent;");
    QPixmap backgroundImage("C:\\Users\\Mustafa\\Documents\\odev\\images\\1.png");
    yenisi->setPixmap(backgroundImage);
    yenisi->setScaledContents(true);

     yenisi->show();
    buttonlar.push_back(yenisi);

}
void MainWindow::hareketettir()
{                                                      // nesnelerin hareketi için.
    int i;
    for(i = 0;i< buttonlar.size();i++){

        if(!buttonlar[i]->kesildimi){
            if(!buttonlar[i]->bombaMi){
            buttonlar[i]->setGeometry(buttonlar[i]->x(),
                                      buttonlar[i]->y()+1,
                                      buttonlar[i]->width(),
                                      buttonlar[i]->height());
            }
            else{
                buttonlar[i]->setGeometry(buttonlar[i]->x(),
                                          buttonlar[i]->y()+3,
                                          buttonlar[i]->width(),
                                          buttonlar[i]->height());
            }
        }


        if(buttonlar[i]->y() > backgroundLabel->height()){
            sayac += 1;
            kacirilanrakkam->setText(QString::number(sayac));

            buttonlar[i]->deleteLater();
            buttonlar.removeAt(i);


            i--;
        }

    }

}


void MainWindow::mousePressEvent(QMouseEvent *event)                 // tıklamayı alarak labellerin üzerinde mi diye kontrol ettim.
{
    QPoint point = event->pos();
    QLabel *label =durduroynat;
    QPoint labelPos1 = label->mapTo(this, QPoint(0, 0));
    if (point.x() >= labelPos1.x() && point.x() <= labelPos1.x() + durduroynat->width() &&
        point.y() >= labelPos1.y() && point.y() <= labelPos1.y() + durduroynat->height()) {


        if(!durduroynat->kesildimi){
        durduroynat->kesildimi = !durduroynat->kesildimi;
        zamanlayici->stop();
        zamanlayici2->stop();
        zamanlayici3->stop();
        zamanlayici4->stop();
        durduroynat->setGeometry(backgroundLabel->width()/2-200,backgroundLabel->height()/2-200,400,400);
        }
        else{

            animasyon();
            durduroynat->kesildimi = !durduroynat->kesildimi;

        }

    }


    if(zamanlayici->isActive()){


    for (int i = 0; i < buttonlar.size(); i++) {


        if(!buttonlar[i]->kesildimi){
            QLabel *label = buttonlar[i];
            QPoint labelPos = label->mapTo(this, QPoint(0, 0));


            if (point.x() >= labelPos.x() && point.x() <= labelPos.x() + label->width() &&
                point.y() >= labelPos.y() && point.y() <= labelPos.y() + label->height()) {

                QPixmap backgroundImage("C:\\Users\\Mustafa\\Documents\\odev\\images\\2.png");
                buttonlar[i]->setPixmap(backgroundImage);
                buttonlar[i]->setStyleSheet("background-color: transparent;");
                buttonlar[i]->kesildimi = true;
                if(buttonlar[i]->bombaMi){
                    int x = labelPos.x();
                    int y = labelPos.y();
                    for(i =0;i<buttonlar.size();i++){
                        buttonlar[i]->kesildimi = true;
                        kesilensayaci +=1;
                        buttonlar[i]->setPixmap(backgroundImage);
                        buttonlar[i]->setStyleSheet("background-color: transparent;");


                        QPixmap backgroundImage1("C:\\Users\\Mustafa\\Pictures\\Camera Roll\\8c116683a20b78f93f5d37fbce649ee3.webp");


                        QLabel *labelYeni = new karpuz(this);
                        QLabel *yazi = new karpuz(this);
                        QFont font ;
                        font.setPointSize(50);
                        font.setWeight(QFont::Bold);
                        yazi->setFont(font);

                        yazi->setText("+"+QString::number(buttonlar.size()));
                        yazi->setGeometry(backgroundLabel->width()-200,120,200,150);
                        yazi->setStyleSheet("background-color: transparent;");
                        yazi->show();

                        labelYeni->setPixmap(backgroundImage1);
                        labelYeni->setGeometry(backgroundLabel->x()/2,backgroundLabel->y()/2,300,300);
                        labelYeni->setStyleSheet("background-color: transparent;");
                        labelYeni->show();
                        QTimer *zamanlayici=new QTimer(this);       // burda bomba kesilince ekrana kaç karpuz aynı anda kesildiğini ve bomba resmi veriyorum.
                        zamanlayici->start(2000);
                        connect(zamanlayici, &QTimer::timeout, [=]() {       // 3sn sonra silinmesi için zamanlayıcı ayarladım.
                            sil(labelYeni,yazi,zamanlayici);
                        });
                }
                }
                kesilensayaci +=1;
                kesilenrakkam->setText(QString::number(kesilensayaci));


            }

        }

    }
    }


        }

void MainWindow::silinecekkontrol()
{                                                                  // labellerın yapısında kesildikten sonra 3 sn durması için sayac koydum.
    int i ;
    for(i=0;i<buttonlar.size();i++){
        if(buttonlar[i]->kesildimi){
            buttonlar[i]->artir();                  // burda 1 artıyor .
            if(buttonlar[i]->saniyesi == 3){                // eğer 3 olduysa siliyor.
                buttonlar[i]->deleteLater();
                buttonlar.removeAt(i);
            }
            else if (buttonlar[i]->bombaMi){         // eğer bombaysa direk siliyorum .
                buttonlar[i]->deleteLater();
                buttonlar.removeAt(i);
            }

        }
    }
}

void MainWindow::bombaolustur()           // bombaları burada oluşturdum .
{
    QFile file("C:\\Users\\Mustafa\\Documents\\odev\\konumlar.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Dosya açılamadı!";

    }

    QTextStream in(&file);


    int satirSayisi = 0;
    while (!in.atEnd())
    {
        in.readLine();
        satirSayisi++;
    }


    int rastgeleSatirNo = rand()%(satirSayisi)+1;

    file.seek(0);


    for(int i = 0; i < rastgeleSatirNo - 1; i++)
    {
        in.readLine();
    }

    QString rastgeleSatir = in.readLine();

    file.close();
    QStringList a = rastgeleSatir.split(' ');
    int x =a[0].toInt();
    int y = a[1].toInt();



    karpuz * yenisi = new karpuz(this);
    yenisi->setGeometry(x,y,35,35);
    yenisi->setStyleSheet("background-color: transparent;");
    QPixmap backgroundImage("C:\\Users\\Mustafa\\Pictures\\Camera Roll\\Bomb-Cool-icon.png");
    yenisi->setPixmap(backgroundImage);
    yenisi->setScaledContents(true);

    yenisi->show();
    yenisi->bombaMi = true;
    buttonlar.push_back(yenisi);

}

void MainWindow::sil(QLabel * a,QLabel *b,QTimer * zamanlayici)       // bu fonksiyon bombayı kestikten sonra zamanlayici duruyor tek sefer çalışması için.
{
    a->deleteLater();                                                // ekrana gelen resmi ve kesilen karpuz sayısını siliyor.
    b->deleteLater();
    zamanlayici->stop();
}

void MainWindow::animasyon(){

    QLabel * a = new QLabel(this);
    QString c ;
    if(sayac11 == 3){
      c= "C:\\Users\\Mustafa\\Downloads\\Icons8-Windows-8-Numbers-3-Black.512.png";
    }
    else if (sayac11==2){
         c = "C:\\Users\\Mustafa\\Downloads\\Icons8-Windows-8-Numbers-2-Black.512.png";
    }
    else if (sayac11 == 1){
         c ="C:\\Users\\Mustafa\\Downloads\\Icons8-Windows-8-Numbers-1-Black.512.png";
    }
    else if (sayac11 == 0){
        c = "C:\\Users\\Mustafa\\Downloads\\Simpleicons-Team-Simple-Go.512.png";
    }else{
        sayac11 = 3;
        zamanlayici->start();
        zamanlayici2->start();
        zamanlayici3->start();
        zamanlayici4->start();
        durduroynat->setGeometry(backgroundLabel->width()-50,50,50,50);
        return;

    }
    QPixmap b(c);
    sayac11 -=1;
    a->setGeometry((window()->width()/2)-100,(window()->height()/2)-100,200,200);
    a->setPixmap(b);
    a->setStyleSheet("background-color: transparent;");
    a->setScaledContents(true);
    a->show();
    QTimer *zamanlayici5=new QTimer(this);
    zamanlayici5->start(10);
     sayac10 = 0;
    connect(zamanlayici5, &QTimer::timeout, [=]() {
         animasyonhareket(a,zamanlayici5);

    });



}
void MainWindow::animasyonhareket(QLabel * a,QTimer *b){
    sayac10 += 1;
    a->setGeometry(a->x()-2.5,a->y()-2.5,a->height()+5,a->width()+5);
    a->show();
    if(sayac10 >= 100){
        b->stop();
        a->deleteLater();
         animasyon();
         }



    }

