#include "Score.h"
#include <Fonts.h>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    score = 0;

    font = new GridFonts();

    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::yellow);
    setFont(font->getHUDFont());
    setPos(0, 10);
}


void Score::increaseScore(int scoreValue)
{
    score += scoreValue;
    setPlainText(QString("Score: ") + QString::number(score));
}

void Score::resetScore()
{
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score));
}



int Score::getScore()
{
    return score;
}


