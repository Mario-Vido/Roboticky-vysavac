#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <math.h>
///Adko a Majko2


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{

    //tu je napevno nastavena ip. treba zmenit na to co ste si zadali do text boxu alebo nejaku inu pevnu. co bude spravna
    ipaddress="127.0.0.1"; //192.168.1.11 127.0.0.1
  //  cap.open("http://192.168.1.11:8000/stream.mjpg");
    ui->setupUi(this);
    datacounter=0;
  //  timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(getNewFrame()));
    actIndex=-1;
    useCamera1=false;



    datacounter=0;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    ///prekreslujem obrazovku len vtedy, ked viem ze mam nove data. paintevent sa
    /// moze pochopitelne zavolat aj z inych dovodov, napriklad zmena velkosti okna
    painter.setBrush(Qt::black);//cierna farba pozadia(pouziva sa ako fill pre napriklad funkciu drawRect)
    QPen pero;
    pero.setStyle(Qt::SolidLine);//styl pera - plna ciara
    pero.setWidth(3);//hrubka pera -3pixely
    pero.setColor(Qt::green);//farba je zelena
    QRect rect;
    rect= ui->frame->geometry();//ziskate porametre stvorca,do ktoreho chcete kreslit
    rect.translate(0,15);
    painter.drawRect(rect);

    if(useCamera1==true && actIndex>-1)/// ak zobrazujem data z kamery a aspon niektory frame vo vectore je naplneny
    {
        std::cout<<actIndex<<std::endl;

    }
    else
    {
        if(updateLaserPicture==1) ///ak mam nove data z lidaru
        {
            updateLaserPicture=0;

            painter.setPen(pero);
            //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
         //   std::cout<<copyOfLaserData.numberOfScans<<std::endl;
            for(int k=0;k<copyOfLaserData.numberOfScans/*360*/;k++)
            {
                int dist=copyOfLaserData.Data[k].scanDistance/20; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
                int xp=rect.width()-(rect.width()/2+dist*2*sin((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().x(); //prepocet do obrazovky
                int yp=rect.height()-(rect.height()/2+dist*2*cos((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().y();//prepocet do obrazovky
                if(rect.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                    painter.drawEllipse(QPoint(xp, yp),2,2);
            }
        }
    }
}


/// toto je slot. niekde v kode existuje signal, ktory je prepojeny. pouziva sa napriklad (v tomto pripade) ak chcete dostat data z jedneho vlakna (robot) do ineho (ui)
/// prepojenie signal slot je vo funkcii  on_pushButton_9_clicked
void  MainWindow::setUiValues(double robotX,double robotY,double robotFi)
{
     ui->lineEdit_2->setText(QString::number(robotX));
     ui->lineEdit_3->setText(QString::number(robotY));
     ui->lineEdit_4->setText(QString::number(robotFi));
}

Data dataSave; //ukladame data
Location location;


int MainWindow::processThisRobot(TKobukiData robotdata)
{
    if(dataSave.stop==true)
    {
    if(dataSave.init==true) // inicializujeme data
    {
        dataSave.encoder_Left_prev = robotdata.EncoderLeft;
        dataSave.encoder_Right_prev = robotdata.EncoderRight;
        dataSave.encoder_Angle_prev = robotdata.GyroAngle/100.0;

        dataSave.init = false;
    }

    dataSave.encoder_Left = robotdata.EncoderLeft;
    dataSave.encoder_Right = robotdata.EncoderRight;

    //pretečenie riešime
    if(dataSave.encoder_Left_prev - dataSave.encoder_Left > 60000)
    {
        dataSave.encoder_Left_prev = -(65535 - dataSave.encoder_Left_prev);
    }
    else if(dataSave.encoder_Left_prev - dataSave.encoder_Left < -60000)
    {
         dataSave.encoder_Left_prev = 65535 + dataSave.encoder_Left_prev;
    }
    if(dataSave.encoder_Right_prev - dataSave.encoder_Right > 60000)
    {
        dataSave.encoder_Right_prev = -(65535 - dataSave.encoder_Right_prev);
    }
    else if(dataSave.encoder_Right_prev - dataSave.encoder_Right < -60000)
    {
         dataSave.encoder_Right_prev = 65535 + dataSave.encoder_Right_prev;
    }
    //počítame a riešime uhol
    dataSave.encoder_Angle = robotdata.GyroAngle/100.0 - dataSave.encoder_Angle_prev;
    if(dataSave.encoder_Angle >180.0)
    {
        dataSave.encoder_Angle = dataSave.encoder_Angle - 360.0;
    }
    else if(dataSave.encoder_Angle<-180.0)
    {
        dataSave.encoder_Angle = dataSave.encoder_Angle + 360.0;
    }

    // počítanie vzdialenosti
    location.distance_Left_w = (tick_meter * (dataSave.encoder_Left - dataSave.encoder_Left_prev));
    location.distance_Right_w = tick_meter * (dataSave.encoder_Right - dataSave.encoder_Right_prev);
    location.distance = (location.distance_Left_w + location.distance_Right_w)/2;

    dataSave.encoder_Left_prev = dataSave.encoder_Left;
    dataSave.encoder_Right_prev = dataSave.encoder_Right;

    //vypočítane pozície x,y a uhla
    location.act_posX = location.act_posX + (location.distance * cos(dataSave.encoder_Angle*PI/180.0));
    location.act_posY = location.act_posY + (location.distance * sin(dataSave.encoder_Angle*PI/180.0));

///TU PISTE KOD... TOTO JE TO MIESTO KED NEVIETE KDE ZACAT,TAK JE TO NAOZAJ TU. AK AJ TAK NEVIETE, SPYTAJTE SA CVICIACEHO MA TU NATO STRING KTORY DA DO HLADANIA XXX

    if(datacounter%5)
    {
        ///tu zapisujeme tak aby sme to uvideli v GUI

        emit uiValuesChanged(location.act_posX, location.act_posY, dataSave.encoder_Angle);
    }
    datacounter++;


    }
    return 0;
}

///toto je calback na data z lidaru, ktory ste podhodili robotu vo funkcii on_pushButton_9_clicked
/// vola sa ked dojdu nove data z lidaru
int MainWindow::processThisLidar(LaserMeasurement laserData)
{
    memcpy( &copyOfLaserData,&laserData,sizeof(LaserMeasurement));
    //tu mozete robit s datami z lidaru.. napriklad najst prekazky, zapisat do mapy. naplanovat ako sa prekazke vyhnut.
    // ale nic vypoctovo narocne - to iste vlakno ktore cita data z lidaru
    updateLaserPicture=1;
    update();//tento prikaz prinuti prekreslit obrazovku.. zavola sa paintEvent funkcia


    return 0;

}


void MainWindow::on_pushButton_9_clicked() //start button
{
    dataSave.stop = false;
    forwardspeed=0;
    rotationspeed=0;
    //tu sa nastartuju vlakna ktore citaju data z lidaru a robota
    connect(this,SIGNAL(uiValuesChanged(double,double,double)),this,SLOT(setUiValues(double,double,double)));

    ///setovanie veci na komunikaciu s robotom/lidarom/kamerou.. su tam adresa porty a callback.. laser ma ze sa da dat callback aj ako lambda.
    /// lambdy su super, setria miesto a ak su rozumnej dlzky,tak aj prehladnost... ak ste o nich nic nepoculi poradte sa s vasim doktorom alebo lekarnikom...
    robot.setLaserParameters(ipaddress,52999,5299,/*[](LaserMeasurement dat)->int{std::cout<<"som z lambdy callback"<<std::endl;return 0;}*/std::bind(&MainWindow::processThisLidar,this,std::placeholders::_1));
    robot.setRobotParameters(ipaddress,53000,5300,std::bind(&MainWindow::processThisRobot,this,std::placeholders::_1));

    ///ked je vsetko nasetovane tak to tento prikaz spusti (ak nieco nieje setnute,tak to normalne nenastavi.cize ak napr nechcete kameru,vklude vsetky info o nej vymazte)
    robot.robotStart();


}

void MainWindow::on_pushButton_2_clicked() //forward
{
    //pohyb dopredu
    dataSave.stop = true;
    robot.setTranslationSpeed(500);

}

void MainWindow::on_pushButton_3_clicked() //back
{
    dataSave.stop = true;
    robot.setTranslationSpeed(-250);

}

void MainWindow::on_pushButton_6_clicked() //left
{
    dataSave.stop = true;
    robot.setRotationSpeed(3.14159/2);

}

void MainWindow::on_pushButton_5_clicked()//right
{
    dataSave.stop = true;
    robot.setRotationSpeed(-3.14159/2);

}

void MainWindow::on_pushButton_4_clicked() //stop
{
    dataSave.stop = false;
    robot.setTranslationSpeed(0);

}




void MainWindow::on_pushButton_clicked()
{
    if(useCamera1==true)
    {
        useCamera1=false;

        ui->pushButton->setText("use camera");
    }
    else
    {
        useCamera1=true;

        ui->pushButton->setText("use laser");
    }
}

void MainWindow::getNewFrame()
{

}
