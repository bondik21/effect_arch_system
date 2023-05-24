#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Component {
public:
    virtual string render() const = 0;
};

//компонент - поле вводу
class InputComponent : public Component {
private:
    string name;
public:
    InputComponent(const string& name) : name(name) {}

    string render() const override {
        return "<input type='text' name='" + name + "' />";
    }
};

//компонент - вибір зі списку
class SelectComponent : public Component {
private:
    string name;
    vector<string> options;
public:
    SelectComponent(const string& name, const vector<string>& options)
        : name(name), options(options) {}

    string render() const override {
        string result = "<select name='" + name + "'>";
        for (const string& option : options) {
            result += "<option value='" + option + "'>" + option + "</option>";
        }
        result += "</select>";
        return result;
    }
};

//компанувальник складає компоненти в одну форму
class FormComposer {
private:
    vector<Component*> components;
public:
    void addComponent(Component* component) {
        components.push_back(component);
    }

    string composeForm() const {
        string result = "<form>";
        for (Component* component : components) {
            result += component->render();
        }
        result += "</form>";
        return result;
    }
};

int main() {
    //компоненти форми
    InputComponent input1("Логін");
    InputComponent input2("Пароль");
    SelectComponent select("Код", { "111", "222", "333" });

    //компанувальник
    FormComposer composer;
    composer.addComponent(&input1);
    composer.addComponent(&input2);
    composer.addComponent(&select);

    //виводимо HTML-форму
    string form = composer.composeForm();
    cout << form << endl;

    return 0;
}