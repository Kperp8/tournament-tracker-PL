#include "extended-teams.h"

ExtendedTeams::ExtendedTeams(const QString& name): Teams(name)
{}


void ExtendedTeams::addMatch(const MatchStats& m) //parametrem jest referencja do nowo-utworzonego w mainwindow.cpp obiektu struktury
{
    Teams::addMatch(m);

    if(m.ustawienia_zaawansowane)
    {
        totalShotsOnTarget += m.shotsOnTgt;
        totalShots         += m.shotsTot;
        totalPasses         += m.passes;
        totalPossesion      +=m.possesion;
        totalCorners        +=m.corners;

        for (int i = 0; i < m.scorers.size(); ++i)
        {
            const QString& s = m.scorers[i];
            bool found = false;

            for (int j = 0; j < m_scorers.size(); ++j)
                if (m_scorers[j].first == s)
                {
                    m_scorers[j].second++;
                    found = true;
                    break;
                }

            if (!found) m_scorers.append(qMakePair(s, 1));
        }
    }
}


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


double ExtendedTeams::poissonProb(double lambda, int k)
{
    if (lambda <= 0.0) return 0.0;
    return qExp(-lambda) * qPow(lambda, k) / tgamma(k + 1); //gamma to silnia. to jest zwykly rozklad poissona z rpis kol 1
}

double ExtendedTeams::expectedGoalsAccuracy() const
{
    double sumProb = 0.0;
    int    count   = 0;

    const QVector<MatchStats>& mm = matches();
    for (int i = 0; i < mm.size(); ++i)
    {
        if (!mm[i].ustawienia_zaawansowane) continue;

        sumProb += poissonProb(mm[i].expectedG, mm[i].goalsFor);
        ++count;
    }

    return count ? 100.0 * sumProb / count : 0.0;
}

double ExtendedTeams::averageCorners() const
{
    const QVector<MatchStats>& mm = matches();

    return static_cast<double>(totalCorners / mm.size());

}

double ExtendedTeams::averagePasses() const
{
    const QVector<MatchStats>& mm = matches();

    return static_cast<double>(totalPasses / mm.size());

}

double ExtendedTeams::averagePosession() const
{
    const QVector<MatchStats>& mm = matches();

    return static_cast<double>(totalPossesion / mm.size());

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

void ExtendedTeams::setName(const QString & name)
{
    Teams::setName(name);
}
