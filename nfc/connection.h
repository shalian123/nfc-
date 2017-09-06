#ifndef CONNECTION_H
#define CONNECTION_H

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
                "name varchar(20),"
                "position varchar(20),"
                "pressure varchar(20),"
                "tempeture varchar(20),"
                "medium varchar(20),"
                "material varchar(20),"
                "diameter varchar(20),"
                "thickness varchar(20),"
                "image_path varchar(100))");

    query1.exec("insert into Measuring_point values(0,'sha','lian','150MPa','20','无','无','12mm','14mm','C:/Users/hasee/Desktop/nfc-05/nfc/pics/changshi.png')");


    // 创建另一个数据库连接，要使用不同的连接名，这里是“connection2”
    /*QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "connection2");
    db2.setDatabaseName("my2.db");
    if (!db2.open()) {
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    // 这里要指定连接
    QSqlQuery query2(db2);
    query2.exec("create table student (id int primary key, "
                "name varchar(20))");
    query2.exec("insert into student values(10, '是')");
    query2.exec("insert into student values(11, 'MaLiang')");
    query2.exec("insert into student values(12, 'shalian')");*/
    return true;
}

#endif // CONNECTION_H
