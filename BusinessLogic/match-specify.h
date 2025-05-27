#ifndef MATCH_SPECIFY_H
#define MATCH_SPECIFY_H

#include <QDate>
#include <QStringList>

//struktura dla pojedynczego meczu dla jednej druzyny
struct MatchStats
{
    QDate        date;
    int          goalsFor   = 0;
    int          goalsAg    = 0;
    int          shotsOnTgt = 0;
    int          shotsTot   = 0;
    int          expectedG  = 0;
    QStringList  scorers;
};


#endif // MATCH_SPECIFY_H
