#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Employee;

class Visitor {
public:
    virtual void visit(Employee& employee) = 0;
};

//дозволяє об'єкту типу Visitor відвідати об'єкт, який його реалізує
class Visitable {
public:
    virtual void accept(Visitor& visitor) = 0;
};

//містить інформацію про посаду та зарплату працівника
class Employee : public Visitable {
public:
    Employee(const string& position, int salary) : position_(position), salary_(salary) {}

    const string& getPosition() const {
        return position_;
    }

    int getSalary() const {
        return salary_;
    }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    string position_;
    int salary_;
};

//відділ який містить ім'я та список співробітників
class Department : public Visitable {
public:
    Department(const string& name, const vector<Employee>& employees) : name_(name), employees_(employees) {}

    const string& getName() const {
        return name_;
    }

    const vector<Employee>& getEmployees() const {
        return employees_;
    }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    string name_;
    vector<Employee> employees_;
};

//компанія яка містить ім'я та список відділів
class Company : public Visitable {
public:
    Company(const string& name, const vector<Department>& departments) : name_(name), departments_(departments) {}

    const string& getName() const {
        return name_;
    }

    const vector<Department>& getDepartments() const {
        return departments_;
    }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

private:
    string name_;
    vector<Department> departments_;
};

//конкретний відвідувач, який відвідує об'єкти типу Employee, Department та Company
class SalaryReportVisitor : public Visitor {
public:
    void visit(Employee& employee) override {
        cout << "Посада: " << employee.getPosition() << ", Зарплата: " << employee.getSalary() << endl;
    }

    void visit(Department& department) override {
        cout << "Відділ: " << department.getName() << endl;
        const auto& employees = department.getEmployees();
        for (const auto& employee : employees) {
            employee.accept(*this);
        }
    }

    void visit(Company& company) override {
        cout << "Компанія: " << company.getName() << endl;
        const auto& departments = company.getDepartments();
        for (const auto& department : departments) {
            department.accept(*this);
        }
    }
};

int main() {
    Employee employee1("Software Інженер", 5000);
    Employee employee2("Проджект менеджер", 7000);
    Employee employee3("Sales Manager", 6000);
    Department department1("Інженерія", { employee1, employee2 });
    Department department2("Продаж", { employee3 });
    Company company("IT Comp", { department1, department2 });

    SalaryReportVisitor salary_report;
	department1.accept(salary_report);
    cout << "Звіт про зарплату компанії:" << endl;
    company.accept(salary_report);

    cout << endl;
    cout << "Звіт про зарплату для інженерного відділу:" << endl;
    department1.accept(salary_report);

    return 0;
}