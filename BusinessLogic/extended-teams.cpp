#include "extended-teams.h"

ExtendedTeams::ExtendedTeams(const QString& name)
    : Teams(name)
{}


void ExtendedTeams::addMatch(const MatchStats& m) //parametrem jest referencja do nowo-utworzonego w mainwindow.cpp obiektu struktury
{
    m_matches.append(m); //QVector<MatchStats> m_matches; znajdziesz w skladowych prywatnych extended-teams.h


    Teams::addMatch(m.goalsFor, m.goalsAg); //bazowy konstruktor dla podstawowych danych


    totalShotsOnTarget += m.shotsOnTgt;
    totalShots         += m.shotsTot;
    totalExpectedG     += m.expectedG;

    for (int i = 0; i < m.scorers.size(); ++i) //PATRZ DOKLADNIE m.scorers - odnosisz sie do pola QStringList scorers w Match Stats - match-specify

    {
        QString name = m.scorers[i];
        bool found = false;

        for (int j = 0; j < m_scorers.size(); ++j) //PATRZ DOKLADNIE QVector<QPair<QString, int>> m_scorers;
        {
            if (m_scorers[j].first == name)        //czyli vector, ktory przechowuje mapowania (strzelec, liczba goli)
            {
                m_scorers[j].second += 1;           //iterujesz po wektorach .first to jest klucz - strzelec
                found = true;                       // .second to wartosc czyli liczba zdobytych goli
                break;
            }
        }

        if (!found)
            m_scorers.append(qMakePair(name, 1));
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
    if (m_matches.isEmpty()) return 0.0;

    double wynik = 0;
    for(int i = 0; i < getMatchesPlayed(); i++)
    {
        double lambda = m_matches[i].expectedG;
        double k = m_matches[i].goalsFor;
        wynik += poissonProb(lambda, k);
    }



    return 100.0 * wynik / m_matches.size();  // w %
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
