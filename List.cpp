#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

//циклический список
template<typename LT>
class List
{
private:
    //ячейка
    template<typename NT>
    class Node
    {
    public:
        NT data; //данные
        Node* next; //указатель на следующий элемент
        Node(NT _data=NT(), Node* _next=NULL) : data(_data), next(_next) {}
        ~Node(){}
    };

    Node<LT>* head;             //указатель на говолу
    Node<LT>* end;              //указатель на конец
    int index_elem;             //индекс текущего элемента обхода
    int SIZE;                   //размер списка

public:
    List() : head(NULL), end(NULL), index_elem(0), SIZE(0) {} //контруктор перемещения
    List(List<LT>& obj);

    ~List();

    void push_back(const LT& _data); //добавление элементов в конец списка
    void print(); //вывд списка
    
    //----------------------------------------
    void set_first_elem_crawl(int index); //установка 1 элемнта обхода
    LT&  get_elem();                      //получение доступа к элемнту обхода
    void pop_elem();                      //удаление элемнта обхода

    LT& operator[](const int index); //доступ к элементу
    List<LT>& operator=(List<LT>&& r_obj); //перемещение
    //-------------------------------------------------
    bool empty() { return (SIZE == 0)? true : false; }
    int  size()  { return SIZE; }                      
};

template<typename LT>
List<LT>::List(List<LT>& obj) : head(obj.head), index_elem(obj.index_elem), end(obj.end), SIZE(obj.SIZE) {}

template<typename LT>
List<LT>::~List()
/*Удаляем список*/
{
    if (head != NULL)
    {
        Node<LT>* tmp;

        for (int i = 0; i < SIZE-1; i++)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }

        head->next = NULL;
        delete head;
    }
}

template<typename LT>
void List<LT>::push_back(const LT& _data)
/*Добавление в конец списка*/
{
    //если элемнтов нет
    if (SIZE == 0)
    {
        head = new Node<LT>(); //создаем елемент
        head->data = _data;    //заполняем
        end = head;            //присваем новый хвост
    }
    else
    {
        Node<LT>* tmp = new Node<LT>(); //создаем елемент
        tmp->data = _data;              //заполняем
        end->next = tmp;                //говорим что n-ый элемент указывает на наш новый элемент
        end = tmp;                      //присваем новый хвост
        end->next = head;               //зацикливаем список
    }

    SIZE++; //увеливаем количтво элементов
}

template<typename LT>
void List<LT>::print()
/*выводим список*/
{
    Node<LT>* tmp = head; //создаем временнный объект для обхода

    //пока не конец списка выводи элемнты
    for (int i = 0; i < SIZE; i++)
    {
        cout << tmp->data << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}


template<typename LT>
void List<LT>::set_first_elem_crawl(int index)
{
    //если индекс в порядке
    if (index >= 0 || index < SIZE)
    {
        //создаю временный указатель на элемент для обхода списка
        Node<LT>* tmp = head;

        int count = 0; //счетчик
        while (count < index) //пока не найден нужный элемент
        {
            tmp = tmp->next; // переходи на следующий элемент
            count++;
        }

        index_elem = index; //запоминаем индекс текущего элемента
        return;
    }

    //ошибка индексирования
    throw std::invalid_argument("index error");
}

template<typename LT>
LT&  List<LT>::get_elem()
{
    //создаю временный указатель на элемент для обхода списка
    Node<LT>* tmp = head;

    int count = 0; //счетчик
    while (count < index_elem) //пока не найден нужный элемент
    {
        tmp = tmp->next; // переходи на следующий элемент
        count++;
    }

    return tmp->data; //возвращаю найденный данные
}

template<typename LT>
void List<LT>::pop_elem()
/* Удаление index элемента */
{
    // если по этому номеру что-то лежит и этот элемент внутри списка
    Node<LT> *tmp     = head; 
    Node<LT> *helping = head;

    for (int i = 0; i < index_elem; i++)
    {
        helping = tmp; // предыдущее значение temp
        tmp = tmp->next;
    }

    if (tmp == head) // если элемент который надо удалить первый
    {
        head = tmp->next;
        end->next = head;
    }
    else if (tmp == end)
    {
        helping->next = head;
        end = helping;
    }
    else
    {
        helping->next = tmp->next;
    }

    delete(tmp);

    SIZE--; // уменьшаем размер списка
}

template<typename LT>
LT& List<LT>::operator[](const int index)
{
    //если индекс в порядке
    if (index >= 0 || index < SIZE)
    {
        //создаю временный указатель на элемент для обхода списка
        Node<LT>* tmp = head;

        int count = 0; //счетчик
        while (count < index) //пока не найден нужный элемент
        {
            tmp = tmp->next; // переходи на следующий элемент
            count++;
        }

        return tmp->data; //возвращаю найденный данные
    }

    //ошибка индексирования
    throw std::invalid_argument("index error");
}

template<typename LT>
List<LT>& List<LT>::operator=(List<LT>&& r_obj)
{    
    if (&r_obj == this)
        return *this;

    //очистка списка
    if (head != NULL)
    {
        Node<LT>* tmp;

        for (int i = 0; i < SIZE-1; i++)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }

        head->next = NULL;
        delete head;
    }

    head = r_obj.head; 
    end =  r_obj.end; 
    SIZE = r_obj.SIZE;
    index_elem = r_obj.index_elem;

    //отнимаем
    r_obj.head = NULL; 
    r_obj.end = NULL; 
    r_obj.SIZE = 0;
    r_obj.index_elem = 0;

    return *this;
}
