#ifndef BOOKINGITEM_H
#define BOOKINGITEM_H

#include <QListWidgetItem>

class QPushButton;

class BookingItem : public QWidget
{
    Q_OBJECT
public:
    explicit BookingItem(QWidget *parent = nullptr);

    QString name() const;
    QVector<quint8> hours() const;

    void updateHours(QVector<quint8> avalibleHours);

private:
    QString m_name;
    QVector<quint8> m_choosenTime;

    QVector<QPushButton*> m_buttons;

private slots:
    void timeButtoonClicked();

};

#endif // BOOKINGITEM_H
