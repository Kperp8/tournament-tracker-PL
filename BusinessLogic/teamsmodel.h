#ifndef TEAMSMODEL_H
#define TEAMSMODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "teams.h"

class BUSINESSLOGIC_EXPORT TeamsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TeamsModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setTeams(QList<Teams> teams); // aktualizuje liste obiektow do wyświetlenia, TRZEBA WEZWAĆ PRZY KAŻDEJ ZMIANIE
    int rowCount(const QModelIndex& parent = QModelIndex()) const override; // potrzebujemy dla QAbstractTable
    int columnCount(const QModelIndex& parent = QModelIndex()) const override; // jak powyżej
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override; // przekazuje dane do tabeli
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override; // przekazuje nazwy kolumn

private:
    QList<Teams> q_teams; // lista do wyświetlenia
};

#endif // TEAMSMODEL_H
