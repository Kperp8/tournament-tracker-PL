#ifndef TEAMS_H
#define TEAMS_H

#include "BusinessLogic_global.h"
#include "match-specify.h"
#include <QVector>
#include <Qstring>

class BUSINESSLOGIC_EXPORT Teams
{
private:

    QString m_name;
    QVector<MatchStats> m_matches;

    int m_goalsFor = 0;
    int m_goalsAgainst = 0;
    int m_matchesPlayed = 0;
    int m_points = 0;

public:

    explicit Teams(const QString &name = "");

    QString getName() const;

    void addMatch(const MatchStats& m);
    void addMatch(int goalsFor, int goalsAg);
    const QVector<MatchStats>& matches() const;


    int getPoints() const;
    int getGoalsFor() const;
    int getGoalsAgainst() const;
    int getMatchesPlayed() const;

    void setPoints(int p);
    void setGoalsFor(int g);
    void setGoalsAgainst(int g);
    void setMatchesPlayed(int m);

    virtual void displayData() const;

    virtual void setName(const QString & name);

    bool operator==(const Teams& other) const;
    bool operator<(const Teams& other)  const;

};

#endif // TEAMS_H
