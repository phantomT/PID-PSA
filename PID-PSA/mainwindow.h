#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void read_data();

    void on_SaveRecieve_clicked();

    void on_ClearRecieve_clicked();

    void on_PIDRead_clicked();

    void on_PIDSend_clicked();

    void on_PIDPlot_clicked();

    void on_SendData_clicked();

    void on_ClearSend_clicked();

    void on_SendText_cursorPositionChanged();

    void on_SendText_textChanged();

    void on_SettingP_textEdited(const QString &arg1);

    void on_SettingI_textEdited(const QString &arg1);

    void on_SettingD_textEdited(const QString &arg1);

    void on_SettingT_textEdited(const QString &arg1);

    void on_RecieveText_historyChanged();

    void on_OpenAll_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTimer *timer;
};

#endif // MAINWINDOW_H
