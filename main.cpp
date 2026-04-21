#include <QCoreApplication>
#include <QDebug>
#include <vector>

#include "account.h"
#include "client.h"
#include "admin.h"
#include "Product.h"
#include "Order.h"
#include "services.h"

void testare() {
    qDebug() << "======= START TESTARE SISTEM SIVG-MB =======\n";
    
    Product* p1 = new Product(1, "Bormasina Bosch", 450.0, false);
    Product* p2 = new Product(2, "Montaj Rafturi", 100.0, true);

    client* c1 = new client(101, "vlad.constructor@yahoo.com", "hash_parola", false, 12);

    Order* comandaClient = new Order(5001, c1->returnID(), "Curier", "Ramburs", "Noua");
    comandaClient->addProduct(p1);
    comandaClient->addProduct(p2);

    OrderService oService;
    UserService uService;

    double pretBrut = p1->returnPrice() + p2->returnPrice();
    double pretDupaReducere = oService.calculateDiscount(c1, pretBrut);

    qDebug() << "[TEST FIDELIZARE]";
    qDebug() << "Client:" << c1->returnmail();
    qDebug() << "Comenzi anterioare:" << c1->returnOrder();
    qDebug() << "Pret Total Brut:" << pretBrut << "RON";
    qDebug() << "Pret dupa reducere (10%):" << pretDupaReducere << "RON\n";

    qDebug() << "[TEST RESTRICTIE PLATA]";
    c1->toggleProb();
    qDebug() << "Status client schimbat in PROBLEMATIC:" << c1->returnProb();

    if (!oService.placeOrder(c1, *comandaClient)) {
        qDebug() << "Rezultat: Corect! Comanda RAMBURS a fost respinsa pentru clientul problematic.";
    }
    qDebug() << "\n======= FINALIZARE TESTE =======";

    delete p1;
    delete p2;
    delete c1;
    delete comandaClient;
}

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    testare();
    return 0;
}