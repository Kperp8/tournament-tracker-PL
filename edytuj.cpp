#include "edytuj.h"
#include "ui_edytuj.h"

Edytuj::Edytuj(const QString & currentName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Edytuj)
{
    ui->setupUi(this);
}

Edytuj::~Edytuj()
{
    delete ui;
}

QString Edytuj::GetNewName() const
{
    return ui->LineEdit_edytuj->text().trimmed();
}
