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
#include <cmath>
#define _hypot hypot
#undef slots
#include<Python.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("straight");
    ui->comboBox->addItem("cross");
    ui->comboBox->addItem("8direction");
    ui->comboBox->addItem("crosses");
    ui->comboBox->addItem("city1");
    ui->comboBox->addItem("city2");
    ui->comboBox->addItem("city3");
    ui->comboBox->addItem("city4");
    ui->comboBox->addItem("city5");
    ui->comboBox->addItem("city6");
    ui->comboBox->addItem("city7");
    ui->comboBox->addItem("expressway1");
    ui->comboBox->addItem("expressway2");

}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    QString appPath=qApp->applicationDirPath();
    QString mapPath=appPath+"/map/"+arg1+".png";
    QImage img(mapPath);
    QImage imgs;
    imgs=img.scaled(ui->label_4->size());
    ui->label_4->setPixmap(QPixmap::fromImage(imgs));
    if(arg1.compare("straight")==0){
        ui->comboBox_2->addItem("single");
        ui->comboBox_2->addItem("double");
        ui->comboBox_2->addItem("random");
    }
    if(arg1.compare("cross")==0){
        ui->comboBox_2->addItem("single1");
        ui->comboBox_2->addItem("single2");
        ui->comboBox_2->addItem("single3");
        ui->comboBox_2->addItem("double1");
        ui->comboBox_2->addItem("double2");
        ui->comboBox_2->addItem("double3");
        ui->comboBox_2->addItem("double4");
        ui->comboBox_2->addItem("double5");
        ui->comboBox_2->addItem("double6");
        ui->comboBox_2->addItem("double7");
        ui->comboBox_2->addItem("double8");
        ui->comboBox_2->addItem("double9");
        ui->comboBox_2->addItem("double10");
        ui->comboBox_2->addItem("double11");
        ui->comboBox_2->addItem("trible1");
        ui->comboBox_2->addItem("trible2");
        ui->comboBox_2->addItem("trible3");
        ui->comboBox_2->addItem("trible4");
        ui->comboBox_2->addItem("trible5");
        ui->comboBox_2->addItem("trible6");
        ui->comboBox_2->addItem("trible7");
        ui->comboBox_2->addItem("trible8");
        ui->comboBox_2->addItem("trible9");
        ui->comboBox_2->addItem("trible10");
        ui->comboBox_2->addItem("trible11");
        ui->comboBox_2->addItem("trible12");
        ui->comboBox_2->addItem("trible13");
        ui->comboBox_2->addItem("trible14");
        ui->comboBox_2->addItem("trible15");
        ui->comboBox_2->addItem("trible16");
        ui->comboBox_2->addItem("fourfold1");
        ui->comboBox_2->addItem("fourfold2");
        ui->comboBox_2->addItem("fourfold3");
        ui->comboBox_2->addItem("fourfold4");
        ui->comboBox_2->addItem("fourfold5");
        ui->comboBox_2->addItem("fourfold6");
        ui->comboBox_2->addItem("fourfold7");
        ui->comboBox_2->addItem("fourfold8");
        ui->comboBox_2->addItem("fourfold9");
        ui->comboBox_2->addItem("fourfold10");
        ui->comboBox_2->addItem("fourfold11");
        ui->comboBox_2->addItem("fourfold12");
        ui->comboBox_2->addItem("fourfold13");
        ui->comboBox_2->addItem("fourfold14");
        ui->comboBox_2->addItem("fourfold15");
        ui->comboBox_2->addItem("fourfold16");
        ui->comboBox_2->addItem("fourfold17");
        ui->comboBox_2->addItem("fourfold18");
        ui->comboBox_2->addItem("fourfold19");
        ui->comboBox_2->addItem("random");
    }

    /*if(arg1.compare("cross")==0){
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
    }*/
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
    if(ui->comboBox->currentText()=="straight"||ui->comboBox->currentText()=="cross"){
        if(ui->comboBox_2->currentText()=="random"){
            QString appPath=qApp->applicationDirPath();
            qDebug("%s",qPrintable(appPath));
            QString sysPath="sys.path.append('"+appPath+"')";
            qDebug("%s",qPrintable(sysPath));
            QByteArray changetoChar=sysPath.toLatin1();

            Py_SetPythonHome((wchar_t *)(L"./Python310"));
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
            QString filesource=appPath+"/net/"+net+".net.xml";
            QString target=path+"/"+ui->textEdit_6->toPlainText()+".net.xml";
            QFile::copy(filesource,target);
        }
        else{
            QString appPath=qApp->applicationDirPath();
            QString filesource=appPath+"/rou/"+rou+".rou.xml";
            QString target=path+"/"+ui->textEdit_6->toPlainText()+".rou.xml";
            QFile::copy(filesource,target);
            filesource=appPath+"/net/"+net+".net.xml";
            target=path+"/"+ui->textEdit_6->toPlainText()+".net.xml";
            QFile::copy(filesource,target);
        }
    }
    else{
        QString appPath=qApp->applicationDirPath();
        qDebug("%s",qPrintable(appPath));
        QString sysPath="sys.path.append('"+appPath+"')";
        qDebug("%s",qPrintable(sysPath));
        QByteArray changetoChar=sysPath.toLatin1();

        Py_SetPythonHome((wchar_t *)(L"./Python310"));
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
        QString filesource=appPath+"/net/"+net+".net.xml";
        QString target=path+"/"+ui->textEdit_6->toPlainText()+".net.xml";
        QFile::copy(filesource,target);
    }

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

    Py_SetPythonHome((wchar_t *)(L"./Python310"));
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

