#include "VikasAssistant.h"
#include <QTextCodec>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VikasAssistant w;
    w.show();
    return a.exec();
}
