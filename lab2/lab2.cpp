#include <iostream>
#include <string>
#include <vector>
using namespace std;

//інтерфейс патерну посередник
class Mediator {
public:
    virtual void notify(Component* sender, string event) = 0;
};

//Клас компонент який потрібен для забезпечення можливості взаємодії між компонентами форми та медіатором, та для загальної взаємодії з інтерфейсом
class Component {
public:
    Component(Mediator* mediator) : mediator_(mediator) {}

    virtual void setEnabled(bool enabled) {
        enabled_ = enabled;
        if (enabled_) {
            cout << "Компонент доступен" << endl;
        } else {
            cout << "Компонент не доступен" << endl;
        }
    }

    virtual void fireEvent(string event) {
        mediator_->notify(this, event);
    }

protected:
    Mediator* mediator_;
    bool enabled_ = true;
};

//Віртуальна кнопка
class Button : public Component {
public:
    Button(Mediator* mediator) : Component(mediator) {}

    void click() {
        if (enabled_) {
            cout << "Підтвердити" << std::endl;
            fireEvent("click");
        }
    }
};

//Клас для поля у якому вводиться текст
class TextField : public Component {
public:
    TextField(Mediator* mediator) : Component(mediator) {}

    void setText(string text) {
        if (enabled_) {
            text_ = text;
            cout << "Текст: " << text_ << endl;
            fireEvent("textChanged");
        }
    }

private:
    string text_;
};

//Чекбокс
class CheckBox : public Component {
public:
    CheckBox(Mediator* mediator) : Component(mediator) {}

    void setChecked(bool checked) {
        if (enabled_) {
            checked_ = checked;
            cout << "Checkbox checked: " << checked_ << endl;
            fireEvent("checkedChanged");
        }
    }

private:
    bool checked_ = false;
};

// Клас, який буде виконувати роль посередника, за допомогою нього користувач може взаємодіяти між компонентами описаними у цьому класі нижче
class OrderFormMediator : public Mediator {
public:

	//час доставки
    void setDeliveryDate(string date) {
        deliveryDate_ = date;
        updateDeliveryTime();
    }

	//отримувач
    void setRecipient(bool isOtherPerson) {
        isOtherPerson_ = isOtherPerson;
        updateRecipientFields();
    }

	//забрати самому
    void setSelfPickup(bool selfPickup) {
        selfPickup_ = selfPickup;
        updateDeliveryFields();
    }

	//ім'я отримувача
    void setRecipientName(string name) {
        recipientName_ = name;
        cout << "Ім'я отримувача: " << recipientName_ << endl;
    }

	//номер телефону
    void setRecipientPhone(string phone) {
        recipientPhone_ = phone;
        cout << "Номер телефону: " << recipientPhone_ << endl;
    }


	//Цей метод викликається коли трапляється зміна у полі форми, після чого автоматично в усіх змінених формах викликається метод update
    void notify(Component* sender, string event) {
        if (event == "dateChanged") {
            updateDeliveryTime();
        } else if (event == "checkedChanged") {
            updateRecipientFields();
        } else if (event == "selfPickupChanged") {
            updateDeliveryFields();
        }
    }

private:
    string deliveryDate_;
	vector<string> deliveryTimes_;
	bool isOtherPerson_ = false;
	bool selfPickup_ = false;
	string recipientName_;
	string recipientPhone_;

//метод оновлення часу доставки
void updateDeliveryTime() {
    if (deliveryDate_ == "today") {
        deliveryTimes_ = {"09:30 - 12:00", "14:00 - 16:00", "18:00 - 20:00"};
    } else if (deliveryDate_ == "tomorrow") {
        deliveryTimes_ = {"09:30 - 12:00", "14:00 - 16:00", "18:00 - 20:00"};
    } else {
        deliveryTimes_ = {"09:30 - 12:00", "14:00 - 16:00"};
    }

    cout << "Час доставки оновлено: ";
    for (auto time : deliveryTimes_) {
        cout << time << ", ";
    }
    cout << endl;
}

//метод оновлення отримувача
void updateRecipientFields() {
    if (isOtherPerson_) {
        recipientNameField_->setEnabled(true);
        recipientPhoneField_->setEnabled(true);
    } else {
        recipientNameField_->setEnabled(false);
        recipientPhoneField_->setEnabled(false);
    }
}

//метод оновлення інформації про доставку
void updateDeliveryFields() {
    if (selfPickup_) {
        deliveryDateField_->setEnabled(false);
        deliveryTimeField_->setEnabled(false);
        recipientCheckBox_->setEnabled(false);
        updateRecipientFields();
    } else {
        deliveryDateField_->setEnabled(true);
        deliveryTimeField_->setEnabled(true);
        recipientCheckBox_->setEnabled(true);
    }
}

	TextField* deliveryDateField_;
	TextField* deliveryTimeField_;
	CheckBox* recipientCheckBox_;
	TextField* recipientNameField_;
	TextField* recipientPhoneField_;

int main() {
	OrderFormMediator mediator;
	
	//створення компонентів інтерфейсу
	TextField deliveryDateField(&mediator);
	TextField deliveryTimeField(&mediator);
	CheckBox recipientCheckBox(&mediator);
	TextField recipientNameField(&mediator);
	TextField recipientPhoneField(&mediator);
	Button submitButton(&mediator);

	//передача посилань на компоненти патерну посереднику
	mediator.deliveryDateField_ = &deliveryDateField;
	mediator.deliveryTimeField_ = &deliveryTimeField;
	mediator.recipientCheckBox_ = &recipientCheckBox;
	mediator.recipientNameField_ = &recipientNameField;
	mediator.recipientPhoneField_ = &recipientPhoneField;

	//налаштування обробників подій
	deliveryDateField.setEnabled(true);
	deliveryDateField.setText("today");
	deliveryDateField.fireEvent("dateChanged");

	deliveryTimeField.setEnabled(false);

	recipientCheckBox.setEnabled(true);
	recipientCheckBox.setChecked(false);
	recipientCheckBox.fireEvent("checkedChanged");

	recipientNameField.setEnabled(false);
	recipientPhoneField.setEnabled(false);

	submitButton.setEnabled(true);
	submitButton.click();

return 0;
}