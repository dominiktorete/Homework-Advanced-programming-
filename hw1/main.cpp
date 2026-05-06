#include <iostream>
using namespace std;

struct point {
    double m_x;
    double m_y;
    point(double x, double y) : m_x(x), m_y(y) {
        //m_x = x;
       // m_y = y; //здесь нужно было добавить написать m_y = y  вместо y = y , синтаксически верно так и так, но семантически будет верен первый вариант
    }
};//здесь нужно было добавть точку с запятой, синатксически классы, структуры, перечисления и объединения должны заканчиваться на точку с запятой

void print_point(const point& point_object);
/*здесь было объявление с определением как после функции main, из за этого возникала ошибка,
  поскольку компилятор не знал какую из 2-х функций ему вызвать (ambiguous), поэтому оставили только объявление,
  а определение оставили после фукнции main
*/

/* {
   std::cout << "x:" << point_object.m_x << ", y: "
             << point_object.m_y << std::endl;
}*/

int main()// нужно было вместо Main указать main.
{
   // int i;  данную переменную можно оставить а можно объявить ее в цикле for.
    for (int i = 0; i < 5; i++) { //было for (i = 0; i < 5; i++);, здесь нужно было убрать точку с запятой, цикл не выпонял пустые операции
        point my_point(i, 2 * i); // здесь по сути должны быть значения типа double, но ничего страшного.
        print_point(my_point);
    }
    return 0;
}

void print_point(const point& point_object) {
    std::cout << "x:" << point_object.m_x << ", y: "
              << point_object.m_y << std::endl;
}