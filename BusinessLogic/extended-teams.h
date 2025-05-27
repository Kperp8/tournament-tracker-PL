#ifndef EXTENDED_TEAMS_H
#define EXTENDED_TEAMS_H

#include "teams.h"
#include "match-specify.h"
#include <QVector>
#include <QHash>
#include <QtMath>
#include <QtMath>


class BUSINESSLOGIC_EXPORT ExtendedTeams : public Teams
{
public:
    explicit ExtendedTeams(const QString& name = "");


    void addMatch(const MatchStats& m);


    const QVector<MatchStats>& matches() const { return m_matches; }
    int  matchCount()           const { return m_matches.size();   }


    double goalsPerMatch()        const;
    double shootingAccuracy()     const;
    double expectedGoalsAccuracy() const;
    QString topScorer()           const;
    void setName(const QString & name) override;

private:

    static double poissonProb(double lambda, int k);


    QVector<MatchStats> m_matches;

    int totalShotsOnTarget = 0;
    int totalShots         = 0;
    int totalExpectedG     = 0;
    QVector<QPair<QString, int>> m_scorers; //czyli vector, ktory przechowuje mapowania (strzelec, liczba goli)
    //
};

#endif // EXTENDED_TEAMS_H
