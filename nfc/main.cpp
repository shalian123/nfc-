#include <QtWidgets/QApplication>
#include "widget.h"
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include "connection.h"
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Widget w;

    // 创建数据库连接
  /*  if (!createConnection()) return 1;

    // 使用QSqlQuery查询连接1的整张表，先要使用连接名获取该连接
    QSqlDatabase db1 = QSqlDatabase::database("connection1");//database（）静态函数，通过指定链接名来获取相应的数据库连接
    QSqlQuery query1(db1);
    qDebug() << "connection1:";
    query1.exec("select * from student");
    while(query1.next())
    {
        qDebug() << query1.value(0).toInt() << query1.value(1).toString();
    }

    // 使用QSqlQuery查询连接2的整张表
    QSqlDatabase db2 = QSqlDatabase::database("connection2");

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
    while(query2.next())//遍历输出
    {
        QString text = query2.value(1).toString();//
        qDebug() << query2.value(0).toInt() << query2.value(1).toString();
    }
*/
    w.show();

    return a.exec();

}

