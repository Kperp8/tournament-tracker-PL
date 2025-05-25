#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "teams.h"
#include <QVector>
#include <QString>

class BUSINESSLOGIC_EXPORT FileOp
{
public:
    //static bool saveToFile(const QVector<Teams>& teams, const QString& path); narazie zobacze czy dziala load
    static QVector<Teams> loadFromFile(const QString& path);
};


#endif // FILE_HANDLING_H
