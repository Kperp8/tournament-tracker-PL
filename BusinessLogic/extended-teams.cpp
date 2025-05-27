#include "extended-teams.h"

ExtendedTeams::ExtendedTeams(const QString& name)
    : Teams(name)
{}


void ExtendedTeams::addMatch(const MatchStats& m)
{
    m_matches.append(m);

    // 1) klasyczne pola z bazowej klasy Teams
    Teams::addMatch(m.goalsFor, m.goalsAg);

    // 2) akumulatory „zaawansowane”
    totalShotsOnTarget += m.shotsOnTgt;
    totalShots         += m.shotsTot;
    totalExpectedG     += m.expectedG;

    for (int i = 0; i < m.scorers.size(); ++i)
    {
        QString name = m.scorers[i];
        bool found = false;

        for (int j = 0; j < m_scorers.size(); ++j)
        {
            if (m_scorers[j].first == name)
            {
                m_scorers[j].second += 1;
                found = true;
                break;
            }
        }

        if (!found)
            m_scorers.append(qMakePair(name, 1));
    }
}

/*---------------- statystyki sezonowe ----------------*/
double ExtendedTeams::goalsPerMatch() const
{
    return getMatchesPlayed()
    ? static_cast<double>(getGoalsFor()) / getMatchesPlayed()
    : 0.0;
}

double ExtendedTeams::shootingAccuracy() const
{
    return totalShots
               ? 100.0 * static_cast<double>(totalShotsOnTarget) / totalShots
               : 0.0;
}

/*—— rozkład Poissona ———————————————————————————————*/
double ExtendedTeams::poissonProb(double lambda, int k)
{
    if (lambda <= 0.0) return 0.0;
    return qExp(-lambda) * qPow(lambda, k) / tgamma(k + 1); //gamma to silnia
}

double ExtendedTeams::expectedGoalsAccuracy() const
{
    if (!getMatchesPlayed() || totalExpectedG == 0) return 0.0;

    const double lambda = static_cast<double>(totalExpectedG) / getMatchesPlayed();  // średnie xG
    const int    k      = qRound(goalsPerMatch());                                   // średnie gole

    return 100.0 * poissonProb(lambda, k);  // w %
}

QString ExtendedTeams::topScorer() const
{
    if (m_scorers.isEmpty()) return "brak danych";

    int maxGoals = -1;
    QString topName;

    for (int i = 0; i < m_scorers.size(); ++i)
    {
        if (m_scorers[i].second > maxGoals)
        {
            maxGoals = m_scorers[i].second;
            topName = m_scorers[i].first;
        }
    }

    return topName + " (" + QString::number(maxGoals) + ")";
}
