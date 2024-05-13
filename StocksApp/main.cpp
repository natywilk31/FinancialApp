/// This is the main class of our app. It will open up our main window.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyleSheet(
        "QWidget {"
        "    background-color: #444444;"
        "}"
        "QLabel {"
        "    font-family: \"Arial Bold\", monospace;"
        "    border-width: 0px;"
        "}"
        "* {"
        "    font-family: \"Terminal\", monospace;"
        "    color: white;"
        "}"
        "QWidget {"
        "    border: 5px solid #0047ab;"
        "    border-radius: 8px;"
        "}"
        "QPushButton {"
        "    border: 2px solid #0047ab;"
        "    border-radius: 5px; "
        "QPushButton {"
        "    background-color: #0047ab;"
        "    color: white;"
        "}"
        "QTabWidget::pane { background-color: #0047ab; }"
        "QTabBar::tab { background-color: #0047ab; color: #white; }"
        "QTabBar::tab:selected { background-color: white; }"
        );
    MainWindow w;
    w.show();
    return a.exec();
}

