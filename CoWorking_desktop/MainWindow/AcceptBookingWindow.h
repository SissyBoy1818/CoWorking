#ifndef ACCEPTBOOKINGWINDOW_H
#define ACCEPTBOOKINGWINDOW_H

#include <QDialog>

class QDialogButtonBox;
class QLabel;

class AcceptBookingWindow : public QDialog
{
    Q_OBJECT
public:
    AcceptBookingWindow(const QString &cabinet, const QString &date, quint8 hours);

private:
    QDialogButtonBox *m_buttons;

    QLabel *m_label;
};

#endif // ACCEPTBOOKINGWINDOW_H
