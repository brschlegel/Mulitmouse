#include "UIData.h"

UIData* UIData::instance;

UIData* UIData::getInstance()
{
    if (instance == NULL)
    {
        instance = new UIData();
    }
    return instance;
}

sf::Texture* UIData::getTexture(sf::String name)
{
    if (images.find(name) != images.end())
        return images[name];
    return images["default"];
}

UIData::UIData()
{
    sf::Font font;
    font.loadFromFile("fonts/Main.ttf");
    fonts["MainFont"] = font;
    

    std::vector<sf::String> files{"default", "DebugLevel", "Dodgeball","Juggling", "Pong", "Maze","NonMusicalChairs" };
    for (int i = 0; i < files.size(); i++)
    {
        sf::Image image;
        if (!image.loadFromFile("images/" + files[i] + ".png"))
            std::cout << "Bruh";
        sf::Texture* t = new sf::Texture();
        t->loadFromImage(image);
         
        images[files[i]] = t;
    }
}