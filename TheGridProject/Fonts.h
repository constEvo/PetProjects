#ifndef FONTS_H
#define FONTS_H

#include <QString>
#include <QFont>
#include <QFontDatabase>

class GridFonts
{
public:
    GridFonts();

    QFont getTitleFont();
    QFont getHUDFont();

private:
    int id;
    QString HUDFamily;
    QFont TitleFont;
    QFont HUDFont;
};




#endif // FONTS_H
