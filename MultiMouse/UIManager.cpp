#include "UIManager.h"



using namespace std;
UIManager::UIManager()
{
	//labels.push_back(new Timer(30, 20, 20, 24, Color::getRed(), fonts["MainFont"], Color::getBlue()));
	SCREENWIDTH = sf::VideoMode::getDesktopMode().width;
	SCREENHEIGHT = sf::VideoMode::getDesktopMode().height;
}

void UIManager::draw(sf::RenderWindow* window)
{
	window->pushGLStates();
	window->resetGLStates();
	for (int i = 0; i < labels.size(); i++)
	{
		labels[i]->draw(window);
	}
	for (int i = 0; i < sprites.size(); i++)
	{
		window->draw(*sprites[i]);
	}
	window->popGLStates();
}

Label* UIManager::getLabelByName(std::string name)
{
	for (Label* label : labels)
	{
		if(label->name == name )
			return label;
	}
	return nullptr;
}

void UIManager::unload()
{
	for (int i = 0; i < labels.size(); i++)
	{
		delete labels[i];
	}
}

sf::Vector2<int> UIManager::convertWorldToUICoords(float x, float y)
{
	int newX = (SCREENWIDTH / (8.8889 * 2)) * x + (SCREENWIDTH / 2);
	int newY = (SCREENHEIGHT / 10.0f) * -y + (SCREENHEIGHT / 2);

	return sf::Vector2<int>(newX, newY);
}

sf::Vector2i UIManager::converWorldToUIDim(float width, float height)
{

	int newX = (SCREENWIDTH / (8.8889 * 2)) * width;
		int newY = (SCREENHEIGHT / 10.0f) * height;

	return sf::Vector2<int>(newX, newY);
}

Label* UIManager::buildLabelInTrigger (std::string string, PolygonObject* obj,sf::String fontName, Color color , std::string name)
{
	sf::Vector2i vec = convertWorldToUICoords(obj->x * 2, obj->y * 2);
	Label* l = new Label(string, vec.x, vec.y, 24, color, UIData::getInstance()->fonts[fontName], Color::getBlue(), name);
	labels.push_back(l);
	return l;
}

Label* UIManager::buildLabel(std::string string, float x, float y, int size, sf::String fontName, Color color, std::string name)
{
	sf::Vector2i vec = convertWorldToUICoords(x, y);
	Label* l = new Label(string, vec.x, vec.y, size, color, UIData::getInstance()->fonts[fontName], Color::getBlue(), name);
	labels.push_back(l);
	return l;
}

float UIManager::getWidthOfText(sf::String string, int charSize,  sf::String fontName)
{
	float size = 0;
	sf::Font font = UIData::getInstance()->fonts[fontName];
	
	UINT32 prevChar = -1;
	for (UINT32 c : string)
	{
		sf::Glyph current = font.getGlyph(c, charSize, false);
		size += current.bounds.width;
		if (prevChar != -1)
		{
			size += font.getKerning(prevChar, c, charSize);
		}
		prevChar = c;
	}

	return size * (8.889 * 2) / SCREENWIDTH;
}

sf::String UIManager::fitInBox(sf::String string, int size, float width, sf::String fontname)
{
	std::vector<std::string> words;
	
	std::string s = string;
	//code taken from stack overflow: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		words.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	words.push_back(s);

	//now we have populated words vector

	float lengthOfLine = 0;
	float lengthOfSpace = getWidthOfText(" ", size, fontname);
	std::string newString;
	for (int i = 0; i < words.size(); i++)
	{
		float lengthOfWord = getWidthOfText(words[i], size, fontname);
		lengthOfLine += lengthOfWord;
		lengthOfLine += lengthOfSpace;
		if (lengthOfLine > width)
		{
			lengthOfLine = lengthOfWord + lengthOfSpace;
			words[i] = '\n' + words[i];
		}
		
		newString +=  words[i];
		newString += " ";
	}
	
	return newString;
}

sf::Sprite* UIManager::buildSprite(sf::String imageName, float x, float y, float width, float height)
{
	sf::Sprite* sprite = new sf::Sprite();
	sf::Vector2i vecCoord = convertWorldToUICoords(x, y);
	sf::Vector2i vecDim = converWorldToUIDim(width, height);
	sprite->setTexture(*UIData::getInstance()->getTexture(imageName), true);
	sf::IntRect rect = sprite->getTextureRect();
	//have to choose which one is smaller to preserve aspect ratio
	float scale;
	float xScale = ((float)vecDim.x) / rect.width;
	float yScale = ((float)vecDim.y) / rect.height;
	if (xScale > yScale)
		scale = yScale;
	else
		scale = xScale;

	sprite->setScale( scale,scale ); 
	sf::FloatRect spriteRect = sprite->getLocalBounds();
	sprite->setOrigin(spriteRect.left + spriteRect.width / 2.0f,
		spriteRect.top + spriteRect.height / 2.0f);
	sprite->setPosition(vecCoord.x, vecCoord.y);
	sprites.push_back(sprite);
	return sprite;
}
