#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <graphics.h>
using namespace std;

//void *__gxx_personality_v0;


const int multigx=50;
const int addigx=50;
const int multigy=-50;
const int addigy=400;


ifstream in("poligon.in");
ofstream out("poligon.out");
struct punct
{
    double x,y;

    punct(double _x,double _y):x(_x),y(_y) {}
    punct() {}
    bool operator<(punct b);
    bool operator==(punct b)
    {
        if(x==b.x&&y==b.y)return true;
        else return false;
    }

    bool operator!=(punct b)
    {

        return x!=b.x||y!=b.y;
    }

} aux;  //aux e de fapt centrul de greutate si cum sortarea se va face direct in vector il voi folosi in definirea operatorului ca sa mearga mai usor pentru mine
template <class X>
bool se_gaseste(X a,vector<X> vec)
{
    for(int i=0; i<vec.size(); i++)if(a==vec[i])return true;
    return false;
}

double determinant(punct P,punct Q,punct R)
{
    return Q.x*R.y+P.x*Q.y+R.x*P.y-Q.x*P.y-R.x*Q.y-P.x*R.y;   //formula din curs efectiv in aceeasi ordine
}

bool punct::operator<(punct b)    //aici este efectiv operatorul < facut cu ajutorul determinantului ca sa pot sa sortez apoi punctele cu sort()
{
    int det=determinant(aux,*this,b);
    if(det>0)return true;
    else if(det==0)
    {
        if(x<b.x)return true;
        else return false;
    }
    else return false;



}

int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    vector<punct> puncte;
    int nr_puncte;
    in>>nr_puncte;
    for(int i=0; i<nr_puncte; i++)
    {
        double _x,_y;
        in>>_x>>_y;
        puncte.push_back(punct(_x,_y));
    }

    int _x=0,_y=0;
    for(int i=0; i<puncte.size(); i++)
    {
        _x+=puncte[i].x;
        _y+=puncte[i].y;
    }
    aux.x=_x/nr_puncte;
    aux.y=_y/nr_puncte;

    for(int i=0; i<puncte.size()-1; i++)
    {
        setcolor(BLUE);

        line((int)puncte[i].x*multigx+addigx,(int)puncte[i].y*multigy+addigy,(int)puncte[i+1].x*multigx+addigx,(int)puncte[i+1].y*multigy+addigy);
    }
    setcolor(BLUE);
    line((int)puncte[0].x*multigx+addigx,(int)puncte[0].y*multigy+addigy,(int)puncte[puncte.size()-1].x*multigx+addigx,(int)puncte[puncte.size()-1].y*multigy+addigy);

    delay(500);
    vector<punct> graham;
    graham.push_back(puncte[0]);//adaug primele doua puncte in "stiva" care nu este stiva ca la final mai verific si punctele de la inceput
    graham.push_back(puncte[1]);
    setcolor(YELLOW);
    line((int)graham[0].x*multigx+addigx,(int)graham[0].y*multigy+addigy,(int)graham[1].x*multigx+addigx,(int)graham[1].y*multigy+addigy);
    delay(500);

    for(int i=2; i<puncte.size(); i++)
    {
        setcolor(YELLOW);
        line((int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy,(int)puncte[i].x*multigx+addigx,(int)puncte[i].y*multigy+addigy);
        delay(500);
        if(determinant(graham[graham.size()-2],graham[graham.size()-1],puncte[i])>0)graham.push_back(puncte[i]);    //daca punctul este la stanga il adauga direct
        else
        {
            setcolor(RED);
            line((int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy,(int)puncte[i].x*multigx+addigx,(int)puncte[i].y*multigy+addigy);
            delay(500);


            while(graham.size()>1&&determinant(graham[graham.size()-2],graham[graham.size()-1],puncte[i])<=0)
            {
                setcolor(RED);
                line((int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy,(int)puncte[i].x*multigx+addigx,(int)puncte[i].y*multigy+addigy);
                delay(500);
                setcolor(RED);
                line((int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy,(int)graham[graham.size()-2].x*multigx+addigx,(int)graham[graham.size()-2].y*multigy+addigy);

                delay(500);
                graham.erase(graham.end()-1);
                setcolor(YELLOW);
                line((int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy,(int)puncte[i].x*multigx+addigx,(int)puncte[i].y*multigy+addigy);
                delay(500);

            }  //cat timp punctul este la dreapta elimin ultimul punct din stiva
            graham.push_back(puncte[i]);
        }


    }
    while(graham.size()>2&&determinant(graham[graham.size()-2],graham[graham.size()-1],graham[0])<=0)
    {
        setcolor(RED);
        line((int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy,(int)graham[0].x*multigx+addigx,(int)graham[0].y*multigy+addigy);


        graham.erase(graham.end()-1);
        setcolor(RED);
        line((int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy,(int)graham[0].x*multigx+addigx,(int)graham[0].y*multigy+addigy);


    } //verific inceputul

    cleardevice();
    for(int i=0; i<graham.size()-1; i++)
    {
        setcolor(GREEN);

        line((int)graham[i].x*multigx+addigx,(int)graham[i].y*multigy+addigy,(int)graham[i+1].x*multigx+addigx,(int)graham[i+1].y*multigy+addigy);

    }

    setcolor(GREEN);

    line((int)graham[0].x*multigx+addigx,(int)graham[0].y*multigy+addigy,(int)graham[graham.size()-1].x*multigx+addigx,(int)graham[graham.size()-1].y*multigy+addigy);

    getch();
    out<<graham.size()<<'\n';
    for(int i=0; i<graham.size(); i++)
    {
        out<<graham[i].x<<" "<<graham[i].y<<'\n';

    }


    in.close();
    out.close();
    closegraph();
    return 0;
}
