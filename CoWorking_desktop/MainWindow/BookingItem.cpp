#include "BookingItem.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

BookingItem::BookingItem(QWidget *parent)
    : QWidget{parent}
{
    auto *mainLayout = new QVBoxLayout(this);
    auto *label = new QLabel("Cabinet");
    auto *layout = new QGridLayout();

    mainLayout->addWidget(label, 1);
    mainLayout->addLayout(layout, 10);

    for (int i = 8; i < 23; ++i) {
        auto *btn = new QPushButton(QString("%1:00").arg(QString::number(i), 2, u'0'));
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        btn->setFixedHeight(30);
        btn->setCheckable(true);
        layout->addWidget(btn, (i-8)/5, (i-8)%5);

        connect(btn, &QPushButton::clicked, this, &BookingItem::timeButtoonClicked);
    }


}

QString BookingItem::name() const
{
    return m_name;
}

QVector<quint8> BookingItem::hours() const
{
    return m_choosenTime;
}

void BookingItem::updateHours(QVector<quint8> avalibleHours)
{
    for (int i = 0; i < m_buttons.size(); ++i) {
        auto *btn = m_buttons.at(i);
        int time = btn->text().left(2).toInt();
        if (!std::find(avalibleHours.begin(), avalibleHours.end(), time)) {
            btn->setChecked(false);
            btn->setEnabled(false);
            btn->setFlat(true);
        }
    }
}

void BookingItem::timeButtoonClicked()
{
    auto *btn = (QPushButton*)sender();
    int time = btn->text().left(2).toInt();
    if (btn->isChecked()) {
        m_choosenTime.push_back(time);
    } else {
        m_choosenTime.erase(std::find(m_choosenTime.begin(), m_choosenTime.end(), time));
    }
    qDebug() << m_choosenTime;
}
