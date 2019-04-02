#ifndef CORREDOR_H
#define CORREDOR_H
#include <SFML/Graphics.hpp>


class Corredor
{
    public:
        Corredor(sf::Sprite _s);
        virtual ~Corredor();
        Corredor(const Corredor& other);
        sf::Sprite sprite();
        float X();
        float Y();
        void correr(int tile);
    private:
        sf::Sprite s;
};

#endif // CORREDOR_H
