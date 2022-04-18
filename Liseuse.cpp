/*
** JOJO 
*/

#include "Liseuse.hpp"

std::string makeUrl(int upload, std::string Name, int tome = 0, int nb = 0)
{
  char buffI[4];
  snprintf(buffI, 4, "%03d", nb);
  std::string uploadB = upload == -1 ? "" : std::to_string(upload);
  
  return "https://i0.wp.com/sushi-scan.su/wp-content/uploads" + uploadB + "/" + Name + "Tome" + std::to_string(tome) + "-" + buffI + ".jpg";
}

void Liseuse::changePng(int modI)
{
  char buffI[4];
  static int way = 0;

  timer.restart();
  if (modI >= 0) {
    bt = sf::Texture(btNext);
    window.setTitle("Liseuse Page : " + url.substr(url.size() - 7, 3));
    bs.setTextureRect(sf::IntRect(0, 0, bt.getSize().x, bt.getSize().y));
    snprintf(buffI, 4, "%03d", stoi(url.substr(url.size() - 7, 3)) + modI);
    url = url.substr(0, url.size() - 7) + buffI + ".jpg";
    if (!way)
    {
      way = 1;
      system(std::string("curl " + url + " > asset/buff.jpg").c_str());
      btNext.loadFromFile("asset/buff.jpg");
      return changePng(modI);
    }
  }
  else
  {
    btNext = sf::Texture(bt);
    snprintf(buffI, 4, "%03d", stoi(url.substr(url.size() - 7, 3)) + modI);
    url = url.substr(0, url.size() - 7) + buffI + ".jpg";
    window.setTitle("Liseuse Page : " + url.substr(url.size() - 7, 3));
    system(std::string("curl " + url + " > asset/buff.jpg").c_str());
    bt.loadFromFile("asset/buff.jpg");
    bs.setTextureRect(sf::IntRect(0, 0, bt.getSize().x, bt.getSize().y));
    if (way)
    {
      way = 0;
      return changePng(modI);
    }
  }

  view.setSize(bt.getSize().x, bt.getSize().y / 2);
  view.setCenter(bt.getSize().x / 2 + 10, 540);
  window.setView(view);
  int bRand = std::rand() % 7000;
  bRand += 7000; // -> 7000 - 14000
  if ((std::rand() % 100) > 50)
  {
    sfx.setPitch((float)bRand / 10000.0f);
    sfx.play();
  }
  else
  {
    sfx2.setPitch((float)bRand / 10000.0f);
    sfx2.play();
  }

  if (modI)
  {
    window.clear();
    window.draw(bs);
    window.display();
    system(std::string("curl " + url + " > asset/buff.jpg").c_str());
    btNext.loadFromFile("asset/buff.jpg");
  }
}

Liseuse::Liseuse(std::string _url) : url(_url), window(sf::VideoMode::getDesktopMode(), "Lecturer")
{
  bsfx.loadFromFile("asset/sfx.ogg");
  sfx.setBuffer(bsfx);
  bsfx2.loadFromFile("asset/sfx2.ogg");
  sfx2.setBuffer(bsfx2);
  system(std::string("curl " + url + " > asset/buff.jpg").c_str());
  btNext.loadFromFile("asset/buff.jpg");

  changePng(1);
  bs.setTexture(bt);
  sf::IntRect v2i = bs.getTextureRect();
  v2i.height /= 2;
  v2i.width += 70;
  v2i.left -= 35;
  view = sf::View(sf::FloatRect(v2i));
  window.setView(view);
  window.setFramerateLimit(45);
  sfx2.setVolume(60);
  sfx.setVolume(60);
  std::cout << std::endl << "URL  : " <<  _url << std::endl; 
}

void Liseuse::move(int mody, int modx)
{
  timer.restart();
  view.move(modx, mody);
  window.setView(view);
}

void Liseuse::play()
{
  bool fstR = true;
  bool freeMove = false;
  sf::Vector2i mPos_old;
  static sf::Vector2i mPos = sf::Mouse::getPosition(window);

  while (window.isOpen())
  {

    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    if (!window.hasFocus())
      continue;
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))&& timer.getElapsedTime().asMilliseconds() > 50)
      changePng(1);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && timer.getElapsedTime().asMilliseconds() > 100 && window.hasFocus())
    {
      freeMove = !freeMove;
      timer.restart();
    }

    if (freeMove && window.hasFocus())
    {
      mPos = sf::Mouse::getPosition(window);
      if (fstR)
      {
        mPos_old = mPos;
        fstR = false;
      }
      float x = (float)mPos_old.x - mPos.x;
      float y = (float)mPos_old.y - mPos.y;
      view.move(x, -y);
      window.setView(view);
      if (mPos.y > 1000)
      {
        sf::Mouse::setPosition(sf::Vector2i(mPos.x, 100), window);
        mPos_old = sf::Vector2i(mPos.x, 100);
      }
      else if (mPos.y < 1)
      {
        sf::Mouse::setPosition(sf::Vector2i(mPos.x, 1000), window);
        mPos_old = sf::Vector2i(mPos.x, 1000);
      }
      else
        mPos_old = mPos;
    }
    else
      fstR = true;

    if (((sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) && timer.getElapsedTime().asMilliseconds() > 10)
      changePng(-1);
    if ((event.type == sf::Event::MouseWheelScrolled))
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || freeMove)
      {
        if (timer.getElapsedTime().asMilliseconds() > 10)
        {
          timer.restart();
          float zoomBuff = 1 - (event.mouseWheelScroll.delta / 10);
          view.zoom(zoomBuff);
          window.setView(view);
        }
      }
      else
        move(-100 * event.mouseWheelScroll.delta);
    }
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && timer.getElapsedTime().asMilliseconds() > 1)
      move(-30);
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && timer.getElapsedTime().asMilliseconds() > 1)
      move(30);
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) && timer.getElapsedTime().asMilliseconds() > 1)
      move(0, -10);
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) && timer.getElapsedTime().asMilliseconds() > 1)
      move(0, 10);
    event.mouseWheelScroll.delta = 0;
    window.clear();
    window.draw(bs);
    window.display();
  }
}
/*
void Liseuse::setTextures()
{
  char buffI[4];
  sf::Texture buff;

  for (size_t i = 0; i < 10; i++)
  {
    snprintf(buffI, 4, "%03d", stoi(url.substr(url.size() - 7, 3)) + 1);
    url = url.substr(0, url.size() - 7) + buffI + ".jpg";
    system(std::string("curl " + url + " > asset/buff.jpg").c_str());
    bufft[i].loadFromFile("asset/buff.jpg");
  }

}
*/
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc != 5) {
    std::cout << "./liseuse MangaName Page Chapter UploaderNumber\n\
      ./liseuse Berserk  1 0 -1\n\
      ./liseuse OPM 1 0 2\n";
  }
  Liseuse lis(makeUrl(std::atoi(argv[4]), argv[1], std::atoi(argv[2]), std::atoi(argv[3])));

  lis.play();
  return 0;
}