#include <iostream>
#include <string>
#include <vector>
using namespace std;

//абстрактний базовий БД
class Database {
public:
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual vector<string> query(const string& q) = 0;
};

//клас БД PostgreSQL
class PostgresDatabase : public Database {
public:
    void connect() override {
        cout << "Підключення до PostgreSQL database...\n";
    }
    
    void disconnect() override {
        cout << "Відключення від PostgreSQL database...\n";
    }
    
    vector<string> query(const string& q) override {
        cout << "Виконання запиту PostgreSQL: " << q << "\n";
        return {"Result 1", "Result 2", "Result 3"}; //повертаємо тестові дані
    }
};

//клас БД MongoDB
class MongoDB : public Database {
public:
    void connect() override {
        cout << "Підключення до MongoDB database...\n";
    }
    
    void disconnect() override {
        cout << "Відключення від MongoDB database...\n";
    }
    
    vector<string> query(const string& q) override {
        cout << "Виконання запиту MongoDB: " << q << "\n";
        return {"Result 4", "Result 5", "Result 6"}; //повертаємо тестові дані
    }
};

//клас для керування БД
class DatabaseManager {
private:
    vector<Database*> databases; //вектор вказівників на бази даних
    static DatabaseManager* instance; //вказівник на єдиний екземпляр класу

    //приватний конструктор для запобігання створенню інших екземплярів класу, також сюди можна буде додавати нові БД
    DatabaseManager() {
        databases.push_back(new PostgresDatabase());
        databases.push_back(new MongoDB());
    }

public:
    //отримання єдиного екземпляру класу
    static DatabaseManager* getInstance() {
        if (!instance) {
            instance = new DatabaseManager();
        }
        return instance;
    }

    //виконання запиту до всіх баз даних
    void executeQuery(const string& q) {
		for (auto db : databases) {
			db->connect(); //підключення до БД
			auto results = db->query(q); //виконання запиту
			db->disconnect(); //відключення від БД
			//обробка результатів запиту
				for (auto result : results) {
				cout << "Результат: " << result << "\n";
				}
			}
		}
	};

	//ініціалізація вказівника на єдиний екземпляр класу
	DatabaseManager* DatabaseManager::instance = nullptr;

	int main() {
		auto dbManager = DatabaseManager::getInstance(); //отримання єдиного екземпляру класу
		dbManager->executeQuery("SELECT * FROM users"); //виконання запиту до всіх баз даних
		return 0;
	}