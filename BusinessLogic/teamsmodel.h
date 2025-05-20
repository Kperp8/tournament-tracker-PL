#ifndef TEAMSMODEL_H
#define TEAMSMODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "teams.h"

class BUSINESSLOGIC_EXPORT TeamsModel : public QAbstractTableModel
{
    Q_OBJECT
    QList<Teams> q_teams;

public:
    TeamsModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setTeams(QList<Teams> teams); // przekazuje listę obiektów drużyn do obiektu tej klasy
    int rowCount(const QModelIndex& parent = QModelIndex()) const override; // potrzebujemy dla QAbstractTable
    int columnCount(const QModelIndex& parent = QModelIndex()) const override; // jak powyżej
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override; // przekazuje dane do tabeli
};

#endif // TEAMSMODEL_H
