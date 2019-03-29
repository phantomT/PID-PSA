#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //查找可用端口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
            if(serial.open(QIODevice::ReadWrite))
            {
                ui->PortNum->addItem(serial.portName());
                serial.close();
            }
    }
    ui->BaudRatio->setCurrentIndex(10);
    ui->OpenAll->setText(tr("已关闭"));
    ui->PIDRead->setEnabled(false);
    if(ui->SendText->toPlainText()=="")
    {
        ui->ClearSend->setEnabled(false);
        ui->SendData->setEnabled(false);
    }
    if(ui->RecieveText->toPlainText()=="")
    {
        ui->ClearRecieve->setEnabled(false);
        ui->SaveRecieve->setEnabled(false);
        ui->PIDPlot->setEnabled(false);
    }
    if(ui->SettingP->text()==""||ui->SettingI->text()==""||ui->SettingD->text()==""||ui->SettingT->text()=="")
    {
        ui->PIDSend->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_data()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        QString str = ui->RecieveText->toPlainText();
        str += tr(buf);
        ui->RecieveText->clear();
        ui->RecieveText->append(str);
    }
    buf.clear();
}

void MainWindow::on_SaveRecieve_clicked()
{
    QFile file("./data-s.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        out<<ui->RecieveText->toPlainText()<<endl;

        file.close();
    }
}

void MainWindow::on_ClearRecieve_clicked()
{
    ui->RecieveText->clear();
}

void MainWindow::on_PIDRead_clicked()
{
    serial->write("ReadPID\n");
}

void MainWindow::on_PIDSend_clicked()
{
    QString PID = "P:" + ui->SettingP->text() + "I:" + ui->SettingI->text() + "D:" + ui->SettingD->text();
    if(ui->CheckNewLine->isChecked()==true)
        PID += "\r\n";
    serial->write(PID.toLatin1());
}

void MainWindow::on_PIDPlot_clicked()
{

}

void MainWindow::on_SendData_clicked()
{
    QString trans = ui->SendText->toPlainText();
    if(ui->CheckNewLine->isChecked()==true)
        trans += "\r\n";
    serial->write(trans.toLatin1());
}

void MainWindow::on_ClearSend_clicked()
{
    ui->SendText->clear();
}

void MainWindow::on_SendText_cursorPositionChanged()
{
    if(ui->SendText->toPlainText()!="" && ui->OpenAll->text()==tr("已开启"))
    {
        ui->SendData->setEnabled(true);
        ui->ClearSend->setEnabled(true);
    }
    if(ui->SendText->toPlainText()=="")
    {
        ui->ClearSend->setEnabled(false);
        ui->SendData->setEnabled(false);
    }
}

void MainWindow::on_SendText_textChanged()
{
    if(ui->SendText->toPlainText()!="" && ui->OpenAll->text()==tr("已开启"))
    {
        ui->SendData->setEnabled(true);
        ui->ClearSend->setEnabled(true);
    }
    if(ui->SendText->toPlainText()=="")
    {
        ui->ClearSend->setEnabled(false);
        ui->SendData->setEnabled(false);
    }
}

void MainWindow::on_SettingP_textEdited(const QString &arg1)
{
    if(arg1==""||ui->SettingI->text()==""||ui->SettingD->text()==""||ui->SettingT->text()=="")
    {
        ui->PIDSend->setEnabled(false);
    }
    else
    {
        ui->PIDSend->setEnabled(true);
    }
}

void MainWindow::on_SettingI_textEdited(const QString &arg1)
{
    if(arg1==""||ui->SettingP->text()==""||ui->SettingD->text()==""||ui->SettingT->text()=="")
    {
        ui->PIDSend->setEnabled(false);
    }
    else
    {
        ui->PIDSend->setEnabled(true);
    }
}

void MainWindow::on_SettingD_textEdited(const QString &arg1)
{
    if(arg1==""||ui->SettingI->text()==""||ui->SettingP->text()==""||ui->SettingT->text()=="")
    {
        ui->PIDSend->setEnabled(false);
    }
    else
    {
        ui->PIDSend->setEnabled(true);
    }
}

void MainWindow::on_SettingT_textEdited(const QString &arg1)
{
    if(arg1=="")
    {
        ui->PIDPlot->setEnabled(false);
    }
    else
    {
        ui->PIDPlot->setEnabled(true);
        ui->PIDSend->setEnabled(true);
    }
}

void MainWindow::on_RecieveText_historyChanged()
{
    if(ui->RecieveText->toPlainText()=="")
    {
        ui->PIDPlot->setEnabled(false);
    }
    else
    {
        ui->PIDPlot->setEnabled(true);
    }
}

void MainWindow::on_OpenAll_clicked()
{
    if(ui->OpenAll->text() == tr("已关闭"))
    {
        ui->OpenAll->setText(tr("已开启"));
        serial = new QSerialPort;
        serial->setPortName(ui->PortNum->currentText());
        serial->open(QIODevice::ReadWrite);
        serial->setBaudRate(ui->BaudRatio->currentText().toInt());

        switch (ui->DataBit->currentIndex())
        {
        case 5: serial->setDataBits(QSerialPort::Data5);break;
        case 6: serial->setDataBits(QSerialPort::Data6);break;
        case 7: serial->setDataBits(QSerialPort::Data7);break;
        case 8: serial->setDataBits(QSerialPort::Data8);break;
        default: break;
        }

        switch (ui->EOCheck->currentIndex())
        {
        case 0: serial->setParity(QSerialPort::NoParity);break;
        case 1: serial->setParity(QSerialPort::OddParity);break;
        case 2: serial->setParity(QSerialPort::EvenParity);break;
        default: break;
        }

        switch (ui->StopBit->currentIndex())
        {
        case 1: serial->setStopBits(QSerialPort::OneStop);break;
        case 2: serial->setStopBits(QSerialPort::TwoStop);break;
        default: break;
        }
        serial->setFlowControl(QSerialPort::NoFlowControl);

        ui->PortNum->setEnabled(false);
        ui->BaudRatio->setEnabled(false);
        ui->DataBit->setEnabled(false);
        ui->EOCheck->setEnabled(false);
        ui->StopBit->setEnabled(false);
        ui->PIDRead->setEnabled(true);
        ui->PIDSend->setEnabled(true);
        if(ui->SendText->toPlainText()!="")
        {
            ui->SendData->setEnabled(true);
            ui->ClearSend->setEnabled(true);
        }
        else
        {
            ui->ClearSend->setEnabled(false);
            ui->SendData->setEnabled(false);
        }

        QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::read_data);
    }
    else
    {
        ui->OpenAll->setText(tr("已关闭"));
        serial->clear();
        serial->close();
        serial->deleteLater();

        ui->PortNum->setEnabled(true);
        ui->BaudRatio->setEnabled(true);
        ui->DataBit->setEnabled(true);
        ui->EOCheck->setEnabled(true);
        ui->StopBit->setEnabled(true);
        ui->SendData->setEnabled(false);
        ui->PIDRead->setEnabled(false);
        ui->PIDSend->setEnabled(false);
    }
}