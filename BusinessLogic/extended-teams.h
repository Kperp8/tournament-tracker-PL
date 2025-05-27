#ifndef EXTENDED_TEAMS_H
#define EXTENDED_TEAMS_H

#include "teams.h"
#include "match-specify.h"
#include <QVector>
#include <QHash>
#include <QtMath>
#include <QtMath>

/**  Drużyna z pełną historią meczów + zaawansowane metryki  */
class BUSINESSLOGIC_EXPORT ExtendedTeams : public Teams
{
public:
    explicit ExtendedTeams(const QString& name = "");

    // -- zapisywanie nowego meczu ---------------------------------
    void addMatch(const MatchStats& m);

    // -- dostęp tylko-do-odczytu ----------------------------------
    const QVector<MatchStats>& matches() const { return m_matches; }
    int  matchCount()           const { return m_matches.size();   }

    // -- zagregowane statystyki sezonu ----------------------------
    double goalsPerMatch()        const;    // średnia goli
    double shootingAccuracy()     const;    // % strzałów celnych
    double expectedGoalsAccuracy() const;   // „przewidywalność” (xG vs gole) %
    QString topScorer()           const;    // nazwisko + liczba bramek

private:
    // pomocnik – rozkład Poissona
    static double poissonProb(double lambda, int k);

    // --- DANE ----------------------------------------------------
    QVector<MatchStats> m_matches;

    int totalShotsOnTarget = 0;
    int totalShots         = 0;
    int totalExpectedG     = 0;
    QVector<QPair<QString, int>> m_scorers;
};

#endif // EXTENDED_TEAMS_H
