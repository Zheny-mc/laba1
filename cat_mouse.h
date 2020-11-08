#include <iostream>
#include "List.cpp"

#define STOP 's'          // символ остановки ввода мышек
#define MAX_BUFFER 32767
#define WHITE '0'
#define GREY  '1'


using std::cout;
using std::cin;
using std::endl;

//ввод цвета мыши
int  input_color_mouse(); 
//создание живых мышек
List<bool> create_live_mice(); 
//поиск индекса первой мыши
void set_first_mouse(List<bool>& live_mice); 
//кот есть всех мышей
List<bool> eat_mouse(List<bool>& live_mice); 

