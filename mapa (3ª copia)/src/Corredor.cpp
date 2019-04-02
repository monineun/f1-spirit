#include "Corredor.h"
#include <iostream>
#include <math.h>

#define PI 3.141592
#define rad PI/180

Corredor::Corredor(sf::Sprite _s)
{
   s = _s;
}

Corredor::~Corredor()
{
    //dtor
}

Corredor::Corredor(const Corredor& other)
{
    s = other.s;
}

sf::Sprite Corredor::sprite(){

    return s;

}

float Corredor::X(){
    return s.getPosition().x;
}

float Corredor::Y(){
    return s.getPosition().y;
}

void Corredor::correr(int tile){
int ang;
float dirx, diry;


    if(tile==12 || tile == 13){


        if(s.getRotation() <= 30) s.rotate(1.0f);

    }

    dirx = sin(s.getRotation()*0.0175);
    diry = -cos(s.getRotation()*0.0175);

    s.move(dirx*2, diry*2);
    std::cout << "A moverse " << dirx << " y " << diry << " rota "<< s.getRotation() *0.0175 << std::endl;

}
