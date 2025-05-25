#include "file-handling.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>



QVector<Teams> FileOp::loadFromFile(const QString& path) //path przypisujemy w mainwindow.cpp QString path = QFileDialog::getOpenFileName
{
    QVector<Teams> teams;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { //QIODevice::Text czytamy QStrings nie bajty
        qDebug() << "Nie można otworzyć pliku do odczytu:" << path;
        return teams;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();           //https://doc.qt.io/qt-6/qfile.html
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

bool FileOp::saveToFile(const QVector<Teams>& teams, const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Nie można otworzyć pliku do zapisu:" << path;
        return false;
    }

    QTextStream out(&file);
    for (int i = 0; i < teams.size(); i++) {
        out << teams[i].getName() << ","
            << teams[i].getPoints() << ","
            << teams[i].getGoalsFor() << ","
            << teams[i].getGoalsAgainst() << ","
            << teams[i].getMatchesPlayed() << "\n";
    }

    file.close();
    return true;
}

//dla czytania mozesz skopiowac:
/*
FCB,9,12,4,3
MAN CITY,6,8,5,3
MAN UTD,3,4,7,3
RM,0,4,12,3
*/
