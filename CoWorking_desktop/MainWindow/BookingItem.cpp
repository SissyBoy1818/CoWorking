#include "BookingItem.h"

BookingItem::BookingItem(QListWidget *parent)
    : QListWidgetItem{parent}
{
    setText("TEXT");
}
