#include "Fonts.h"
#include <QList>

GridFonts::GridFonts()
{
    id = QFontDatabase::addApplicationFont(":/fonts/fonts/hudFont.ttf");
    HUDFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    TitleFont = QFont(HUDFamily, 40, QFont::Bold);
    HUDFont = QFont(HUDFamily, 26, QFont::Bold);
}

QFont GridFonts::getTitleFont()
{
    return TitleFont;
}

QFont GridFonts::getHUDFont()
{
    return HUDFont;
}
