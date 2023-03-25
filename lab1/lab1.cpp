#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Створення базового інтерфейсу інетатора
template<typename T>
class Iterator {
public:
    virtual T next() = 0;
    virtual bool hasNext() const = 0;
};

//Цей клас зберігає туристичні місця
class TouristAttraction {
public:
    TouristAttraction(std::string name, string location, int rating) :
        m_name(name), m_location(location), m_rating(rating) {}

    string getName() const { return m_name; }
    string getLocation() const { return m_location; }
    int getRating() const { return m_rating; }

private:
    string m_name;
    string m_location;
    int m_rating;
};

//Цей клас реалізує сам ітератор і відпопідає за збереження туристичних місць
class TouristAttractionCollection {
public:

    //Ініціалізація туристичних місць
    TouristAttractionCollection() {
        m_attractions.push_back(TouristAttraction("Площа Свободи", "Харків", 4));
        m_attractions.push_back(TouristAttraction("Софійський собор", "Київ", 5));
        m_attractions.push_back(TouristAttraction("Ейфелева вежа", "Харків", 4));
        m_attractions.push_back(TouristAttraction("Києво-Печерська лавра", "Київ", 5));
    }

    //Цей метод повертає ітератор для отримання списку туристичних місць за сценаріями описаними нижче
    Iterator<TouristAttraction>* getIterator(string scenario) {
        if (scenario == "Туристичний маршрут на власний розсуд") {
            return new TouristAttractionIterator(m_attractions);
        }
        else if (scenario == "Рекомендації навігатора") {
            return new NavigatorIterator(m_attractions);
        }
        else if (scenario == "Екскурсія з місцевим гідом") {
            return new
		}
	}
	return 0;
}