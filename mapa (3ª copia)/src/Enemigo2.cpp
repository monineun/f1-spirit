#include "Enemigo2.h"

Enemigo2::Enemigo2(sf::Sprite _s)
{
    s = _s;
}

Enemigo2::~Enemigo2()
{
    //dtor
}

Enemigo2::Enemigo2(const Enemigo2& e)
{
    s = e.s;
}

sf::Sprite Enemigo2::sprite(){

    return s;

}

void Enemigo2::correr(){


}

/*

float Enemigo2::X(){
    return e.s.getPosition().x;
}

float Enemigo2::Y(){
    return e.s.getPosition().y;
}

*/
