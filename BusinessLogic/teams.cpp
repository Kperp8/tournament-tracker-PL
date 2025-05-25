#include "teams.h"
#include <QDebug>

Teams::Teams(const QString &name)
{

    this->name = name;
    this->points = 0;
    this->goalsFor = 0;
    this->goalsAgainst = 0;
    this->matchesPlayed = 0;

}

QString Teams::getName() const {
    return name;
}

void Teams::addMatch(int gf, int ga) {
    goalsFor += gf;
    goalsAgainst += ga;
    matchesPlayed++;

    if (gf > ga)
        points += 3;
    else if (gf == ga)
        points += 1;
    // 0 punktów jeśli przegrana
}

int Teams::getPoints() const {
    return points;
}

int Teams::getGoalsFor() const {
    return goalsFor;
}

int Teams::getGoalsAgainst() const {
    return goalsAgainst;
}

int Teams::getMatchesPlayed() const {
    return matchesPlayed;
}

void Teams::displayData() const
{
    qDebug() << ">> Drużyna:" << name
             << ">> Punkty:" << points
             << ">> Gole zdobyte:" << goalsFor
             << ">> Gole stracone:" << goalsAgainst
             << ">> Mecze:" << matchesPlayed;
}

void Teams::setPoints(int p) { points = p; }
void Teams::setGoalsFor(int g) { goalsFor = g; }
void Teams::setGoalsAgainst(int g) { goalsAgainst = g; }
void Teams::setMatchesPlayed(int m) { matchesPlayed = m; }


