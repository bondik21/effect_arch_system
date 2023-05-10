#include <iostream>
#include <string>
#include <vector>

using namespace std;

//інтерфейс для будівельників запитів
class QueryBuilder {
public:
    virtual void select(string columns) = 0;
    virtual void where(string condition) = 0;
    virtual void limit(int limit) = 0;
    virtual string getSQL() = 0;
};

//клас для будівельника запитів СУБД PostgreSQL
class PostgresQueryBuilder : public QueryBuilder {
private:
    string query;

public:
    void select(string columns) override {
        query += "SELECT " + columns + " ";
    }

    void where(string condition) override {
        query += "WHERE " + condition + " ";
    }

    void limit(int limit) override {
        query += "LIMIT " + to_string(limit) + " ";
    }

    string getSQL() override {
        return query;
    }
};

//клас для будівельника запитів СУБД MySQL
class MysqlQueryBuilder : public QueryBuilder {
private:
    string query;

public:
    void select(string columns) override {
        query += "SELECT " + columns + " ";
    }

    void where(string condition) override {
        query += "WHERE " + condition + " ";
    }

    void limit(int limit) override {
        query += "LIMIT " + to_string(limit) + " ";
    }

    string getSQL() override {
        return query;
    }
};

//клас який використовує будівельників запитів для різних СУБД
class QueryDirector {
private:
    QueryBuilder* builder;

public:
    void setBuilder(QueryBuilder* newBuilder) {
        builder = newBuilder;
    }

    string buildQuery(string columns, string condition, int limit) {
        builder->select(columns);
        builder->where(condition);
        builder->limit(limit);
        return builder->getSQL();
    }
};

//клієнтський код з використанням звернення до обох СУБД
int main() {
    QueryDirector director;
    PostgresQueryBuilder pgBuilder;
    MysqlQueryBuilder mysqlBuilder;

    //створення запиту для PostgreSQL
    director.setBuilder(&pgBuilder);
    string pgQuery = director.buildQuery("id, name", "count > 30", 10);
    cout << "Запит PostgreSQL: " << pgQuery << endl;

    //створення запиту для MySQL
    director.setBuilder(&mysqlBuilder);
    string mysqlQuery = director.buildQuery("id, name", "count > 40", 10);
    cout << "Запит MySQL: " << mysqlQuery << endl;

    return 0;
}