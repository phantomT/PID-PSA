#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int pidtimer;
qreal recdata;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strpath = QApplication::applicationDirPath();
    strpath += "/icon.ico";

    MainWindow w;
    w.setWindowTitle(QStringLiteral("PID-Parameters-Setting-Assistant"));
    a.setWindowIcon(QIcon(strpath));
    w.show();

    return a.exec();
}
