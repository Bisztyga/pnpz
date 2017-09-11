#ifndef EVENTS_H
#define EVENTS_H

#include <QDialog>

namespace Ui {
class Events;
}

class Events : public QDialog
{
    Q_OBJECT

public:
    explicit Events(QWidget *parent = 0);
    ~Events();

private:
    Ui::Events *ui;
};

#endif // EVENTS_H
