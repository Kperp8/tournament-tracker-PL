#include "file-handling.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

QVector<Teams> FileOp::loadFromFile(const QString &path)
{
    QVector<Teams> teams;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Nie można otworzyć pliku do odczytu:" << path;
        return teams;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() != 5)
            continue;

        QString name = parts[0];
        int points = parts[1].toInt();
        int goalsFor = parts[2].toInt();
        int goalsAgainst = parts[3].toInt();
        int matchesPlayed = parts[4].toInt();

        Teams team(name);
        team.setPoints(points);
        team.setGoalsFor(goalsFor);
        team.setGoalsAgainst(goalsAgainst);
        team.setMatchesPlayed(matchesPlayed);

        teams.append(team);
    }

    file.close();
    return teams;
}

bool FileOp::saveToFile(const QVector<Teams> &teams, const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Nie można otworzyć pliku do zapisu:" << path;
        return false;
    }

    QTextStream out(&file);
    for (int i = 0; i < teams.size(); i++)
    {
        out << teams[i].getName() << ","
            << teams[i].getPoints() << ","
            << teams[i].getGoalsFor() << ","
            << teams[i].getGoalsAgainst() << ","
            << teams[i].getMatchesPlayed() << "\n";
    }

    file.close();
    return true;
}