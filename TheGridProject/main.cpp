#include <QApplication>
#include "View.h"
#include "AudioPlayer.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    AudioPlayer::initialize();

    View* view = new View();
    view->show();

    //AudioPlayer::cleanup();


    return a.exec();
}
