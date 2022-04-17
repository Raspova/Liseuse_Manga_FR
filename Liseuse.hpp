/*
** EPITECH PROJECT, 2022
** Liseuse
** File description:
** liseuse
*/

#ifndef LISEUSE_HPP_
#define LISEUSE_HPP_


#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Liseuse
{
private:
    
    std::string url;
    sf::RenderWindow window;

    sf::Texture bt;
    sf::Texture btNext;
    sf::Sprite bs;
    sf::Clock timer;
    sf::View view;
    sf::Sound sfx;
    sf::SoundBuffer bsfx;
    sf::Sound sfx2;
    sf::SoundBuffer bsfx2;

public:
    void setTextures();
    void move(int mody, int modx = 0);
    void changePng(int modI);
    void play();
    Liseuse(std::string _url);
    ~Liseuse();
};
Liseuse::~Liseuse()
{
}


#endif /* !LISEUSE_HPP_ */
