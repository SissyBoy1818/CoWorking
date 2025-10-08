#include "AcceptBookingWindow.h"

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>

AcceptBookingWindow::AcceptBookingWindow(const QString &cabinet, const QString &date, quint8 hours)
{
    auto *layout = new QVBoxLayout(this);

    m_label = new QLabel(QString("Забронивать рабочее место %1 на %2 часa(-ов) в %3?")
                             .arg(cabinet, QString::number(hours), date), this);
    m_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                     Qt::Horizontal, this);

    layout->addWidget(m_label);
    layout->addWidget(m_buttons);

    QObject::connect(m_buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(m_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    setWindowTitle("Подтвердите бронь");
    resize(300, 150);
}
