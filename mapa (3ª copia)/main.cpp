#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <iostream>
#include <TileMap.h>
#include <math.h>
#include "Enemigo2.h"
#include "Corredor.h"

#define kVel 2
#define PI 3.141592
#define rad PI/180
#define kMaxSpeed 4
#define kRot 1
#define kFr 0.02

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 720), "F1-SPIRIT");

        sf::Texture tex;
    if (!tex.loadFromFile("resources/pantalla.png"))
    {
        std::cerr << "Error cargando la imagen pantalla.png";
        exit(0);
    }


    sf::Texture tex3;
    if (!tex3.loadFromFile("resources/spritesheet_vehicles.png"))
    {
        std::cerr << "Error cargando la imagen spritesheet_vehicles.png";
        exit(0);
    }

    sf::Sprite sprite(tex);
    sf::Sprite sprite3(tex3);
    sf::Sprite sprite4(tex3);


    sprite3.setOrigin(70/2,131/2);
    sprite3.setTextureRect(sf::IntRect(2*70 + 5, 3*131 - 12, 70, 128));
    sprite3.setPosition(630, 2160);
    sprite3.setScale(0.5f, 0.5f);

    sprite4.setOrigin(70/2,131/2);
    sprite4.setTextureRect(sf::IntRect(3*70 + 5, 3*131 - 12, 70, 128));
    sprite4.setPosition(680, 2160);
    sprite4.setScale(0.5f, 0.5f);

   // Enemigo *coche;
   // coche = new Enemigo(sprite4);

    Corredor* e;
    e = new Corredor(sprite4);

    bool left=false, right=false, delante = false, atras = false, space = false;
    float dirx, diry, vel=0, mv, ang, velf;

    sf::View gameView(sf::FloatRect(0, 0, 480, 680));
    gameView.setViewport(sf::FloatRect(0.02, 0.02, 0.5, 1));
    gameView.zoom(1.3f);
    sf::View fullView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    fullView.setViewport(sf::FloatRect(0, 0, 1, 1));


    int _width, _height, _tilewidth, _spacing;

    tinyxml2::XMLDocument doc;
    doc.LoadFile("circuito.tmx");


    tinyxml2::XMLElement *mapa = doc.FirstChildElement("map");
    mapa->QueryIntAttribute("width", &_width);
    mapa->QueryIntAttribute("height", &_height);
    mapa->QueryIntAttribute("tilewidth", &_tilewidth);


    tinyxml2::XMLElement *esp = mapa->FirstChildElement("tileset");

    tinyxml2::XMLElement *img = esp->FirstChildElement("image");
    const char*filename = img->Attribute("source");

    //std::cout << "Anchura: " << _width << " Altura: " << _height << " Tamano del tile: " << _tilewidth << std::endl;
    //std::cout << "Source: " << filename << std::endl;

    int tam = _width*_height;
    int *_tilemap = new int[tam];

    tinyxml2::XMLElement *data = mapa->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");

    for(int i=0; i<tam; i++){
        data->QueryIntAttribute("gid", &_tilemap[i]);
        data = data->NextSiblingElement("tile");
    }

    TileMap map;
    if (!map.load(filename, sf::Vector2u(_tilewidth, _tilewidth), _tilemap, _width, _height))
        return -1;

    int tilex, tiley, tileactu, tilexe, tileye, tileactue;


//Bucle del juego
    while (window.isOpen())
    {

        tilex = sprite3.getPosition().x/64;
        tiley = sprite3.getPosition().y/64;
        tileactu = _tilemap[tilex + tiley * _width]-1;

        //std::cout << "Estoy en el tile " << tilex << ", " << tiley << ". En el tile " <<  _tilemap[tilex + tiley * _width]-1 << std::endl;



        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) right = true;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) left = true;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) space = true;

        sf::Event event;

        while (window.pollEvent(event))
        {

            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }


        if(space){
         if(vel<kMaxSpeed) vel+=0.01*kVel;
        }else if (vel > 0) vel -= kFr;

        if(sprite3.getRotation()>300) ang = (360 - sprite3.getRotation())*-1;
        else ang = sprite3.getRotation();


        if(right && ang <= 40) sprite3.rotate(1.0f*kRot);

        if(left && ang >-40) sprite3.rotate(-1.0f*kRot);


        right = false;
        left = false;
        space = false;

        dirx = sin(sprite3.getRotation()*rad);
        diry = -cos(sprite3.getRotation()*rad);

        velf=vel;

        if(tileactu==97){
         //std::cout << "Estoy en la hierba" << std::endl;
         velf = vel*0.5;
        }
        else{
         //std::cout << "Ya no estoy en la hierba" << std::endl;
        }

        sprite3.move(dirx*velf, diry*velf);
        gameView.setCenter(sprite3.getPosition());

        tilexe = e->X()/64;
        tileye = e->Y()/64;
        tileactue = _tilemap[tilex + tiley * _width]-1;
        std::cout << "La naranja esta en el " << tileactue << std::endl;

        e->correr(tileactue);

        window.clear();

        window.setView(gameView);
        window.draw(map);
        window.draw(sprite3);
        //window.draw(coche->getCoche());
        window.draw(e->sprite());

        window.setView(fullView);
        window.draw(sprite);

        window.display();

    }

    return EXIT_SUCCESS;
}
