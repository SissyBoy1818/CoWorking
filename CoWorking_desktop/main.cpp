#include "AuthorizationWindow/LoginWigdet.h"
#include "Network/NetworkManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto *net = new NetworkManager();
    LoginWigdet w(net);

    w.show();
    return a.exec();
}
