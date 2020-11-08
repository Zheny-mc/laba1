#include "cat_mouse.h"

int input_color_mouse()
//ввод цвета мыши
{
    char color;

    //ввод данных
    cout << "Input color mouse(0 - white, 1 - grey): ";
    cin >> color;

    //если есть ошибки при вводе
    if ((color != GREY && color != WHITE && color != STOP) || cin.peek() != '\n')
    {
        //выводи ошибку
        throw std::invalid_argument("Аn error occurred when entering the mouse color");
    }
    
    //верни правильное значение
    return color;
}

List<bool> create_live_mice()
//создание живых мышек
{
    List<bool> live_mice;
    char color;

    //пока нет ошибок или конца
    while (true)
    {
        //ввод цвета мыши
        color = input_color_mouse();
        
        //если конец ввода мышек
        if (color == int(STOP))
            break;
        
        //добавление в список
        live_mice.push_back( bool(color - '0') );
    }

    return live_mice;
}

void set_first_mouse(List<bool>& live_mice) 
//поиск индекса первой мыши
{
    for (int i = 0; i < live_mice.size(); i++)
    {
        if (live_mice[i] == bool(GREY-'0'))
        {
            //определение первой мышки
            live_mice.set_first_elem_crawl(i);
            return;
        }
    }
    //серой мыши не обнаружено
    throw std::invalid_argument("List empty!");
}

List<bool> eat_mouse(List<bool>& live_mice) 
//кот есть всех мышей
{
    List<bool> dead_mice;

    //кот ходит по кругу
    while (!live_mice.empty())
    {
        //добавляю очередную мышь в список съеденных
        dead_mice.push_back(live_mice.get_elem());
        live_mice.pop_elem();
    }

    return dead_mice;
}