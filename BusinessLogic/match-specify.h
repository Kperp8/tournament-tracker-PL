#ifndef MATCH_SPECIFY_H
#define MATCH_SPECIFY_H

#include <QDate>
#include <QStringList>

struct MatchStats
{
    QDate date;
    int goalsFor = 0;
    int goalsAg = 0;
    int shotsOnTgt = 0;
    int shotsTot = 0;
    int expectedG = 0;
    int corners = 0;
    int possesion = 0;
    int passes = 0;
    QStringList scorers;
    bool ustawienia_zaawansowane = false;
};

#endif // MATCH_SPECIFY_H