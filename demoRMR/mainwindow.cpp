    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <math.h>
#include <fstream>

//#include "Other files"
///Adko a Majko2


double koncovyX = 0;
double koncovyY = 2.5;
int gg = 0;
int endMat[2][20];
float endMatf[2][20];
const double tick_meter = 0.000085292090497737556558;
const int MAP_WIDTH = 600;
const int MAP_HEIGHT = 500;
//const int endPointX = 35;
//const int endPointY = 46;
const int startPointX = 5;
const int startPointY = 11;
int map1[MAP_WIDTH][MAP_HEIGHT] = {{0}};
int p=0;
const int scanRange = 5;
const int mapWidth = 150;
const int mapHeight = 100;

/////sklusajmodtadetoa
char str[] = "C:/Users/Aardwark/Documents/2sem/projekt/rmrNew/RMR/map.txt";

int** create2DArray(int rows, int cols) {
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i * j;
        }
    }
    return arr;
}

int mapovac(char *filename,int mapa[47][59]) {

    FILE *fp;
    int ROWS = 47;
    int COLS = 59;


    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fscanf(fp,"%c",&mapa[i][j]);
        }
    }


    fclose(fp);

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (mapa[y][x] == 48) {
                // Set the adjacent cells to walls
                if(mapa[y-1][x]==49){
                    mapa[y][x] = 55;
                }
                if(mapa[y+1][x]==49){
                    mapa[y][x] = 55;
                }
                if(mapa[y][x-1]==49){
                    mapa[y][x] = 55;
                }
                if(mapa[y][x+1]==49){
                    mapa[y][x] = 55;
                }

                if(mapa[y-2][x]==49){
                    mapa[y][x] = 55;
                }
                if(mapa[y+2][x]==49){
                    mapa[y][x] = 55;
                }
                if(mapa[y][x-2]==49){
                    mapa[y][x] = 55;
                }
                if(mapa[y][x+2]==49){
                    mapa[y][x] = 55;
                }
           }
        }
    }
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
           if (mapa[y][x] == 55) {
                mapa[y][x] = 49;
           }
        }
    }


    printf("\ntotojestart%.0d\n", mapa[startPointX][startPointY]-47);
    //    SOLVED      pointer musi byt 3(vsetky trojky) potom vsetky stvorky (teraz mi vypise cely riadok) cize dat premenu ktora incrementuje a inkrementacne cislo zapise
    int f = 0;
    char ink = 50;
    while ((mapa[startPointX-1][startPointY] == 48)&&(mapa[startPointX+1][startPointY] == 48)&&(mapa[startPointX][startPointY-1] == 48)&&(mapa[startPointX][startPointY+1] == 48)&&(f < 5000)) {
        printf("  %d  ,",f);

        for (int y = 0; y < ROWS; y++) {
           for (int x = 0; x < COLS; x++) {
                if(mapa[y][x] != 127){


                    if ((mapa[y][x] == ink)&&(mapa[y][x] != 49)&&(mapa[y][x] != 48)) {
                        printf(" %d ",ink);
                        if(mapa[y-1][x]==48){
                            mapa[y-1][x] = ink+1;
                        }
                        if(mapa[y+1][x]==48){
                            mapa[y+1][x] = ink+1;
                        }
                        if(mapa[y][x-1]==48){
                            mapa[y][x-1] = ink+1;
                        }
                        if(mapa[y][x+1]==48){
                            mapa[y][x+1] = ink+1;
                        }
                    }
                    if (mapa[y][x] == 119) {
                        ink = 51;
                        mapa[y][x] = 52;

                    }
              //  ink++;
            }
           }
        }
        ink++;
        f++;
    }

    int y=11;
    int x=5;
    int k=0;
    int bufferX = 5;
    int bufferY = 11;
    int h = 0;
    int d = 0;
    int p = 0;
    int l = 0;
    int n = 0;
//  SOLVED  tusapozret
    if(mapa[y-1][x] != 48){
        y=y-1;
    }
    else if(mapa[y+1][x] != 48){
        y=y+1;
    }
    else if(mapa[y][x-1] != 48){
        x=x-1;
    }
    else if(mapa[y][x+1] != 48){
        x=x+1;
    }
    printf("\nmalobybyt t %c\n",mapa[y][x]);
    endMat[0][0] = x;
    endMat[1][0] = y;
    while((mapa[y][x]-1==mapa[y-1][x])||(mapa[y][x]-1==mapa[y+1][x])||(mapa[y][x]-1==mapa[y][x-1])||(mapa[y][x]-1==mapa[y][x+1])){
        bufferX = x;
        bufferY = y;
        h = 0;
        d = 0;
        p = 0;
        l = 0;
        n = 0;


        while(mapa[y][x]-1==mapa[y-1][x]){
           l++;
           y=y-1;
           if(mapa[y][x]==52){
            mapa[y][x]=119;
           }
        }
        x = bufferX;
        y = bufferY;

        while(mapa[y][x]-1==mapa[y+1][x]){
           p++;
           y=y+1;
           if(mapa[y][x]==52){
            mapa[y][x]=119;
           }
        }
        x = bufferX;
        y = bufferY;

        while(mapa[y][x]-1==mapa[y][x-1]){
           h++;
           x=x-1;
           if(mapa[y][x]==52){
            mapa[y][x]=119;
           }
        }
        x = bufferX;
        y = bufferY;

        while(mapa[y][x]-1==mapa[y][x+1]){
           d++;
           x=x+1;
           if(mapa[y][x]==52){
            mapa[y][x]=119;
           }
        }
        x = bufferX;
        y = bufferY;

        printf("\l = %d p = %d h = %d d = %d\n",l, p, h, d);


        n = l;
        if(p>n){n=p;}
        if(h>n){n=h;}
        if(d>n){n=d;}

        if(n==l){
           y=y-l;

        }
        if(n==p){
           y=y+p;

        }
        if(n==h){
           x=x-h;

        }
        if(n==d){
           x=x+d;

        }

        endMat[0][k] = x;
        endMat[1][k] = y;

        mapa[y][x-3]='u';
        printf("\malo by byt u %c\n",mapa[y][x]);

        k++;
        printf("\k = %d\n",k);
        if(k>500){
           break;
        }
    }
    printf("\nmapayx%c\n",mapa[y][x]);
    printf("\n-1mapayx%c\n",mapa[y][x]-1);


    return 0;
}



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


            for(int k=0;k<copyOfLaserData.numberOfScans/*360*/;k++)
            {

                int dist=copyOfLaserData.Data[k].scanDistance/20; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
                int xp=rect.width()-(rect.width()/2+dist*2*sin((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().x(); //prepocet do obrazovky*/
                int yp=rect.height()-(rect.height()/2+dist*2*cos((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect.topLeft().y();//prepocet do obrazovky*/
                if(rect.contains(xp,yp)){//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                    painter.drawEllipse(QPoint(xp, yp),2,2);
                }
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


double Vzdialenost_Left_w;
double Vzdialenost_Right_w;
double Vzdialenost;

double act_posX= 0.0;
double act_posY= 0.0;
double act_agl= 0.0;
bool engineFire = true;
bool helper = true;
double pointAToPoinB;
int speedingUp = 0;
int speedingDown = 500;
double Kp=0.02;
bool init = true;
double encoder_Left_prev;
double encoder_Right_prev;
double encoder_Angle_prev;

double encoder_Left;
double encoder_Right;
double encoder_Angle;

double diff_Left;
double diff_Right;
bool stop;

void inicialzation(TKobukiData robotdata){
    encoder_Left_prev = robotdata.EncoderLeft;
    encoder_Right_prev = robotdata.EncoderRight;
    encoder_Angle_prev = robotdata.GyroAngle/100.0;
    void loadMapp();
    printf("ahoj");
    init = false;
}

void locationPositon(TKobukiData robotdata){
    encoder_Left = robotdata.EncoderLeft;
    encoder_Right = robotdata.EncoderRight;
    //pretečenie riešime
    if(encoder_Left_prev - encoder_Left > 60000)
    {
        encoder_Left_prev = -(65535 - encoder_Left_prev);
    }
    else if(encoder_Left_prev - encoder_Left < -60000)
    {
         encoder_Left_prev = 65535 + encoder_Left_prev;
    }
    if(encoder_Right_prev - encoder_Right > 60000)
    {
        encoder_Right_prev = -(65535 - encoder_Right_prev);
    }
    else if(encoder_Right_prev - encoder_Right < -60000)
    {
         encoder_Right_prev = 65535 + encoder_Right_prev;
    }
}

void calculatingVzdialenost(TKobukiData robotdata){
    //počítame a riešime uhol
    encoder_Angle = robotdata.GyroAngle/100.0 - encoder_Angle_prev;
    if(encoder_Angle >180.0)
    {
        encoder_Angle = encoder_Angle - 360.0;
    }
    else if(encoder_Angle<-180.0)
    {
        encoder_Angle = encoder_Angle + 360.0;
    }
    // počítanie vzdialenosti
    Vzdialenost_Left_w = (tick_meter * (encoder_Left - encoder_Left_prev));
    Vzdialenost_Right_w = tick_meter * (encoder_Right - encoder_Right_prev);
    Vzdialenost = (Vzdialenost_Left_w + Vzdialenost_Right_w)/2;

    encoder_Left_prev = encoder_Left;
    encoder_Right_prev = encoder_Right;

    //vypočítane pozície x,y a uhla
    act_posX = act_posX + (Vzdialenost * cos(encoder_Angle*PI/180.0));
    act_posY = act_posY + (Vzdialenost * sin(encoder_Angle*PI/180.0));
    pointAToPoinB = sqrt(pow(koncovyX,2)+pow(koncovyY,2))/100;
}

/////////////////////////
double calculateAngle(double x1, double y1, double x2, double y2) {

    double angle = atan2(y2 - y1, x2 - x1);
    angle = angle * 180.0 / 3.14159265358979323846;
    return angle;
}




void loadMapp(){
    printf("nacitalsommapu.\n");
}
//
void MainWindow::PID(){
    //   výpočet uhla a inicializovanie premennych
        double tick = 4;
        double ciselko;
        ciselko = calculateAngle(act_posX, act_posY, koncovyX, koncovyY);
        //okolie bodu kde sa chceme dostať, počítame obvod kruhu a následne vzdialenosť od stredu kruhu, ak vypočítana vzdialenosť od stredu je menšia ako vzdialenosť kružnice od kruhu tak zastavíme
        if(((pow(act_posX-koncovyX,2) + pow(act_posY-koncovyY,2))/100)  <pow(0.005,2)){ // rzchlost na yaklade vydialenosti k bodu
            robot.setTranslationSpeed(0);
            //printf("ciel");
            speedingDown=0;
            printf("pred podmienkou %d",gg);
            printf("\ngg+1 x=%f y%f \n",endMatf[0][gg+1], endMatf[1][gg+1]);
            if(((fabs(endMatf[0][gg+1] +0.4) <= 0.01) )&&((fabs(endMatf[1][gg+1] +0.4) <= 0.01))){
            engineFire = false;
            robot.setTranslationSpeed(0);
            printf("zbehol som");
            cout<<("zbehol som")<<endl;
            }
            else{
            printf("somv elsefit %d",gg);
            cout<<("somv elsefit %d",gg)<<endl;
            gg++;
            koncovyX = endMatf[0][gg];
            koncovyY = endMatf[1][gg];
            }



        }
        else if (engineFire == true) {
            std::cout<<"zelana  "<<koncovyX<<" "<<koncovyY<<" "<<gg<<std::endl;

            // sledujeme či sa nachádzame v tom rozsahu akom sme vypočítali aby sme sa mohli dostať do bodu kde chceme
            if ((encoder_Angle < ciselko + 3) && (encoder_Angle > ciselko - 3)) {

                // prva podmienka rovnaka ako pri zastavení len s vačšou vzdialenost kružnice od stredu && druha podmienka aby nám rychlosť nepreskočilo 500
                if (speedingUp<500 && pow(act_posX-koncovyX,2)/100 + pow(act_posY-koncovyY,2)/100 >= pow(0.1,2)){

                    speedingUp=speedingUp+tick;
                    // uloženie poslednej rýchlosti do spomelania nech spomalujeme od tej rýchlosti kde sme skončili
                    if(speedingUp<500){
                    robot.setTranslationSpeed(speedingUp);
                    speedingDown=speedingUp/*100*(pow(koncovyX-act_posX,2) + pow(koncovyY-act_posY,2))*/;
                    }
                    }
                // podmienka prvá rovnaká ako všetky s kruhom, ak je vzdialenosť od stredu manšia ako vzdialenosť od kružnice tak začneme spomalovať
                //&& aby sme sa nedostali do záporných hodnôt tak spomalujeme len do 10
                else if((pow(act_posX-koncovyX,2) + pow(act_posY-koncovyY,2))/100 <= pow(0.1,2) && speedingDown>150){

                    // uložená rýchlosť sa postupne stále zmänšuječím bližšie ideme
                    speedingDown=speedingDown - 50*(pow(koncovyX-act_posX,2) + pow(koncovyY-act_posY,2));
                    if(speedingDown>500){
                        speedingDown=500;
                    }
                    else if ((speedingDown - 25*(pow(koncovyX-act_posX,2) + pow(koncovyY-act_posY,2)))<150){
                        speedingDown=150;
                    }
                    else{
                        robot.setTranslationSpeed(speedingDown);
                    }

                }
                else if(speedingDown<=150 && speedingDown>=0){
                    speedingDown=150;
                    robot.setTranslationSpeed(150);
                }
            }

            else if ((encoder_Angle > ciselko + 7) || (encoder_Angle < ciselko - 7)) {
                if(encoder_Angle>ciselko+7){
                   robot.setRotationSpeed((Kp*(ciselko-encoder_Angle)));
                   speedingUp=0;
                   speedingDown=0;
                }
                else if((encoder_Angle < ciselko - 7)){
                    robot.setRotationSpeed(Kp*(ciselko-encoder_Angle));
                    speedingUp=0;
                    speedingDown=0;
                }


            }

        }
}
///////////////////////

int MainWindow::processThisRobot(TKobukiData robotdata)
{
    if(init==true)
    {
        inicialzation(robotdata);
    }
    locationPositon(robotdata);
    calculatingVzdialenost(robotdata);
    if(datacounter%5)
    {
        ///tu zapisujeme tak aby sme to uvideli v GUI
        emit uiValuesChanged(act_posX, act_posY, encoder_Angle);
    }
    datacounter++;


 ///////////////zacinap pid//////////////////////
    PID();

    return 0;
}


///toto je calback na data z lidaru, ktory ste podhodili robotu vo funkcii on_pushButton_9_clicked
/// vola sa ked dojdu nove data z lidaru
int MainWindow::processThisLidar(LaserMeasurement laserData)
{

    memcpy( &copyOfLaserData,&laserData,sizeof(LaserMeasurement));
    //tu mozete robit s datami z lidaru.. napriklad najst prekazky, zapisat do mapy. naplanovat ako sa prekazke vyhnut.
    // ale nic vypoctovo narocne - to iste vlakno ktore cita data z lidaru
    if(robot.getTranslationSpeed()==0){

    for(int k=0;k<copyOfLaserData.numberOfScans;k++)
    {

        int dist=copyOfLaserData.Data[k].scanDistance/100; ///vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazeni
        if((dist>=scanRange && dist<=30 && dist<=6.4) || (dist>=scanRange && dist<=30 && dist>=7)){
            int xp=act_posX*10+(cos(((360.0-laserData.Data[k].scanAngle)*3.14159/180.0)+encoder_Angle*3.14159/180.0))*dist; //prepocet do obrazovky
            int yp=act_posY*10+(sin(((360.0-laserData.Data[k].scanAngle)*3.14159/180.0)+encoder_Angle*3.14159/180.0))*dist;//prepocet do obrazovky
            xp += 20;
            yp += 20;
            p=1;
            if (xp>= 0 && xp < mapWidth && yp >= 0 && yp < mapHeight) {
                    map1[xp][yp] = 1;
            }
        }
    }
    }
    updateLaserPicture=1;
    update();//tento prikaz prinuti prekreslit obrazovku.. zavola sa paintEvent funkcia


    return 0;

}


void MainWindow::on_pushButton_9_clicked() //start button
{
    stop = false;
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

void MainWindow::on_pushButton_10_clicked(){
    std::ofstream outfile("map.txt");
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            outfile << (map1[x][y] == 0 ? "0" : "1");
        }
        outfile << std::endl;
    }
    outfile.close();

}

void MainWindow::on_pushButton_2_clicked() //forward
{
    //pohyb dopredu
    stop = true;
    robot.setTranslationSpeed(500);

}

void MainWindow::on_pushButton_3_clicked() //back
{
    stop = true;
    robot.setTranslationSpeed(-250);

}

void MainWindow::on_pushButton_6_clicked() //left
{
    stop = true;
    robot.setRotationSpeed(3.14159/4);

}

void MainWindow::on_pushButton_5_clicked()//right
{
    stop = true;
    robot.setRotationSpeed(-3.14159/4);

}

void MainWindow::on_pushButton_4_clicked() //stop
{
    stop = false;
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
