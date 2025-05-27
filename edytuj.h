#ifndef EDYTUJ_H
#define EDYTUJ_H

#include <QDialog>

namespace Ui {
class Edytuj;
}

class Edytuj : public QDialog
{
    Q_OBJECT

public:
    explicit Edytuj(const QString & currentName, QWidget *parent = nullptr);
    ~Edytuj();

    QString GetNewName() const;

private:
    Ui::Edytuj *ui;
};

#endif // EDYTUJ_H
