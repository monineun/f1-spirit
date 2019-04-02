#ifndef ENEMIGO2_H
#define ENEMIGO2_H
#include <SFML/Graphics.hpp>


class Enemigo2
{
    public:
        Enemigo2(sf::Sprite _s);
        virtual ~Enemigo2();
        Enemigo2(const Enemigo2& other);
        sf::Sprite sprite();
        void correr();
        //float X();
        //float Y();
    private:
        sf::Sprite s;
};

#endif // ENEMIGO2_H
