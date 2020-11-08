/*
*Задача:
    N серых и M белых мышей сидят по кругу. Кошка ходит по кругу по часовой
    стрелке и съедает каждую S -тую мышку. В первый раз счет начинается с
    серой мышки. Составить алгоритм определяющий порядок в котором сидели
    мышки, если через некоторое время осталось K серых и L белых мышей.

*Автор: Бубнов Евгений 19-ивт-2
*/
#include "cat_mouse.h"

int main()
{

    List<bool> live_mice; 
    List<bool> dead_mice; 

    try
    {
        //создание списка живых мышек
        live_mice = create_live_mice();

        //вывод результата создания списка
        cout << "Live mice: ";
        live_mice.print();

        //поиск первой мышки
        set_first_mouse(live_mice);

        //кот обедает
        dead_mice = eat_mouse(live_mice);
        
        //результат обеда
        cout << "Dead mice: ";
        dead_mice.print();
    }
    catch(const std::exception& e)
    {
        //в случае ошибки
        cout << e.what() << endl;
    }

    return 0;
}
