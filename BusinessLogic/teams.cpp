#include "teams.h"

Teams::Teams(const QString &name)
    : name(name), points(0), goalsFor(0), goalsAgainst(0), matchesPlayed(0) {}

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
