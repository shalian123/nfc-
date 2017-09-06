#include "widget.h"
#include "ui_widget.h"
#include <collection.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QPalette>
#include <QBrush>
#include <QList>
#include <QImage>
#include <QStringList>
#include <QCheckBox>
#include <QFile>
#include <QtNetwork>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
   // setAutoFillBackground(true);   // 这个属性一定要设置
    pixmap.load(":/image/images/UI0"); //初始背景图片
    uid = 0;
    mouse_press = true;

    /********************************TableWidget******************************/
        // 创建表格部件，同时指定行数和列数
    /*    tableWidget = new QTableWidget(this);
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
      //  ui->manageLayout->addWidget(tableWidget);
     //   tableWidget->show();

    QFile file("./test.txt");
   // file.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);//以追加的方式打开，新增加的内容将被追加到文件末尾
    file.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);//以重写的方式打开，再写入新的数
    QTextStream out(&file);
//生成json对象
    QJsonObject thicknessRecordObject_1;
    thicknessRecordObject_1.insert("rfid", "2311asdsdtgdsff");
    thicknessRecordObject_1.insert("pointid", 123354);
    thicknessRecordObject_1.insert("checkdate", "2016-12-01");
    thicknessRecordObject_1.insert("value", 22.13);
    thicknessRecordObject_1.insert("a", 12.21);
    thicknessRecordObject_1.insert("b", 15.32);
    thicknessRecordObject_1.insert("c", 12.36);
    thicknessRecordObject_1.insert("d", 12.98);
    thicknessRecordObject_1.insert("e", 15.32);
    thicknessRecordObject_1.insert("f", 14.32);
    thicknessRecordObject_1.insert("g", 16.23);
    thicknessRecordObject_1.insert("h", 12.32);
    thicknessRecordObject_1.insert("expflag", "0");

    QJsonObject thicknessRecordObject_2;
    thicknessRecordObject_2.insert("rfid", "2311asdsdtgdsff");
    thicknessRecordObject_2.insert("pointid", 123354);
    thicknessRecordObject_2.insert("checkdate", "2016-12-22");
    thicknessRecordObject_2.insert("value", 22.13);
    thicknessRecordObject_2.insert("a", 12.21);
    thicknessRecordObject_2.insert("b", 15.32);
    thicknessRecordObject_2.insert("c", 12.36);
    thicknessRecordObject_2.insert("d", 12.98);
    thicknessRecordObject_2.insert("e", 15.32);
    thicknessRecordObject_2.insert("f", 14.32);
    thicknessRecordObject_2.insert("g", 16.23);
    thicknessRecordObject_2.insert("h", 12.32);
    thicknessRecordObject_2.insert("expflag", "0");

    QJsonArray versionArray;
    versionArray.append(thicknessRecordObject_1);
    versionArray.append(thicknessRecordObject_2);

    QJsonObject json;
    json.insert("thicknessrecord", QJsonValue(versionArray));

    QJsonDocument document1;
    document1.setObject(json);
    QByteArray byteArray = document1.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    out << strJson;
    out << "\n";
    file.close();


    _uploadManager = new QNetworkAccessManager(this);
   // connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));
   // m_buf = NULL;   //析构函数中，if( m_buf != NULL ) delete[] m_buf;



    if (createConnection()) //连接成功
 {
    // 使用QSqlQuery查询连接1的整张表，先要使用连接名获取该连接
    QSqlDatabase db1 = QSqlDatabase::database("connection1");//database（）静态函数，通过指定链接名来获取相应的数据库连接
    QSqlQuery query1(db1);
    qDebug() << "connection1:";
    //query1.exec("select * from Measuring_point");
    query1.exec("select id,pointpart,originthickness from Measuring_point");
    query1.last();
    int nRow=query1.at()+1;
    query1.first();
    //tableWidget->setColumnCount(nRow);
    //while(query1.next())//这边不能再有了，因为会影响到for循环的query1.next()
    //{
        //qDebug() << "ok";
       // qDebug() << query1.value(0).toInt() << query1.value(1).toString();
    //}

    tableWidget = new QTableWidget(this);
    QStringList header;
    header<<"设备管理"<<"测点部位" <<"公称壁厚(mm)" <<"测量壁厚(mm)"
         <<"测量时间"<<"测量提示"<<"关联状态"<<"更多";
    tableWidget->setRowCount(nRow);//一定要有行和列
    tableWidget->setColumnCount(8);
    tableWidget->setHorizontalHeaderLabels(header);
    /*QPalette pll = tableWidget->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    tableWidget->setPalette(pll);  //和QTextEdit一样，都可以使用样式表QPalette来修改它的背景颜色和背景图片，这里我们把刷子设置为全透明的，就可以是透明的
   */
    ui->manageLayout->addWidget(tableWidget);


              /************第一行的数据******************/
    tableWidget->setItem(0,0,new QTableWidgetItem(query1.value(0).toString()));
    tableWidget->setItem(0,1,new QTableWidgetItem(query1.value(1).toString()));
    tableWidget->setItem(0,2,new QTableWidgetItem(query1.value(2).toString()));

    /********************将数据在table widget显示************************/
    for(int i=1;query1.next();i++){

        tableWidget->setItem(i,0,new QTableWidgetItem(query1.value(0).toString()));
        tableWidget->setItem(i,1,new QTableWidgetItem(query1.value(1).toString()));
        tableWidget->setItem(i,2,new QTableWidgetItem(query1.value(2).toString()));

        QCheckBox* checkBoxSeclect = new QCheckBox();
        QCheckBox* checkBoxInsert = new QCheckBox();
        QCheckBox* checkBoxUpdate = new QCheckBox();
        QCheckBox* checkBoxDelect = new QCheckBox();
        tableWidget->setCellWidget(i,3,checkBoxSeclect);
        tableWidget->setCellWidget(i,4,checkBoxInsert);
        tableWidget->setCellWidget(i,5,checkBoxUpdate);
        tableWidget->setCellWidget(i,6,checkBoxDelect);
        //qDebug() << "ok";
     }

    tableWidget->show();

 }
}

Widget::~Widget()
{
    //if( m_buf != NULL ) delete[] m_buf;
    delete ui;
}




    //方法三：利用QPainter的drawPixmap函数，这种方法只能用在paintEvent()函数中
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
   // QPixmap pixmap(":/image/images/UI.png");
    painter.drawPixmap(0, 0, pixmap);//绘制UI
}


void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        //qDebug()<<"move";
        //鼠标相对于屏幕的位置
        QPoint move_pos = event->globalPos();
        //移动主窗体
        this->move(move_pos - move_point);
    }
}


//发送请求
void Widget::on_pushButton_clicked()
{
    manage = new QNetworkAccessManager(this);
    manage1= new QNetworkAccessManager(this);
    QNetworkRequest network_request;
    QNetworkRequest network_request1;

    /*设置发送数据*/

   //QString cityName = "杭州";

  // network_request.setUrl(QUrl("http://apis.haoservice.com/weather?cityname=%E6%9D%AD%E5%B7%9E&key=4c08a10447eb435e98080000c50f3f77&paybyvas=false"));

   /* 注意：当url里有中文或空格之类的，需要用一些在线转码工具进行url编码，这里纠结了很久*/

  //验证用户
     network_request.setUrl(QUrl("http://172.16.10.24:8081/shsh/nfc/nfc-thickness!checkUser.action?pid=1369&username=superuser&password=admin"));

 //下载测点信息
   // network_request.setUrl(QUrl("http://172.16.10.24:8081/shsh/nfc/nfc-thickness!downloadMeasurePoint.action?token=7eb935fb518e4234b83d3cae22d3873d&pnum=6"));

    //下载测厚记录
  //  network_request1.setUrl(QUrl("http://172.16.10.24:8081/dreamfoil/nfc/nfc-thickness!downloadThicknessRecord.action?token=306d848a21164e23a4ce33a051b6dde7"));
    /*发送get网络请求*/
    reply = manage->get(network_request);
   // manage1->get(network_request1);
    /*建立connect，replyFinished为自定义槽函数，获取api发回来的天气信息（Jason）格式*/
    connect(manage,SIGNAL(finished(QNetworkReply *)),this,SLOT( getReplyFinished(QNetworkReply *)) );
  //  connect(manage1,SIGNAL(finished(QNetworkReply *)),this,SLOT( getReplyFinished(QNetworkReply *)) );
    connect(reply, SIGNAL (downloadProgress(qint64,qint64)),this, SLOT(updateDataReadProgress(qint64,qint64)));
    ui->progressBar_2->setValue(0);
    ui->progressBar_2->show();
}

void Widget::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar_2->setMaximum(totalBytes);
    ui->progressBar_2->setValue(bytesRead);
}

//获取传回的数据
void Widget::getReplyFinished(QNetworkReply *reply)
{
    if(reply->error()!= QNetworkReply::NoError)
       qDebug() << QStringLiteral("下载响应失败");

    QByteArray bytes = reply->readAll();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(bytes,&jsonError);//解析json文档
    if (jsonError.error != QJsonParseError::NoError) {
            qDebug() << QStringLiteral("解析Json失败");//此处可以验证是否获取到天气信息（json格式）
            //qDebug() << bytes;//如果API响应的不是json格式的数据，则不用解析，直接输出
            return;
        }
    QJsonObject data = document.object();//转化为对象，传回的整体是一个对象
    //QJsonArray data = document.array();  // 转化为数组
    qDebug() << "测点信息：" << data;
    qDebug()<<"result:";
    getMeasurePointInfo(data);//获取测点信息
   // getMeasureRecordInfo(data);
}

//获取测点result信息，进一步解析json
void Widget::getMeasurePointInfo(QJsonObject data)
{
    if (data.contains("result"))
    {
     QJsonValue value = data.value("result");
     if(value.isArray()){    //result是数组
        QJsonArray array = value.toArray();
        int nSize = array.size();  // 获取数组大小
        MeasurePointInfo pointInfo;
        //QStringList todayInfoList;//在文本框里显示
        QSqlDatabase db1 = QSqlDatabase::database("connection1");//database（）静态函数，通过指定链接名来获取相应的数据库连接
        QSqlQuery query1(db1);
        for (int i = 0; i < nSize; ++i) {  // 遍历数组
               if(array.at(i).isObject()){  //数组里面又是对象
                   QJsonObject object =array.at(i).toObject();
                   pointInfo.orgseq = object.value("orgseq").toString();//装置序列
                   pointInfo.pointpart = object.value("pointpart").toString();//测点部位
                   pointInfo.equipname = object.value("equipname").toString();//设备名称
                   pointInfo.deviceid = object.value("deviceid").toString();//装置id
                   pointInfo.originthickness = object.value("originthickness").toDouble();//公称壁厚
                   pointInfo.equipcode = object.value("equipcode").toString();//设备编号
                   pointInfo.equipid = object.value("equipid").toInt();       //设备id
                   pointInfo.parturl = object.value("parturl").toString();  //部位图
                   pointInfo.id = object.value("id").toInt();                 //测点id
                   qDebug() << "getMeasurePointInfo:\n" <<pointInfo.orgseq<< pointInfo.pointpart << pointInfo.equipname << pointInfo.deviceid << pointInfo.originthickness
                           <<pointInfo.equipcode<<pointInfo.equipid<<pointInfo.parturl<<pointInfo.id;
                 }
               //插入数据
               query1.prepare("insert into Measuring_point values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");//位置绑定
               query1.bindValue(0,pointInfo.id);
               query1.bindValue(1,pointInfo.pointpart);
               query1.bindValue(10,pointInfo.orgseq);
               query1.bindValue(13,pointInfo.equipname);
               query1.bindValue(8,pointInfo.deviceid);
               query1.bindValue(6,pointInfo.originthickness);
               query1.bindValue(12,pointInfo.equipcode);
               query1.bindValue(11,pointInfo.equipid);
               query1.bindValue(14,pointInfo.parturl);
               query1.exec();

               //更新数据

               /*query1.clear();
               query1.prepare(QString("update pointpart=?,orgseq=?,"
                                      "equipname=?,deviceid=?,"
                                      "originthickness=?,equipcode=?,"
                                      "equipid=?,partural=? where id=%1").arg(pointInfo.id));
               query1.bindValue(1,pointInfo.pointpart);
               query1.bindValue(10,pointInfo.orgseq);
               query1.bindValue(13,pointInfo.equipname);
               query1.bindValue(8,pointInfo.deviceid);
               query1.bindValue(6,pointInfo.originthickness);
               query1.bindValue(12,pointInfo.equipcode);
               query1.bindValue(11,pointInfo.equipid);
               query1.bindValue(14,pointInfo.partural);
               query1.exec();
              */
            }


    }
 }
}
//获取测点记录的result，并解析
void Widget::getMeasureRecordInfo(QJsonObject data)
{
    if (data.contains("result"))
    {
     QJsonValue value = data.value("result");
     if(value.isArray()){    //result是数组
        QJsonArray array = value.toArray();
        int nSize = array.size();  // 获取数组大小
        MeasureRecordInfo pointInfo;

        QSqlDatabase db1 = QSqlDatabase::database("connection1");//database（）静态函数，通过指定链接名来获取相应的数据库连接
        QSqlQuery query2(db1);
        for (int i = 0; i < nSize; ++i) {  // 遍历数组
               if(array.at(i).isObject()){  //数组里面又是对象
                   QJsonObject object =array.at(i).toObject();
                   pointInfo.checkdate = object.value("checkdate").toString();//测厚时间
                   pointInfo.pointid = object.value("pointid").toInt();//测点id

                   pointInfo.value = object.value("value").toDouble();//测厚值

                   qDebug() << "getMeasureRecordInfo:\n" <<pointInfo.pointid<< pointInfo.checkdate << pointInfo.value;
                 }
               //插入数据
              /* query1.prepare("insert into Measuring_point values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");//位置绑定
               query1.bindValue(0,pointInfo.id);
               query1.bindValue(1,pointInfo.pointpart);
               query1.bindValue(10,pointInfo.orgseq);
               query1.bindValue(13,pointInfo.equipname);
               query1.bindValue(8,pointInfo.deviceid);
               query1.bindValue(6,pointInfo.originthickness);
               query1.bindValue(12,pointInfo.equipcode);
               query1.bindValue(11,pointInfo.equipid);
               query1.bindValue(14,pointInfo.partural);
               query1.exec();

               //更新数据

               /*query1.clear();
               query1.prepare(QString("update pointpart=?,orgseq=?,"
                                      "equipname=?,deviceid=?,"
                                      "originthickness=?,equipcode=?,"
                                      "equipid=?,partural=? where id=%1").arg(pointInfo.id));
               query1.bindValue(1,pointInfo.pointpart);
               query1.bindValue(10,pointInfo.orgseq);
               query1.bindValue(13,pointInfo.equipname);
               query1.bindValue(8,pointInfo.deviceid);
               query1.bindValue(6,pointInfo.originthickness);
               query1.bindValue(12,pointInfo.equipcode);
               query1.bindValue(11,pointInfo.equipid);
               query1.bindValue(14,pointInfo.partural);
               query1.exec();
              */
            }


    }
 }
}




//简单换肤
void Widget::on_updateButton_clicked()
{
    //选择UI的id
    if(uid == 3)
        uid = 0;
    else
        uid = uid + 1;
    //拼凑成UI路径
    QString UIpath = tr(":/image/images/UI%1").arg(uid);
    //qDebug()<<UIpath;
    //加载UI
    pixmap.load(UIpath);
    //产生paintEvent重绘UI
    update();
}



void Widget::on_pushButton_2_clicked()
{

    QFile file("C:/Users/hasee/Desktop/shujv-ceshi/build-untitled-Desktop_QT_5_3-Debug/test.txt");
    file.open(QIODevice::ReadWrite);
    int file_len =file.size();
    QDataStream in(&file);
    qDebug()<<file_len;
    QByteArray fdata=file.readAll();
    if(fdata.isEmpty()){
        return;
    }
    m_buf = new  char[file_len];
    file.close();
    QUrlQuery params;
    params.addQueryItem("token","7eb935fb518e4234b83d3cae22d3873d");
    params.addQueryItem("recordFileString",fdata);
    QString data = params.toString();
    QByteArray postDa=data.toLatin1();
    qDebug()<<fdata;

    //准备头信息
  QNetworkRequest request;
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=utf-8");
 //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/text");
 // request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
  request.setUrl(QUrl("http://172.16.10.24:8081/shsh/nfc/nfc-thickness!uploadThicknessRecordString.action"));
  request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
  request.setRawHeader("Accept","text/html, application/xhtml+xml, */*");
 // request.setRawHeader("Referer","http://localhost:8888/login");
  request.setRawHeader("Accept-Language","zh-CN");
  request.setRawHeader("X-Requested-With","XMLHttpRequest");
  request.setRawHeader("User-Agent","Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)");
  request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
  request.setRawHeader("Accept-Encoding","gzip,deflate");
  //request.setRawHeader("Host","localhost:8888");
 // request.setRawHeader("Content-Length","588");
  request.setRawHeader("Connection","Keep-Alive");
  request.setRawHeader("Cache-Control","no-cache");
  request.setRawHeader("Content-Length",QString::number(postDa.length()).toLatin1());
     qDebug()<<postDa;
  _uploadManager->post(request,postDa);
  connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));

  //connect(_reply, SIGNAL(uploadProgress ( qint64 ,qint64 )), this, SLOT( OnUploadProgress(qint64 ,qint64 )));
}
void Widget::replyFinished(QNetworkReply* reply)
{
    if(reply->error()!= QNetworkReply::NoError)
       qDebug() << QStringLiteral("上传响应失败");

    QByteArray ba = reply->readAll();
   // qDebug()<< ba;
    QJsonParseError jsonpe;
    QJsonDocument json = QJsonDocument::fromJson(ba, &jsonpe);//fromJson解析一个UTF-8编码的JSON文档，并从中创建一个QJsonDocument
    if (jsonpe.error != QJsonParseError::NoError) {
            qDebug() << QStringLiteral("解析Json失败");//此处可以验证是否获取到天气信息（json格式）
            //qDebug() << bytes;//如果API响应的不是json格式的数据，则不用解析，直接输出
            return;
        }

    QJsonObject data = json.object();//转化为对象，传回的整体是一个对象
    //QJsonArray data = document.array();  // 转化为数组
    qDebug() << "上传返回信息：" << data;

    if (data.contains("success"))
   {
       if(data.value("success").toString() == "1"){//成功

          qDebug() << "上传ok";

             }

   }
}
void Widget::OnUploadProgress(qint64 bytesSent,qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesSent);
}

void Widget::on_pushButton_3_clicked()
{

    QFile file("C:/Users/hasee/Desktop/shujv-ceshi/build-untitled-Desktop_QT_5_3-Debug/test.txt");
    file.open(QIODevice::ReadWrite);
    //int file_len =file.size();
    //QByteArray fdata=file.readAll();
    QString data =file.readAll();
    qDebug()<<data;
    QNetworkRequest request;

    request.setUrl(QUrl("http://172.16.10.24:8081/shsh/nfc/nfc-thickness!uploadThicknessRecordString.action"));
   // request.setUrl(QUrl("http://172.16.10.24:8081/shsh/nfc/nfc-thickness!checkUser.action"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Accept","text/html, application/xhtml+xml, */*");
   // request.setRawHeader("Referer","http://localhost:8888/login");
    request.setRawHeader("Accept-Language","zh-CN");
    request.setRawHeader("X-Requested-With","XMLHttpRequest");
    request.setRawHeader("User-Agent","Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)");
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");//窗体数据被编码为名称/值对。这是标准的编码格式
    //request.setRawHeader("Content-Type", "application/json");//如果是json格式访问则加,但是这里我以字符串来发送，将文本里的内容读取发送
    request.setRawHeader("Accept-Encoding","gzip,deflate");
    request.setRawHeader("Connection","Keep-Alive");
    request.setRawHeader("Cache-Control","no-cache");

    QString postData;
   // postData.append("pid=1332&username=superuser&password=admin");
   // postData.append("token=7eb935fb518e4234b83d3cae22d3873d&recordFileString={thicknessrecord:'sha',a:12.21}");
    postData.append("token=7eb935fb518e4234b83d3cae22d3873d&recordFileString=");
    postData+=data;//将文件中的字符串拼接上
    QByteArray postData1=postData.toLatin1();//很重要，要将请求数据编码,toUtf8()也行
    request.setRawHeader("Content-Length",QString::number(postData1.length()).toLatin1());//在请求头部设置请求数据的长度
    _reply = _uploadManager->post(request,postData1);//postData1是请求数据
          qDebug()<<postData1;
    connect( _uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));
    connect( _reply, SIGNAL(uploadProgress ( qint64 ,qint64 )), this, SLOT( OnUploadProgress(qint64 ,qint64 )));
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}
