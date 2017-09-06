#include "widget.h"
#include "ui_widget.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QListWidget>
#include <QSplitter>
#include "connection.h"
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QVector>
#include <QQueue>
#include <QTimer>
#include <QTime>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer_count=0;
    pp = new PaintLine();
    layout = new QHBoxLayout();
    layout->addWidget(pp);
    ui->widget_3->setLayout(layout);

/********************************TableWidget******************************/
    // 创建表格部件，同时指定行数和列数
    tableWidget = new QTableWidget(this);
    QStringList header;
    header<<"设备管理"<<"测点部位" <<"公称壁厚(mm)" <<"测量壁厚(mm)"
         <<"测量时间"<<"测量提示"<<"关联状态"<<"更多";
    tableWidget->setRowCount(50);//一定要有行和列
    tableWidget->setColumnCount(8);
    tableWidget->setHorizontalHeaderLabels(header);
    /*QPalette pll = tableWidget->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    tableWidget->setPalette(pll);  //和QTextEdit一样，都可以使用样式表QPalette来修改它的背景颜色和背景图片，这里我们把刷子设置为全透明的，就可以是透明的
   */
    ui->manageLayout->addWidget(tableWidget);
    tableWidget->show();

    // 创建表格项目，并插入到指定单元
    QTableWidgetItem *tableWidgetItem = new QTableWidgetItem("qt");
    tableWidget->setItem(1, 1, tableWidgetItem);
/*
    // 创建表格项目，并将它们作为标头
    QTableWidgetItem *headerV = new QTableWidgetItem("first");
    tableWidget.setVerticalHeaderItem(0, headerV);
    QTableWidgetItem *headerH = new QTableWidgetItem("ID");
    tableWidget.setHorizontalHeaderItem(0, headerH);
   */

/************************************************************************/

    //QVector<QPushButton*> widgetvec;
    //QVector<QPushButton*> widgetvec(8);
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);//去掉边框，保留任务栏菜单

    setAttribute(Qt::WA_TranslucentBackground);//透明
     //setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);   // 这个属性一定要设置
    pixmap.load(":/image/images/mes_icn_figchange2.png"); //初始背景图片

    setFixedSize(750, 500);//设置小部件的最大最小尺寸
    ui->stackedWidget->setCurrentIndex(0);//初始堆栈窗体显示
    ui->stackedWidget->setFrameStyle(QFrame::Panel|QFrame::Raised);//边框阴影凸起

    QPixmap measure_pixmap;
    measure_pixmap.load(":/image/images/icn_mesure_pre.png");
   // ui->icn_mesure_pre->setBackgroundRole( QPalette::Base);
   // ui->icn_mesure_pre->setFixedSize(mypixmap.width(),mypixmap.height());
    ui->icn_mesure_pre->setIcon(measure_pixmap);
    //ui->icn_mesure_pre->setIconSize(QSize(measure_pixmap.width(),measure_pixmap.height()));
    ui->icn_mesure_pre->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->icn_mesure_pre->setText(tr("测量"));

    QPixmap set_pixmap;
    set_pixmap.load(":/image/images/menu_icn_set_pre.png");
    ui->menu_icn_set_pre->setIcon(set_pixmap);
  //  ui->menu_icn_set_pre->setIconSize(QSize(set_pixmap.width(),set_pixmap.height()));
    ui->menu_icn_set_pre->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->menu_icn_set_pre->setText(tr("设置"));

    QPixmap check_pixmap;
    check_pixmap.load(":/image/images/icn_check_pre.png");
    ui->icn_check_pre->setIcon(check_pixmap);
   // ui->icn_check_pre->setIconSize(QSize(70,25));//不需要，在design中设置就行
    ui->icn_check_pre->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//将文字显示在icon下面一行
    ui->icn_check_pre->setText(tr("校准"));

    QPixmap mng_pixmap;
    mng_pixmap.load(":/image/images/icn_mng_pre.png");
    ui->icn_mng_pre->setIcon(mng_pixmap);
    ui->icn_mng_pre->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->icn_mng_pre->setText(tr("测点管理"));

    QPixmap sys_pixmap;
    sys_pixmap.load(":/image/images/icn_syn_pre.png");
    ui->icn_syn_pre->setIcon(sys_pixmap);
    ui->icn_syn_pre->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->icn_syn_pre->setText(tr("数据同步"));

    QPixmap help_pixmap;
    help_pixmap.load(":/image/images/icn_help_pre.png");
    ui->icn_help_pre->setIcon(help_pixmap);
    ui->icn_help_pre->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->icn_help_pre->setText(tr("帮助"));
/*
    clickLabel = new ClickedLabel(this);
    QString path="icn_help.png";
    QPixmap img(path);
    clickLabel->setPixmap(img);
    clickLabel->resize(img.width(),img.height());
    connect(clickLabel,SIGNAL(clicked(ClickedLabel*)),this,SLOT(on_label_clicked()));
*/
    // 创建数据库连接
    if (createConnection()) //连接成功
{
    // 使用QSqlQuery查询连接1的整张表，先要使用连接名获取该连接
    QSqlDatabase db1 = QSqlDatabase::database("connection1");//database（）静态函数，通过指定链接名来获取相应的数据库连接
    QSqlQuery query1(db1);
    qDebug() << "connection1:";
    query1.exec("select * from Measuring_point");
    while(query1.next())
    {
        qDebug() << "ok";
       // qDebug() << query1.value(0).toInt() << query1.value(1).toString();

    }

    // 使用QSqlQuery查询连接2的整张表
   /* QSqlDatabase db2 = QSqlDatabase::database("connection2");
    QSqlQuery query2(db2);

   //插入一条数据
    query2.exec("insert into student (id, name) values (100, 'ChenYun')");
   //插入多个数据，使用占位符
    query2.prepare("insert into student (id, name) values (?, ?)");//位置绑定
    QVariantList ids;
    ids << 20 << 21 << 22;
    query2.addBindValue(ids);
    QVariantList names;
    names << "xiaoming" << "xiaoliang" << "xiaogang";
    query2.addBindValue(names);
    if(!query2.execBatch()) qDebug() << query2.lastError();

      // 更新
   // query2.exec("update student set name = 'xiaohong' where id = 20");
      // 删除
   // query2.exec("delete from student where id = 21");

    qDebug() << "connection2:";
    query2.exec("select * from student");
    while(query2.next())//遍历，在调试窗口输出
    {
        qDebug() << query2.value(0).toInt() << query2.value(1).toString();
    }
    */
 }

}



Widget::~Widget()
{
    delete ui;
}


//测量
void Widget::on_icn_mesure_pre_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

//设置
void Widget::on_menu_icn_set_pre_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);

   // clickLabel = new ClickedLabel(this);
   // connect(clickLabel,SIGNAL(clicked(ClickedLabel*)),this,SLOT(on_label_clicked()));

}

//校准
void Widget::on_icn_check_pre_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

//测点管理
void Widget::on_icn_mng_pre_clicked()
{
   ui->stackedWidget->setCurrentIndex(3);
}

//数据同步
void Widget::on_icn_syn_pre_clicked()
{
   ui->stackedWidget->setCurrentIndex(4);
}

//帮助
void Widget::on_icn_help_pre_clicked()
{
   ui->stackedWidget->setCurrentIndex(5);

   connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget_help,SLOT(setCurrentIndex(int)));

}

//设置双晶探头模式1
void Widget::on_radioButton_6_clicked()
{
  ui->label_11->setText(tr("在两个连续底面回波之间的时间间隔，不计漆层或涂层的厚度"));
}
//设置双晶探头模式2
void Widget::on_radioButton_7_clicked()
{
  ui->label_11->setText(tr("利用单个底面回波，测量金属的实际厚度和涂层厚度(需适配探头)"));
}
//勾上双晶探头测量模式,注意在设计里将双晶和单晶的checkbox的autoexclusive勾上
void Widget::on_checkBox_3_clicked()
{
  ui->label_11->setText(tr("测量从激励脉冲后的精准延迟到第一回波之间的时间间隔"));
}

//设置里的双晶探头后的问号
void Widget::on_pushButton_5_clicked()
{
    dialog1.show();
    dialog1.exec();
    this->show();
}

//在label显示数据库的信息和图片
void Widget::on_pushButton_7_clicked()
{
    // 使用QSqlQuery查询连接2的整张表
  /*  QSqlDatabase db2 = QSqlDatabase::database("connection2");
    QSqlQuery query2(db2);
    query2.exec("select * from student where id = 10");
    while(query2.next())//遍历输出
    {
        text1 = query2.value(1).toString();
    }
    ui->label_13->setText(text1);//设备名称

    query2.exec("select * from student where id = 11");
    while(query2.next())//遍历输出
    {
        text2 = query2.value(1).toString();
    }
    ui->label_14->setText(text2);//测量部位
*/
    // 使用QSqlQuery查询连接1的整张表
    QSqlDatabase db1 = QSqlDatabase::database("connection1");
    QSqlQuery query1(db1);
    query1.exec("select * from Measuring_point where id = 0");
    while(query1.next())//遍历输出
    {
        point_id = query1.value(0).toInt();
        text1 = query1.value(1).toString();
        text2 = query1.value(2).toString();
        text3 = query1.value(3).toString();
        text4 = query1.value(4).toString();
        text5 = query1.value(5).toString();
        text6 = query1.value(6).toString();
        text7 = query1.value(7).toString();
        text8 = query1.value(8).toString();
        img_path = query1.value(9).toString();
    }
    ui->label_13->setText(text1);//设备名称
    ui->label_14->setText(text2);//测量部位
    ui->label_17->setText(text3);//操作压力
    ui->label_19->setText(text4);//操作温度
    ui->label_21->setText(text5);//管内介质
    ui->label_25->setText(text6);//管道材料
    ui->label_38->setText(text7);//公称直径
    ui->label_40->setText(text8);//公称壁厚
        //QImage *image=new QImage("C:/Users/hasee/Desktop/nfc-02/nfc/pics/changshi.png");
    QImage *image = new QImage(img_path);
    ui->label_42->setGeometry(0,0,500,500);
    ui->label_42->setPixmap(QPixmap::fromImage(*image));
        //label->setPixmap(QPixmap("E:/Qt_Program/Chrysanthemum.jpg"));
    ui->label_42->resize(QSize(image->width(),image->height()));//设置QLabel的大小和图片一致
    ui->label_42->show();
    ui->label_42->setScaledContents(true);//自动适应布满整个label
    //注意，最后改成一个表，一个节点包含 id(主键) 名称 压力 温度 介质 材料 直径 壁厚 图片路径（已实现）
}


//模拟测量数据按钮
void Widget::on_pushButton_8_clicked()
{
    timer = new QTimer(this);//创建一个新的定时器
    //ui->pushButton_9->setText("9.03");//setText里只能显示字符串
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(100);
   // ui->label_44->setText("9.03");
    //ui->label_44->setText(s);

}

//定时产生一个随机数
void Widget::timerUpdate()
{

    int rand = qrand()%100;//产生100以内的正整数
    QString s = tr("%1").arg(rand);//将整型转为字符串
    //ui->label_44->setText(s);
    ui->label_44->setText(s);
    widgetvec[timer_count]->setText(s);//显示随机数


}

//点击完成产生随机数
void Widget::on_pushButton_17_clicked()
{
   timer->stop();
   timer_count++;
   /*connect(textButton1,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
   connect(textButton2,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
   connect(textButton3,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
   connect(textButton4,SIGNAL (clicked()),this,SLOT(on_textButton_clicked()));
   connect(textButton5,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
   connect(textButton6,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
   connect(textButton7,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
   connect(textButton8,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
   */
}



//待模拟完，点击按钮跳出测量数据操作窗口
void Widget::on_textButton_clicked()
{
    //dialog2 = new Dialog_mea(this);
    dialog2.show();
    //dialog2.exec();
    //this->show();
    connect(&dialog2,SIGNAL(Dialog_meaEvent()),this,SLOT(SonWindowEventClicked()));


}


//三次测量设置
void Widget::on_radioButton_11_clicked()
{
    //需要更新的时候，循环删除列表中的对象
    QVector<QPushButton*>::iterator i;
    i = widgetvec.begin();
        while(i!=widgetvec.end())
    {
            delete *i;
            i++;
    }
    widgetvec.clear();
    //qDebug()<<widgetvec.size();


    textButton1 =  new QPushButton();
    QPalette pal_1 = textButton1->palette();//调用调色板类
    pal_1.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton1->setPalette(pal_1);
    textButton1->setStyleSheet("background-color:black");
    //widgetvec.enqueue(textButton1);
    widgetvec << textButton1;
   // ui->horizontalLayout_5->addWidget(textButton1);

    textButton2 = new QPushButton();
    QPalette pal_2 = textButton2->palette();//调用调色板类
    pal_2.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton2->setPalette(pal_2);
    textButton2->setStyleSheet("background-color:black");
    //widgetvec.enqueue(textButton2);
     widgetvec << textButton2;
   // ui->horizontalLayout_5->addWidget(textButton2);

    textButton3 = new QPushButton();
    QPalette pal_3 = textButton3->palette();//调用调色板类
    pal_3.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton3->setPalette(pal_3);
    textButton3->setStyleSheet("background-color:black");
   // widgetvec.enqueue(textButton3);
     widgetvec << textButton3;


    ui->horizontalLayout_5->addWidget(widgetvec[0]);
    ui->horizontalLayout_5->addWidget(widgetvec[1]);
    ui->horizontalLayout_5->addWidget(widgetvec[2]);
    connect(textButton1,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
    connect(textButton2,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
    connect(textButton3,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));

}
//四次设置
void Widget::on_radioButton_12_clicked()
{
    /*这种方法widgetvec一直在增，多了就会出错
     if(widgetvec.count()>4)
    {
    for(int i = 4; i < widgetvec.count(); i++)
    {
       //delete widgetvec[i];
       ui->horizontalLayout_5->removeWidget(widgetvec[i]);
    }
    }
    */
    QVector<QPushButton*>::iterator i;
    i = widgetvec.begin();
        while(i!=widgetvec.end())
    {
            delete *i;
            i++;
    }
    widgetvec.clear();
    textButton1 =  new QPushButton();
    QPalette pal_1 = textButton1->palette();//调用调色板类
    pal_1.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton1->setPalette(pal_1);
    textButton1->setStyleSheet("background-color:black");
    widgetvec << textButton1;
    //ui->horizontalLayout_5->addWidget(textButton1);

    textButton2 = new QPushButton();
    QPalette pal_2 = textButton2->palette();//调用调色板类
    pal_2.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton2->setPalette(pal_2);
    textButton2->setStyleSheet("background-color:black");
    widgetvec << textButton2;
    //ui->horizontalLayout_5->addWidget(textButton2);

    textButton3 = new QPushButton();
    QPalette pal_3 = textButton3->palette();//调用调色板类
    pal_3.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton3->setPalette(pal_3);
    textButton3->setStyleSheet("background-color:black");
    widgetvec << textButton3;
   // ui->horizontalLayout_5->addWidget(textButton3);

    textButton4= new QPushButton();
    QPalette pal_4 = textButton4->palette();//调用调色板类
    pal_4.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton4->setPalette(pal_4);
    textButton4->setStyleSheet("background-color:black");
    widgetvec << textButton4;

    //ui->horizontalLayout_5->spacing(10);
   // ui->horizontalLayout_5->addWidget(textButton4);
    ui->horizontalLayout_5->addWidget(widgetvec[0]);
    ui->horizontalLayout_5->addWidget(widgetvec[1]);
    ui->horizontalLayout_5->addWidget(widgetvec[2]);
    ui->horizontalLayout_5->addWidget(widgetvec[3]);
    //ui->horizontalLayout_5->count()
    connect(textButton1,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
    connect(textButton2,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
    connect(textButton3,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
    connect(textButton4,SIGNAL(clicked()),this,SLOT(on_textButton_clicked()));
}
//五次
void Widget::on_radioButton_13_clicked()
{
    QVector<QPushButton*>::iterator i;
    i = widgetvec.begin();
        while(i!=widgetvec.end())
    {
            delete *i;
            i++;
    }
    widgetvec.clear();
    textButton1 = new QPushButton();
    QPalette pal_1 = textButton1->palette();//调用调色板类
    pal_1.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
    textButton1->setPalette(pal_1);
    textButton1->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton1);
    widgetvec << textButton1;

    textButton2 = new QPushButton();
    QPalette pal_2 = textButton2->palette();//调用调色板类
    pal_2.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton2->setPalette(pal_2);
    textButton2->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton2);
    widgetvec << textButton2;

    textButton3 = new QPushButton();
    QPalette pal_3 = textButton3->palette();//调用调色板类
    pal_3.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
    textButton3->setPalette(pal_3);
    textButton3->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton3);
    widgetvec << textButton3;

    textButton4= new QPushButton();
    QPalette pal_4 = textButton4->palette();//调用调色板类
    pal_4.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以

    textButton4->setPalette(pal_4);
    textButton4->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton4);
    widgetvec << textButton4;

    textButton5= new QPushButton();
    QPalette pal_5 = textButton5->palette();//调用调色板类
    pal_5.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以

    textButton5->setPalette(pal_5);
    textButton5->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton5);
    widgetvec << textButton5;
    //ui->horizontalLayout_5->spacing(10);
    ui->horizontalLayout_5->addWidget(widgetvec[0]);
    ui->horizontalLayout_5->addWidget(widgetvec[1]);
    ui->horizontalLayout_5->addWidget(widgetvec[2]);
    ui->horizontalLayout_5->addWidget(widgetvec[3]);
    ui->horizontalLayout_5->addWidget(widgetvec[4]);

}
//六次
void Widget::on_radioButton_14_clicked()
{
    QVector<QPushButton*>::iterator i;
    i = widgetvec.begin();
        while(i!=widgetvec.end())
    {
            delete *i;
            i++;
    }
    widgetvec.clear();

    textButton1 = new QPushButton();
    QPalette pal_1 = textButton1->palette();//调用调色板类
    pal_1.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
    textButton1->setPalette(pal_1);
    textButton1->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton1);
    widgetvec << textButton1;

    textButton2 = new QPushButton();
    QPalette pal_2 = textButton2->palette();//调用调色板类
    pal_2.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton2->setPalette(pal_2);
    textButton2->setStyleSheet("background-color:black");
    widgetvec << textButton2;
     //ui->horizontalLayout_5->addWidget(textButton2);

    textButton3 = new QPushButton();
    QPalette pal_3 = textButton3->palette();//调用调色板类
    pal_3.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton3->setPalette(pal_3);
    textButton3->setStyleSheet("background-color:black");
   //ui->horizontalLayout_5->addWidget(textButton3);
    widgetvec << textButton3;

    textButton4= new QPushButton();
    QPalette pal_4 = textButton4->palette();//调用调色板类
    pal_4.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton4->setPalette(pal_4);
    textButton4->setStyleSheet("background-color:black");
   // ui->horizontalLayout_5->addWidget(textButton4);
    widgetvec << textButton4;

    textButton5= new QPushButton();
    QPalette pal_5 = textButton5->palette();//调用调色板类
    pal_5.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton5->setPalette(pal_5);
    textButton5->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton5);
    widgetvec << textButton5;

    textButton6= new QPushButton();
    QPalette pal_6 = textButton6->palette();//调用调色板类
    pal_6.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton6->setPalette(pal_6);
    textButton6->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton6);
    widgetvec << textButton6;
    //ui->horizontalLayout_5->spacing(10);
    ui->horizontalLayout_5->addWidget(widgetvec[0]);
    ui->horizontalLayout_5->addWidget(widgetvec[1]);
    ui->horizontalLayout_5->addWidget(widgetvec[2]);
    ui->horizontalLayout_5->addWidget(widgetvec[3]);
    ui->horizontalLayout_5->addWidget(widgetvec[4]);
    ui->horizontalLayout_5->addWidget(widgetvec[5]);
}
//七次
void Widget::on_radioButton_15_clicked()
{
    QVector<QPushButton*>::iterator i;
    i = widgetvec.begin();
        while(i!=widgetvec.end())
    {
            delete *i;
            i++;
    }
    widgetvec.clear();
    textButton1 = new QPushButton();
    QPalette pal_1 = textButton1->palette();//调用调色板类
    pal_1.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton1->setPalette(pal_1);
    textButton1->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton1);
    widgetvec << textButton1;

    textButton2 = new QPushButton();
    QPalette pal_2 = textButton2->palette();//调用调色板类
    pal_2.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton2->setPalette(pal_2);
    textButton2->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton2);
    widgetvec << textButton2;

    textButton3 = new QPushButton();
    QPalette pal_3 = textButton3->palette();//调用调色板类
    pal_3.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton3->setPalette(pal_3);
    textButton3->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton3);
    widgetvec << textButton3;


    textButton4= new QPushButton();
    QPalette pal_4 = textButton4->palette();//调用调色板类
    pal_4.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton4->setPalette(pal_4);
    textButton4->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton4);
    widgetvec << textButton4;


    textButton5= new QPushButton();
    QPalette pal_5 = textButton5->palette();//调用调色板类
    pal_5.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton5->setPalette(pal_5);
    textButton5->setStyleSheet("background-color:black");
   // ui->horizontalLayout_5->addWidget(textButton5);
    widgetvec << textButton5;


    textButton6= new QPushButton();
    QPalette pal_6 = textButton6->palette();//调用调色板类
    pal_6.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton6->setPalette(pal_6);
    textButton6->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton6);
    widgetvec << textButton6;


    textButton7= new QPushButton();
    QPalette pal_7 = textButton7->palette();//调用调色板类
    pal_7.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton7->setPalette(pal_7);
    textButton7->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton7);
    widgetvec << textButton7;
    ui->horizontalLayout_5->addWidget(widgetvec[0]);
    ui->horizontalLayout_5->addWidget(widgetvec[1]);
    ui->horizontalLayout_5->addWidget(widgetvec[2]);
    ui->horizontalLayout_5->addWidget(widgetvec[3]);
    ui->horizontalLayout_5->addWidget(widgetvec[4]);
    ui->horizontalLayout_5->addWidget(widgetvec[5]);
    ui->horizontalLayout_5->addWidget(widgetvec[6]);
}
//八次
void Widget::on_radioButton_16_clicked()
{
    QVector<QPushButton*>::iterator i;
    i = widgetvec.begin();
        while(i!=widgetvec.end())
    {
            delete *i;
            i++;
    }
    widgetvec.clear();
    textButton1 = new QPushButton();
    QPalette pal_1 = textButton1->palette();//调用调色板类
    pal_1.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton1->setPalette(pal_1);
    textButton1->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton1);
    widgetvec << textButton1;

    textButton2 = new QPushButton();
    QPalette pal_2 = textButton2->palette();//调用调色板类
    pal_2.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton2->setPalette(pal_2);
    textButton2->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton2);
    widgetvec << textButton2;

    textButton3 = new QPushButton();
    QPalette pal_3 = textButton3->palette();//调用调色板类
    pal_3.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton3->setPalette(pal_3);
    textButton3->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton3);
    widgetvec << textButton3;

    textButton4= new QPushButton();
    QPalette pal_4 = textButton4->palette();//调用调色板类
    pal_4.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton4->setPalette(pal_4);
    textButton4->setStyleSheet("background-color:black");
   // ui->horizontalLayout_5->addWidget(textButton4);
    widgetvec << textButton4;

    textButton5= new QPushButton();
    QPalette pal_5 = textButton5->palette();//调用调色板类
    pal_5.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton5->setPalette(pal_5);
    textButton5->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton5);
    widgetvec << textButton5;

    textButton6= new QPushButton();
    QPalette pal_6 = textButton6->palette();//调用调色板类
    pal_6.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton6->setPalette(pal_6);
    textButton6->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton6);
    widgetvec << textButton6;

    textButton7= new QPushButton();
    QPalette pal_7 = textButton7->palette();//调用调色板类
    pal_7.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton7->setPalette(pal_7);
    textButton7->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton7);
    widgetvec << textButton7;

    textButton8= new QPushButton();
    QPalette pal_8 = textButton8->palette();//调用调色板类
    pal_8.setColor(QPalette::ButtonText, Qt::white);    //设置按钮上的字体颜色，理论上可以，实际上就是可以
   // pal.setColor(QPalette::Button, Qt::green);      //设置按钮背景颜色，理论上可以，实际上不可以
    textButton8->setPalette(pal_8);
    textButton8->setStyleSheet("background-color:black");
    //ui->horizontalLayout_5->addWidget(textButton8);
    widgetvec << textButton8;
    ui->horizontalLayout_5->addWidget(widgetvec[0]);
    ui->horizontalLayout_5->addWidget(widgetvec[1]);
    ui->horizontalLayout_5->addWidget(widgetvec[2]);
    ui->horizontalLayout_5->addWidget(widgetvec[3]);
    ui->horizontalLayout_5->addWidget(widgetvec[4]);
    ui->horizontalLayout_5->addWidget(widgetvec[5]);
    ui->horizontalLayout_5->addWidget(widgetvec[6]);
    ui->horizontalLayout_5->addWidget(widgetvec[7]);
}

//画线
void Widget::on_pushButton_9_clicked()
{
    //pp = new PaintLine();
    //layout = new QHBoxLayout();
    //layout->addWidget(pp);
    //ui->widget_3->setLayout(layout);
    //pp->show();
    //update();
    pp->timer->stop();
}
//
void Widget::SonWindowEventClicked()
{
    //pp = new PaintLine();//放这会每次触发信号都会产生一个窗体
    //layout = new QHBoxLayout();
   // layout->addWidget(pp);
   // ui->widget_3->setLayout(layout);
    //pp->show();
    update();
}
