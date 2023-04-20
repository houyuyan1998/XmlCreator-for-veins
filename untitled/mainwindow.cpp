#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPainter>
#include <QImage>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage img(":new/map/1.png");
    QImage imgs;
    imgs=img.scaled(ui->label_4->size());
    ui->label_4->setPixmap(QPixmap::fromImage(imgs));

    ui->comboBox->addItem("1");
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
    if(arg1.compare("1")==0){
        QImage img(":new/map/1.png");
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
}

