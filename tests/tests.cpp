#include "gtest/gtest.h" // Подключаем заголовочный файл Google Test.
                         // Компилятор найдет его благодаря флагу -isystem,
                         // который мы укажем позже.

#include "employee.h"    // Подключаем наш employee.h, чтобы его протестировать.
#include <sstream>       // Нужен для stringstream, чтобы имитировать файл в памяти.

// Тест-кейс для проверки оператора сравнения в структуре employee.
// TEST(ИмяНабораТестов, ИмяТеста)
TEST(EmployeeSuite, OperatorLessThan) {
    // Arrange (Подготовка данных)
    employee emp1 = { 101, "Anna", 160.0 };
    employee emp2 = { 102, "Boris", 150.0 };
    employee emp3 = { 101, "AnnaClone", 170.0 };

    // Act & Assert (Действие и Проверка)
    ASSERT_TRUE(emp1 < emp2);      // Проверяем, что 101 < 102 - это правда.
    ASSERT_FALSE(emp2 < emp1);     // Проверяем, что 102 < 101 - это ложь.
    ASSERT_FALSE(emp1 < emp3);     // Проверяем, что 101 < 101 - это ложь.
}

// Тест-кейс для проверки методов read и write.
TEST(EmployeeSuite, ReadWriteIntegrity) {
    // Arrange
    employee original_emp = { 205, "Victor", 188.5 };
    employee loaded_emp = { 0, "", 0.0 }; // Создаем "пустой" объект для загрузки.
    
    // Используем строковый поток для имитации файла в памяти.
    // Он ведет себя как файл, но работает прямо в RAM.
    stringstream ss(ios::binary | ios::in | ios::out);

    // Act
    original_emp.write(ss); // Записываем в наш "файл в памяти".
    loaded_emp.read(ss);    // Читаем из него в другой объект.

    // Assert
    // Проверяем, что все поля прочитанного объекта совпадают с исходными.
    ASSERT_EQ(original_emp.num, loaded_emp.num);          // EQ для простых типов (int).
    ASSERT_STREQ(original_emp.name, loaded_emp.name);     // STREQ для сравнения C-строк (char[]).
    ASSERT_DOUBLE_EQ(original_emp.hours, loaded_emp.hours); // DOUBLE_EQ для double, учитывает погрешности.
}