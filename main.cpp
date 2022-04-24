#include <iostream>
#include <exception>

#define FIELD 10

using namespace std;

/* task 001 */
template <typename T1, typename T2>
double division(T1 a, T2 b) try {
    if (b == 0)
        throw std::runtime_error("DivisionByZero");
    return ((double) a / (double) b) ;
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
    throw std::runtime_error(dynamic_cast<std::runtime_error &>(e));
}


/* task 002 */
class Ex {
public:
    double x;
    Ex(double _x) : x(_x) {
    };
    double_t what() const noexcept {
        return x;
    };
    virtual ~Ex() = default;
};

class Bar {
protected:
    double y;
    double a;
public:
    Bar() : y(0){
    };
void setA(double _a) {
    if ((y + a) <= 100) {
        a = _a;
    } else {
        throw Ex(a * y);
    }
}
virtual ~Bar() = default;
};


/* task 003 CLASS */
struct Position
{
    int8_t x, y;
};

enum class Direction
{
    RIGHT, LEFT, DOWN, UP
};

class OffTheField : public std::exception
{
protected:
    std::string descError;
public:
    OffTheField(Position pos, Direction dir)
    {
        descError = "The current position of the robot (";
        descError += std::to_string(pos.x);
        descError += ", ";
        descError += std::to_string(pos.y);
        descError += ") direction of travel: ";
        switch (dir)
        {
            case Direction::RIGHT:
                descError += "right";
                break;
            case Direction::LEFT:
                descError += "left";
                break;
            case Direction::DOWN:
                descError += "down";
                break;
            case Direction::UP:
                descError += "up";
                break;
            default:
                descError += "wrong direction";
                break;
        }
    };
    const char* what() const noexcept {
        return descError.c_str();
    };
};

class IllegalCommand : public std::exception
{
public:
    IllegalCommand() = default;
};

class Robot
{
protected:
    Position currentPosition;
public:
    Robot() : currentPosition{0, 0} {
    };
    Robot(Position _currentPosition) : currentPosition{_currentPosition} {
    };
    void move(Direction dir);
    void print();
};


/* task 003 FUNCTION */
void Robot::move(Direction dir)
{
    switch (dir)
    {
        case Direction::RIGHT:
            if (++currentPosition.x >= FIELD)
            {
                --currentPosition.x;
                throw OffTheField(currentPosition, dir);
            }
            break;
        case Direction::LEFT:
            if (--currentPosition.x < 0)
            {
                ++currentPosition.x;
                throw OffTheField(currentPosition, dir);
            }
            break;
        case Direction::DOWN:
            if (++currentPosition.y >= FIELD)
            {
                --currentPosition.y;
                throw OffTheField(currentPosition, dir);
            }
            break;
        case Direction::UP:
            if (--currentPosition.y < 0)
            {
                ++currentPosition.y;
                throw OffTheField(currentPosition, dir);
            }
            break;
        default: throw IllegalCommand();
    }
}

void Robot::print()
{
    for (size_t i = 0; i < FIELD; i++)
    {
        for (size_t j = 0; j < FIELD; j++)
        {
            if (j == currentPosition.x && i == currentPosition.y) std::cout << "-R-";
            else std::cout << "_-_";
        }
        std::cout << std::endl;
    }
}



int main(int argc, const char** argv) {
    /* execution time control */
    double start_time =  clock();

    std::cout << "Lesson 008" << std::endl;
    std::cout << "Task 1" << std::endl;
    std::cout << division(1.1,2) << std::endl;
    std::cout << "\n";

/*    std::cout << "Task 2" << std::endl;
    Bar b1;
    double x;
    do {
        std::cout << "enter a number from 1 to 100: "<< std::endl;
        try
        {
            b1.setA(x);
        }
        catch(Ex &err)
        {
            std::cerr<<"Exception: a * y = "<<err.x<<std::endl;
        }
    } while(std::cin>>x && x!=0);
*/

    std::cout << "Task 3" << std::endl;
    Robot r1 (Position {0, 0});
    r1.move(Direction::RIGHT);
    r1.move(Direction::DOWN);
    r1.print();
    r1.move(Direction::LEFT);
    r1.move(Direction::LEFT);
    r1.print();
    std::cout << "\n";

    /* execution time control */
    double end_time = clock();
    double search_time = (end_time - start_time)/1000;
    std::cout << "Program execution time = " << search_time << " sec"<< std::endl;
    return 0;
}


/*
 1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров
 и запускать исключение DivisionByZero, если второй параметр равен 0. В функции main выводить
 результат вызова функции div в консоль, а также ловить исключения.

2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу,
 инициализирующий x значением параметра. Написать класс Bar, хранящий вещественное число y
 (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным
 параметром a. Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится
 значение a. В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры
 целое n. Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0.
 В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.

3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод,
 означающий задание переместиться на соседнюю позицию. Эти методы должны запускать классы-исключения
 OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда
 (направление не находится в нужном диапазоне). Объект исключения должен содержать всю необходимую
 информацию — текущую позицию и направление движения. Написать функцию main, пользующуюся этим классом
 и перехватывающую все исключения от его методов, а также выводящую подробную информацию о всех
 возникающих ошибках.
 */
