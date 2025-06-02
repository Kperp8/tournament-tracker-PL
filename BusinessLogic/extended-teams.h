#ifndef EXTENDED_TEAMS_H
#define EXTENDED_TEAMS_H

#include "teams.h"
#include <QVector>
#include <QHash>
#include <QtMath>
#include <QtMath>

class BUSINESSLOGIC_EXPORT ExtendedTeams : public Teams
{
public:
    explicit ExtendedTeams(const QString &name = "");

    void addMatch(const MatchStats &m);

    double goalsPerMatch() const;
    double shootingAccuracy() const;
    double expectedGoalsAccuracy() const;
    double averagePosession() const;
    double averageCorners() const;
    double averagePasses() const;
    QString topScorer() const;
    void setName(const QString &name) override;

private:
    static double poissonProb(double lambda, int k);

    int totalShotsOnTarget = 0;
    int totalShots = 0;
    int totalPasses = 0;
    int totalCorners = 0;
    int totalPossesion = 0;

    QVector<QPair<QString, int>> m_scorers;
    //
};

#endif // EXTENDED_TEAMS_H