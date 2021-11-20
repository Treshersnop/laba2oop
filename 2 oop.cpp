#include <iostream>
using namespace std;

class MyClass1
{ 
public:
    int x, y;
    MyClass1()//конструктор по умолчанию
    {
        printf("MyClass1()\n");
        x = 0;
        y = 0;
    }
    MyClass1(int x, int y)//конструктор со значениями
    {
        printf("MyClass1(int x, int y)\n");
        this->x = x;
        this->y = y;
    }
    MyClass1(const MyClass1&mc)//копирующий
    {
        printf("MyClass1(const MyClass1 &mc)\n");
        x = mc.x;
        y = mc.y;
    }
    ~MyClass1()//деструктор
    {
        printf("%d, %d\n", x, y);
        printf("~MyClass1()\n");
    }
    void move(int dx, int dy)
    {
        printf("move(int dx, int dy): move(int dx, int dy)\n");
        x = x + dx;
        y = y + dy;
        printf("%d, %d\n", x, y);
    }
    virtual void step()
    {
        x++;
        y++;
        printf("%d, %d\nvoid step(): MyClass1\n", x, y);
    }
};

class maxMyClass :public MyClass1
{
protected:
    int N;
public:
    maxMyClass() :MyClass1()
    {
        printf("maxMyClass()\n");
        N = 0;
    }
    maxMyClass(int x, int y, int N) :MyClass1(x, y)
    {
        printf("maxMyClass(int x, int y, int N)\n");
        this->N = N;
    }
    maxMyClass(const maxMyClass& mc)
    {
        printf("maxMyClass(const maxMyClass &mc)\n");
        x = mc.x;
        y = mc.y;
        N = mc.N;
    }
    ~maxMyClass() 
    {
        printf("%d, %d, N = %d\n", x, y, N);
        printf("~maxMyClass()\n");
    }
    void one_step()
    {
        printf("one_step(): maxMyClass\n");
        N++;
        printf("%d, %d, %d\n\n", x, y, N);
    }
    void step()override
    {        
        x = x + 2;
        y = y + 2;
        printf("%d, %d, %d\nvoid step(): maxMyClass\n", x, y, N);
    }
};

class maxMyClass2 :public MyClass1
{
protected:
    int N;
public:
    maxMyClass2() :MyClass1()
    {
        printf("maxMyClass2()\n");
        N = 0;
    }
    maxMyClass2(int x, int y, int N) :MyClass1(x, y)
    {
        printf("maxMyClass2(int x, int y)\n");
        this->N = N;
    }
    maxMyClass2(const maxMyClass2& mc)
    {
        printf("maxMyClass2(const maxMyClass2 &p)\n");
        x = mc.x;
        y = mc.y;
        N = mc.N;
    }
    ~maxMyClass2()
    {
        printf("%d, %d, N = %d\n", x, y, N);
        printf("~maxMyClass2()\n");
    }
};

class no_class :public MyClass1
{
    void step() override
    {
        x = x + 3;
        y = y + 3;
    }
};

class MyClass2
{
private:
    int x, y;
public:
    MyClass2()
    {
        printf("MyClass2()\n");
        x = 0;
        y = 0;
    }
    MyClass2(int x, int y)
    {
        printf("MyClass2(int x, int y)\n");
        this->x = x;
        this->y = y;
    }
    MyClass2(const MyClass2& mc)
    {
        printf("MyClass2(const MyClass2 &p)\n");
        x = mc.x;
        y = mc.y;
    }
    ~MyClass2()
    {
        printf("%d, %d\n", x, y);
        printf("~MyClass2()\n");
    }
    void move(int dx, int dy)
    {
        printf("move(int dx, int dy)\n");
        x = x + dx;
        y = y + dy;
        printf("%d, %d\n", x, y);
    }
    void move_back(int dx, int dy);
};

void MyClass2:: move_back(int dx, int dy)//реализация метода после определения
{
    printf("move_back(int dx, int dy)\n");
    x = x - dx;
    y = y - dy;
    printf("%d, %d\n", x, y);
}

class MyBase
{
private:
    MyClass2* mc1;
    MyClass2* mc2;
public:
    MyBase()
    {
        printf("MyBase()\n");
        mc1 = new MyClass2;
        mc2 = new MyClass2;
    }
    MyBase(int x1, int y1, int x2, int y2)
    {
        printf("MyBase(int x1, int y1, int x2, int y2)\n");
        mc1 = new MyClass2(x1, y1);
        mc2 = new MyClass2(x2, y2);
    }
    MyBase(const MyBase* mb)
    {
        printf("MyBase(const MyBase* mb)\n");
        mc1 = new MyClass2(*(mb->mc1));
        mc2 = new MyClass2(*(mb->mc2));
    }
    ~MyBase()
    {
        printf("~MyBase()\n");
        delete mc1;
        delete mc2;
    }
};

int main()
{
    setlocale(LC_ALL, "RUS");
    {
        printf("Создание статических объектов:\n");
        MyClass1 mc1;//создание статических объектов
        MyClass1 mc2(1, 1);
        MyClass1 mc3(mc2);
        printf("\nУдаление статических объектов:\n");
    }

    printf("\n\n\n\n");

    {
        printf("Создание динамических объектов:\n");
        MyClass1* mc4 = new MyClass1();//создание динамических объектов
        MyClass1* mc5 = new MyClass1(2, 2);
        MyClass1* mc6 = new MyClass1(*mc5);
        printf("\nУдаление динамических объектов:\n");
        delete mc4;//удаление
        delete mc5;
        delete mc6;
    }

    printf("\n\n\n\n");

    {
        printf("Создание объектов:\n");
        MyClass2 mc7(4, 15);//к х и у обращаться не получится
        MyClass2 mc8(mc7);
        printf("\nВызов методов:\n");
        mc7.move(10, 10);
        mc8.move_back(10, 10);
        printf("\nУдаление объектов:\n");
    }

    printf("\n\n\n\n");

    {
        printf("Создание объекта-предка:\n");
        MyClass1* mc10 = new MyClass1(15, 15);
        printf("Создание объекта-потомка:\n");
        maxMyClass* mc9 = new maxMyClass(15, 15, 1);
        printf("\nВызов методов предка и собственных методов:\n");
        mc10->move(5,5);
        mc9->one_step();//к х и у обращаться не получится
        mc9->move(5, 5);//вызов метода предка
        printf("\nУдаление объекта-предка:\n");
        delete mc10;
        printf("\nУдаление объекта-потомка:\n");
        delete mc9;
    }

    printf("\n\n\n\n");

    {
        printf("Создание объектов:\nСоздание MyClass1* = new maxMyClass\n");
        MyClass1* mc10 = new maxMyClass(5, 5, 5);
        printf("Создание maxMyClass = new maxMyClass\n");
        maxMyClass* mc11 = new maxMyClass(5, 5, 5);
        printf("Создание MyClass1 = new MyClass1\n");
        MyClass1* mc12 = new MyClass1(*mc10);
        printf("Создание maxMyClass2 = new maxMyClass2(без переопределяемого метода)\n");
        maxMyClass2* mc13 = new maxMyClass2(5, 5, 5);
        //maxMyClass* mc13 = new maxMyClass(*mc10); - компилироваться не будет
        //maxMyClass* mc14 = new MyClass1(); - компилироваться не будет
        printf("\nПереопределение методов:\n");
        mc10->step();//переопределение методов
        mc11->step();
        mc12->step();
        mc13->step();
        printf("\nУдаление объектов:\n");
        delete mc10;
        delete mc11;
        delete mc12;
        delete mc13;
    }

    printf("\n\n\n\n");

    {
        printf("\nКомпозиция:\n");
        MyBase* mb1 = new MyBase;
        MyBase* mb2 = new MyBase(1, 1, 2, 2);
        MyBase* mb3 = new MyBase(mb2);
        printf("\nУдаление объектов:\n");
        delete mb1;
        delete mb2;
        delete mb3;
    }

    printf("\n\n\n\n");

    {
        printf("\nСоздание объектов-потомков без конструкторов и деструкторов:\n");
        no_class nc1;
        MyClass1* nc2=new no_class;
        no_class* nc3=new no_class();  
        printf("\nУдаление этих объектов:\n");
        delete nc2;
        delete nc3;
    }
}
