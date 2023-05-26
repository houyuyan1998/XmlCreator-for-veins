#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPainter>
#include <QImage>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <string.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString appPath=qApp->applicationDirPath();
    QString mapPath=appPath+"/map/cross.png";
    QImage img(mapPath);
    QImage imgs;
    imgs=img.scaled(ui->label_4->size());
    ui->label_4->setPixmap(QPixmap::fromImage(imgs));

    ui->comboBox->addItem("cross");
    ui->comboBox->addItem("2");

    ui->comboBox_2->addItem("1");
    ui->comboBox_2->addItem("2");
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1.compare("cross")==0){
        QString appPath=qApp->applicationDirPath();
        QString mapPath=appPath+"/map/cross.png";
        QImage img(mapPath);
        QImage imgs;
        imgs=img.scaled(ui->label_4->size());
        ui->label_4->setPixmap(QPixmap::fromImage(imgs));
    }
    else if(arg1.compare("2")==0){
        QImage img(":new/map/2.png");
        QImage imgs;
        imgs=img.scaled(ui->label_4->size());
        ui->label_4->setPixmap(QPixmap::fromImage(imgs));
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this,"choose the target folder","./",QFileDialog::ShowDirsOnly);
    ui->textEdit_2->clear();
    ui->textEdit_2->insertPlainText(path);
}


void MainWindow::on_pushButton_clicked()
{
    QString path=ui->textEdit_2->toPlainText();
    QString net=ui->comboBox->currentText();
    QString rou=ui->comboBox_2->currentText();

    QString appPath=qApp->applicationDirPath();
    qDebug("%s",qPrintable(appPath));
    QString sysPath="sys.path.append('"+appPath+"')";
    qDebug("%s",qPrintable(sysPath));
    QByteArray changetoChar=sysPath.toLatin1();

    Py_Initialize();
    if(!Py_IsInitialized())
        qDebug()<<"initial failed";

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import random");
    PyRun_SimpleString("import re");
    PyRun_SimpleString("sys.argv=['python.py']") ;
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString(changetoChar);

    PyObject* obj = PyImport_ImportModule("routeMixer");
    if(!obj){
        qDebug()<<"no file";
    }
    PyObject* pfunc=PyObject_GetAttrString(obj,"mixer");
    if(!pfunc){
        qDebug()<<"no function";
    }

    QString libPath=ui->textEdit_2->toPlainText()+"/"+ui->textEdit_6->toPlainText();
    changetoChar=libPath.toLatin1();
    char* address1=changetoChar.data();
    qDebug("%s",address1);

    int n=20;
    n=ui->textEdit->toPlainText().toInt();
    qDebug("%d",n);
    int CircleRate=50;
    CircleRate=ui->textEdit_5->toPlainText().toInt();
    qDebug("%d",CircleRate);

    PyObject* para=PyTuple_New(3);
    PyTuple_SET_ITEM(para,0,Py_BuildValue("i",n));
    PyTuple_SET_ITEM(para,1,Py_BuildValue("i",CircleRate));
    PyTuple_SET_ITEM(para,2,Py_BuildValue("s",address1));

    PyObject* FuncBack=PyObject_CallObject(pfunc,para);

    Py_Finalize();

    /*
    QFile::copy(":new/xml/net/"+net+".net.xml",path+"/"+net+".net.xml");

    QString str;
    QFile readfile(":new/xml/rou/"+net+"."+rou+".rou.xml");
    if(readfile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&readfile);
        str=stream.readAll();
    }
    readfile.close();

    QFile writefile(path+"/"+net+"."+rou+".rou.xml");
    if(writefile.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream stream2(&writefile);
        QStringList list=str.split("\n");
        for(int i=0;i<list.count();i++){
            if(list.at(i).contains("number=")){
                QString temp=list.at(i+1);
                temp.replace(1,temp.length()-2,ui->textEdit->toPlainText());
                stream2<<list.at(i)<<"\n";
                stream2<<temp<<"\n";
                i++;
            }
            else if(list.at(i).contains("period=")){
                QString temp=list.at(i+1);
                temp.replace(1,temp.length()-2,ui->textEdit_3->toPlainText());
                stream2<<list.at(i)<<"\n";
                stream2<<temp<<"\n";
                i++;
            }
            else{
                if(i==list.count()-1){
                    stream2<<list.at(i);
                }
                else{
                    stream2<<list.at(i)<<"\n";
                }
            }
        }
    }
    writefile.close();

    QMessageBox::information(this,"message","success","ok");
    */
}


void MainWindow::on_pushButton_3_clicked()
{
    QString appPath=qApp->applicationDirPath();
    qDebug("%s",qPrintable(appPath));
    QString sysPath="sys.path.append('"+appPath+"')";
    qDebug("%s",qPrintable(sysPath));
    QByteArray changetoChar=sysPath.toLatin1();

    Py_Initialize();
    if(!Py_IsInitialized())
        qDebug()<<"initial failed";

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import random");
    PyRun_SimpleString("import re");
    PyRun_SimpleString("sys.argv=['python.py']") ;
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString(changetoChar);

    PyObject* obj = PyImport_ImportModule("randomGenerator");
    if(!obj){
        qDebug()<<"no file";
    }
    PyObject* pfunc=PyObject_GetAttrString(obj,"library");
    if(!pfunc){
        qDebug()<<"no function";
    }

    QString netPath=appPath+"/net/"+ui->comboBox->currentText()+".net.xml";
    changetoChar=netPath.toLatin1();
    char* address1=changetoChar.data();
    qDebug("%s",address1);

    int step=20;
    step=ui->textEdit_3->toPlainText().toInt();
    qDebug("%d",step);
    int n=1000;
    n=ui->textEdit_4->toPlainText().toInt();
    qDebug("%d",n);

    QString copyPath=ui->textEdit_2->toPlainText();
    copyPath=copyPath+"/"+ui->textEdit_6->toPlainText()+".rou.xml";
    changetoChar=copyPath.toLatin1();
    char* address2=changetoChar.data();
    qDebug("%s",address2);

    PyObject* para=PyTuple_New(4);
    PyTuple_SET_ITEM(para,0,Py_BuildValue("i",step));
    PyTuple_SET_ITEM(para,1,Py_BuildValue("i",n));
    PyTuple_SET_ITEM(para,2,Py_BuildValue("s",address1));
    PyTuple_SET_ITEM(para,3,Py_BuildValue("s",address2));

    PyObject* FuncBack=PyObject_CallObject(pfunc,para);

    Py_Finalize();
}

