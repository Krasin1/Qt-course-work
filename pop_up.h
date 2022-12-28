#ifndef POP_UP_H
#define POP_UP_H

#include <QDialog>
#include "radio_components.hpp"

namespace Ui {
class pop_up;
}

class pop_up : public QDialog
{
    Q_OBJECT

public:
    explicit pop_up(QWidget *parent = nullptr);
    explicit pop_up(QWidget *paretn = nullptr, Radio * other = nullptr);
    ~pop_up();

private slots:
    void on_pushButton_clicked();

private:
    Ui::pop_up *ui;
    Radio * single;
};

#endif // POP_UP_H
