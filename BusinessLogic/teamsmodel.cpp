#include "teamsmodel.h"

void TeamsModel::setTeams(QList<Teams> teams) {
    beginResetModel();
    q_teams = teams;
    endResetModel();
}

int TeamsModel::rowCount(const QModelIndex& parent) const {
    return static_cast<int>(q_teams.size());
}

int TeamsModel::columnCount(const QModelIndex& paren) const {
    return 5; // musi być równe ilości zmiennych w klasie Teams
}

QVariant TeamsModel::data(const QModelIndex& index, int role) const {
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Teams& t = q_teams[index.row()];
    switch (index.column()) {
    case 0:
        return t.getName();
        break;
    case 1:
        return t.getPoints();
        break;
    case 2:
        return t.getGoalsFor();
        break;
    case 3:
        return t.getGoalsAgainst();
        break;
    case 4:
        return t.getMatchesPlayed();
        break;

    default:
        return QVariant();
        break;
    }
}
