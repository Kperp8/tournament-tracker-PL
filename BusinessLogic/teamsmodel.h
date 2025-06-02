#ifndef TEAMSMODEL_H
#define TEAMSMODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "teams.h"

class BUSINESSLOGIC_EXPORT TeamsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TeamsModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    void setTeams(QList<Teams> teams);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QList<Teams> q_teams;
};

#endif // TEAMSMODEL_H