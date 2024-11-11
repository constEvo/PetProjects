#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class GridFonts;


class Score : public QGraphicsTextItem
{
public:
    Score(QGraphicsItem* parent = nullptr);
    void increaseScore(int scoreValue);
    void resetScore();
    int getScore();

private:
    int score;

    //font
    GridFonts* font;
};

#endif // SCORE_H
