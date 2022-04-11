#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 700), "SUPER MARIO");
	int rx = 0, ry = 0;
	Texture t, tx, c, tx2, tx3;
	t.loadFromFile("superr.png");
	tx.loadFromFile("background.png");
	tx2.loadFromFile("background.png");
	tx3.loadFromFile("background.png");
	c.loadFromFile("coins.png");
	
	Sprite player(t);
	Sprite map(tx), map2(tx2), map3(tx3);
	Sprite coin(c);

	player.setPosition(300, 300);
	player.setTextureRect(IntRect(0 * 233, 0 * 222, 253, 258));
	player.setScale(0.5, 0.5);
	map.setPosition(-200,-700);
	
	View camera(FloatRect(0, 0, 880, 600));
	
	camera.setCenter(player.getPosition());
	
	window.setView(camera);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			
			
			rx++;
			rx %= 6;
			player.setTextureRect(IntRect(rx * 253, 0 * 258, 253, 258));
			player.move(0.5, 0);
			camera.move(0.5, 0);
			map.move(-0.5, 0);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {

			player.move(-0.5, 0);
			camera.move(-0.5, 0);
			map.move(-0.5, 0);
			rx++;
			rx %= 6;
			player.setTextureRect(IntRect(rx * 253, 1 * 258, 253, 258));
		}
		window.setView(camera);
		
		window.clear();
		window.draw(map);
		window.draw(player);
		
		window.display();
	}

	return 0;
}