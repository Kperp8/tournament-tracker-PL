#include "teams.h"
#include <QDebug>

Teams::Teams(const QString& name) : m_name(name) {}

QString Teams::getName() const {
    return m_name;
}

void Teams::addMatch(int gf, int ga)
{
    m_goalsFor      += gf;
    m_goalsAgainst  += ga;
    ++m_matchesPlayed;

    if (gf > ga)      m_points += 3;
    else if (gf == ga) m_points += 1;
}

void Teams::addMatch(const MatchStats& m)
{
    m_matches.append(m);
    addMatch(m.goalsFor, m.goalsAg);
}

const QVector<MatchStats>& Teams::matches() const { return m_matches; }

int Teams::getPoints() const {
    return m_points;
}

int Teams::getGoalsFor() const {
    return m_goalsFor;
}

int Teams::getGoalsAgainst() const {
    return m_goalsAgainst;
}

int Teams::getMatchesPlayed() const {
    return m_matchesPlayed;
}

void Teams::displayData() const
{
    qDebug() << ">> Drużyna:" << m_name
             << ">> Punkty:" << m_points
             << ">> Gole zdobyte:" << m_goalsFor
             << ">> Gole stracone:" << m_goalsAgainst
             << ">> Mecze:" << m_matchesPlayed;
}

void Teams::setPoints(int p) { m_points = p; }
void Teams::setGoalsFor(int g) { m_goalsFor = g; }
void Teams::setGoalsAgainst(int g) { m_goalsAgainst = g; }
void Teams::setMatchesPlayed(int m) { m_matchesPlayed = m; }
void Teams::setName(const QString & name) {this->m_name = name;};


bool Teams::operator==(const Teams& other) const
{
    return m_name == other.m_name;
}
bool Teams::operator<(const Teams& other) const
{
    return m_points < other.m_points;
}
