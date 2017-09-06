#ifndef COLLECTION_H
#define COLLECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    // 创建一个数据库连接，使用“connection1”为连接名
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE", "connection1");//可以省略第二个参数即连接名，创建默认连接
    db1.setDatabaseName("my1.db");//数据库名
    if (!db1.open()) {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    // 这里要指定连接
    QSqlQuery query1(db1);
    //query1.exec("SET NAMES 'Latin1'");//使数据库支持中文
    query1.exec("create table Measuring_point (id int primary key, "
                "pointpart varchar(100),"
                "pressure number(10,3),"
                "tempeture number(10,3),"
                "medium varchar(100),"
                "material varchar(100),"
                "originthickness number(10),"
                "outerdiameter number(10),"
                "deviceid number(19),"
                "devicename varchar(100),"
                "orgseq varchar(30),"
                "equipid number(19),"
                "equipcode varchar(100),"
                "equipname varchar(100),"
                "partual varchar(200))");

   // query1.exec("insert into Measuring_point values(0,'sha','lian','150MPa','20','无','无','12mm','14mm','C:/Users/hasee/Desktop/nfc-04/nfc/pics/changshi.png')");


    QSqlQuery query2(db1);
    //query1.exec("SET NAMES 'Latin1'");//使数据库支持中文
    query2.exec("create table ThicknessRecord (pointid int primary key, "
                "checkdate date(100),"
                "value number(10,2))");


    return true;
}




#endif // COLLECTION_H
