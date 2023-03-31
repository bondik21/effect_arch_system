#include <iostream>
#include <string>
#include <vector>
using namespace std;

// клас патерну стратегія
class deliverystrategy {
public:
	//метод який буде приймати загальну вартість доставки, у подальшому він буде використовуватися і в інших класах доставок
    virtual double calculateDeliveryCost(double orderAmount) = 0;
};

// клас Самовивіз
class pickup : public deliverystrategy {
public:
    virtual double calculateDeliveryCost(double orderAmount) {
		
		//у цьому класі ми повертаємо 0 через те, що самовивіз являється безкоштовним
        return 0.0;
    }
};

// клас Доставки зовнішньою службою доставки
class external_del : public deliverystrategy {
public:
    virtual double calculateDeliveryCost(double orderAmount) {
		
		//тут вже робиться націнка на доставку, наприклад 0.1 від загальної суми замовлення
        return orderAmount * 0.1;
    }
};

// клас Доставки власною службою доставки
class own_del : public deliverystrategy {
public:
    virtual double calculateDeliveryCost(double orderAmount) {
		
		//тут такие самий метод, загальна вартість плюс відсоток від вартості замовлення
        return orderAmount * 0.05 + 5.0;
    }
};

// інформація про замовлення
class Order {
public:
    Order(double amount, deliverystrategy* strategy)
        : m_orderAmount(amount), m_deliveryStrategy(strategy) {}

	//цей метод обчислює загальну суму доставки від обраного метода доставки, тобто сума замовлення плюс доставка
    double calculateTotalCost() {
        double deliveryCost = m_deliveryStrategy->calculateDeliveryCost(m_orderAmount);
        return m_orderAmount + deliveryCost;
    }

private:
    double m_orderAmount;
    deliverystrategy* m_deliveryStrategy;
};

int main() {
	
    // замовлення з власною службою доставки
    Order order(550.0, new own_del());
    cout << "Вартість доставки становить: грн" << order.calculateTotalCost() << endl;

    // замовлення з зовнішньою службою доставки
    Order order2(1200.0, new external_del());
    cout << "Вартість доставки становить: грн" << order2.calculateTotalCost() << endl;

    // замовлення самовивозом
    Order order3(230.0, new pickup());
    cout << "Вартість доставки становить: грн" << order3.calculateTotalCost() << endl;

    return 0;
}