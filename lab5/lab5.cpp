#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Entity {
public:
    virtual void get() = 0;
    virtual void validate() = 0;
    virtual string save() = 0;
    virtual void notify_admin() = 0;
    virtual string getName() const = 0;
    virtual pair<int, string> getResponse() const = 0;
    virtual ~Entity() = default;  //віртуальний деструктор
};

class Product : public Entity {
public:
    void validate() override {
        
		//валідація товару
        bool is_valid = true;
        if (!is_valid) {
            notify_admin();
            throw logic_error("Помилка валідації товару.");
        }
    }

    string save() override {
        
		//збереження товару
        return "Товар збережено.";
    }

    void notify_admin() override {
        
		//сповіщення адміністратора
        cout << "Повідомлення адм: Помилка валідації товару." << endl;
    }

    string getName() const override {
        return "Продукт";
    }

    pair<int, string> getResponse() const override {
        return make_pair(200, "Ок");
    }
};

class User : public Entity {
public:
    void validate() override {
		
        //валідація користувача
        bool is_valid = true;
        if (!is_valid) {
            throw logic_error("Помилка валідації користувача.");
        }
    }

    string save() override {
        
		//збереження користувача
        return "Користувача збережено.";
    }

    void notify_admin() override {
        //користувач не може надіслати повідомлення адміністратору у разі невдалої валідації
    }

    string getName() const override {
        return "Користувач";
    }

    pair<int, string> getResponse() const override {
        return make_pair(200, "Ок");
    }
};

class Order : public Entity {
public:
    void validate() override {
        
		//валідація замовлення
        bool is_valid = true;
        if (!is_valid) {
            throw logic_error("Помилка валідації замовлення.");
        }
    }

    string save() override {  //зміна типу повернення на string
        
		//збереження замовлення
        cout << "Замовлення збережено." << endl;
        return "Замовлення збережено.";
    }

    void notify_admin() override {
        //замовлення не потребує сповіщення адміністратора
    }

    void send_response() {
		
        //відправлення відповіді на запит з JSON-поданням замовлення
        cout << "Запит замовлення відправлено." << endl;
    }
};

class EntityUpdater {
protected:
    Entity* entity_;

public:
    explicit EntityUpdater
	} else if (dynamic_cast<User*>(entity)) {
    
	//заборона зміни email користувача
    User* user = dynamic_cast<User*>(entity);

} else if (dynamic_cast<Order*>(entity)) {
    
	//оновлення замовлення
    OrderUpdater order_updater(dynamic_cast<Order*>(entity));
    order_updater.update();
}

cout << endl;
}

//звільнення пам'яті
for (Entity* entity : entities) {
delete entity;
}
entities.clear();

return 0;
}