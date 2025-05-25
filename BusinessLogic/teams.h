#ifndef TEAMS_H
#define TEAMS_H

#include "BusinessLogic_global.h"
#include <Qstring>

class BUSINESSLOGIC_EXPORT Teams
{
public:
    Teams(const QString &name = "");

    QString getName() const;

    void addMatch(int goalsFor, int goalsAgainst);
    int getPoints() const;
    int getGoalsFor() const;
    int getGoalsAgainst() const;
    int getMatchesPlayed() const;
    void displayData() const;
    void setPoints(int p);
    void setGoalsFor(int g);
    void setGoalsAgainst(int g);
    void setMatchesPlayed(int m);



private:
    QString name;
    int points;
    int goalsFor;
    int goalsAgainst;
    int matchesPlayed;
};

#endif // TEAMS_H
