#include "technotes.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TechNotes w;
    w.show();
    
    return a.exec();
}
