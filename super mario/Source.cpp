#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/window.hpp>
using namespace sf;
using namespace std;
//jump
bool grounded = false;
int vy = 0;
RectangleShape rec1(Vector2f(3300, 100));
RectangleShape rec2(Vector2f(675, 100));
RectangleShape rec3(Vector2f(3050, 100));
RectangleShape rec4(Vector2f(3050, 100));

void checkPos(Vector2i mousepos);
void checkMusic(Vector2i musicposition);
bool checkground();
//player struct
struct player
{
	Sprite playersprite;
	Texture playertex;
	int playerIndicator = 0, playerDirection = 0;
} mario;

//menu struct
struct gameMenu
{
	Sprite menuSprite;
	Texture menutex;
	int startBut = 0, settingsBut = 0, exitBut = 0;
}menu;

// settings menu struct
struct settingsMenu
{
	Sprite settingsSprite;
	Texture settingsTex;
	int muteBut = 1, doneBut = 0;
} settings;
// coins struct
struct marioCoin {
	Sprite coinSprite;
	Texture coinTex;
	int coinIndicator = 0;
} coins[100];
//main function
int main() {

	RenderWindow window(VideoMode(1200, 700), "Super Mario");
	window.setFramerateLimit(15);
	//score text
	int score = 0;
	Font font;
	font.loadFromFile("PressStart2P-Regular.ttf");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setString("score : " + to_string(score));
	text.setPosition(30, 15);
	text.setCharacterSize(20);
	//mario character
	mario.playertex.loadFromFile("mario sheet.png");
	mario.playersprite.setTexture(mario.playertex);
	mario.playersprite.setTextureRect(IntRect(1 * 45, 2 * 64, 45, 64));
	mario.playersprite.setScale(1.5, 1.5);
	mario.playersprite.setPosition(300, 535);
	//jump
	rec1.setPosition(0, 630);
	rec2.setPosition(3430, 630);
	rec3.setPosition(4285, 630);
	rec4.setPosition(7450, 630);
	//coin collision sound
	SoundBuffer buffer;
	buffer.loadFromFile("mariocoin.ogg");
	Sound sound;
	sound.setBuffer(buffer);
	// coins 

	coins->coinTex.loadFromFile("coinss.png");
	for (int i = 0; i < 100; i++) {
		coins[i].coinSprite.setTexture(coins->coinTex);
		coins[i].coinSprite.setTextureRect(IntRect(0, 0, 192, 171));


		if (i >= 0 && i <= 3)
			coins[i].coinSprite.setPosition(350 + (i * 100), 580);

		else if (i >= 4 && i <= 6)
			coins[i].coinSprite.setPosition(950 + ((i - 4) * 100), 390);
		else if (i >= 7 && i <= 11)
			coins[i].coinSprite.setPosition(1500 + ((i - 7) * 100), 580);
		else if (i >= 12 && i <= 17)
			coins[i].coinSprite.setPosition(2400 + ((i - 12) * 100), 580);
		else if (i >= 18 && i <= 20)
			coins[i].coinSprite.setPosition(3000 + ((i - 18) * 100), 580);
		else if (i >= 21 && i <= 22)
			coins[i].coinSprite.setPosition(3700 + ((i - 21) * 100), 390);
		else if (i >= 23 && i <= 28)
			coins[i].coinSprite.setPosition(3830 + ((i - 23) * 70), 200);
		else if (i >= 29 && i <= 31)
			coins[i].coinSprite.setPosition(4370 + ((i - 29) * 70), 200);
		else if (i == 32)
			coins[i].coinSprite.setPosition(4520, 390);
		else if (i >= 33 && i <= 34)
			coins[i].coinSprite.setPosition(4800 + ((i - 33) * 60), 390);
		else if (i >= 35 && i <= 37)
			coins[i].coinSprite.setPosition(5000 + ((i - 35) * 100), 580);
		else if (i == 38)
			coins[i].coinSprite.setPosition(5670, 390);
		else if (i >= 39 && i <= 41)
			coins[i].coinSprite.setPosition(5800 + ((i - 39) * 60), 200);
		else if (i >= 42 && i <= 43)
			coins[i].coinSprite.setPosition(6150 + ((i - 42) * 120), 200);
		else if (i >= 44 && i <= 45)
			coins[i].coinSprite.setPosition(6200 + ((i - 44) * 60), 390);
		else if (i >= 46 && i <= 48)
			coins[i].coinSprite.setPosition(6900 + ((i - 46) * 60), 580);
		else if (i >= 49 && i <= 50)
			coins[i].coinSprite.setPosition(8050 + ((i - 49) * 60), 390);
		else if (i == 51)
			coins[i].coinSprite.setPosition(8200, 390);
		coins[i].coinSprite.setScale(0.2, 0.2);
	}


	//menu
	menu.menutex.loadFromFile("menu mario2.png");
	menu.menuSprite.setTexture(menu.menutex);
	menu.menuSprite.setPosition(-20, -10);
	menu.menuSprite.setScale(1.6, 1.5);
	//other sprites
	Texture mapTex;
	Sprite map;
	mapTex.loadFromFile("NES - Super Mario Bros - World 1-1.png");
	map.setTexture(mapTex);
	map.setScale(3, 3);
	//settings menu
	settings.settingsTex.loadFromFile("setting 11.png");
	settings.settingsSprite.setTexture(settings.settingsTex);
	settings.settingsSprite.setPosition(760, 10);
	settings.settingsSprite.setScale(2.5, 2.5);

	//mario music
	Music music;
	music.openFromFile("mariomusic.ogg");

	//Camera
	View camera(FloatRect(0, 0, 1200, 700));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i pos = Mouse::getPosition(window);
			checkPos(pos);
		}
		if (menu.settingsBut == 1 && Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i musicPos = Mouse::getPosition(window);
			checkMusic(musicPos);
		}
		if (settings.muteBut == 0) {
			music.play();
		}
		else if (settings.muteBut == 1) {
			music.pause();
		}

		//Moving Right
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (mario.playersprite.getPosition().y < 580) {
				mario.playerDirection = 1;
				if (mario.playersprite.getPosition().x < 540 || mario.playersprite.getPosition().x >= 9420 && mario.playersprite.getPosition().x < 9780)
				{
					mario.playersprite.move(15, 0);
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 2 * 64, 45, 64));
					mario.playerIndicator++;
				}
				else if (mario.playersprite.getPosition().x == 9780)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 3 * 64, 45, 64));
				else
				{
					mario.playersprite.move(15, 0);
					camera.move(15, 0);
					text.move(15, 0);
					mario.playerIndicator++;
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 2 * 64, 45, 64));
				}
			}
		}
		//Moving Left 
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (mario.playersprite.getPosition().y < 580) {
				mario.playerDirection = -1;
				if ((mario.playersprite.getPosition().x > 100 && mario.playersprite.getPosition().x <= 540) || (mario.playersprite.getPosition().x <= 9780 && mario.playersprite.getPosition().x > 9420))
				{
					mario.playersprite.move(-15, 0);
					mario.playerIndicator++;
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 1 * 64, 45, 64));
				}
				else if (mario.playersprite.getPosition().x <= 100)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 1 * 64, 45, 64));
				else
				{
					mario.playerIndicator++;
					mario.playerIndicator %= 4;
					mario.playersprite.setTextureRect(IntRect(mario.playerIndicator * 45, 1 * 64, 45, 64));
					camera.move(-15, 0);
					text.move(-15, 0);
					mario.playersprite.move(-15, 0);


				}
			}
		}
		else
		{
			if (mario.playersprite.getPosition().x == 9780)
				mario.playersprite.setTextureRect(IntRect(1 * 45, 3 * 64, 45, 64));
			else
			{
				if (mario.playerDirection == 1)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 2 * 64, 45, 64));
				else if (mario.playerDirection == -1)
					mario.playersprite.setTextureRect(IntRect(1 * 45, 1 * 64, 45, 64));
			}
		}
		//jump
		if (checkground()) {
			grounded = true;
			vy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				vy = 35;
			}
		}
		else {
			grounded = false;
			vy -= 5;
		}
		//coin animation
		for (int i = 0; i < 100; i++) {
			coins[i].coinSprite.setTextureRect(IntRect(coins->coinIndicator * 192, 0, 192, 171));
		}
		// collision with coins
		for (int i = 0; i < 100; i++) {
			if (mario.playersprite.getGlobalBounds().intersects(coins[i].coinSprite.getGlobalBounds())) {
				coins[i].coinSprite.setScale(0, 0);
				text.setString("score : " + to_string(score));
				score++;
				sound.play();

			}
		}
		coins->coinIndicator++;
		coins->coinIndicator %= 6;

		window.setView(camera);
		window.clear();
		window.draw(menu.menuSprite);
		music.play();

		if (menu.settingsBut == 1 && settings.doneBut == 1) {
			window.draw(menu.menuSprite);
		}
		if (menu.startBut == 1) {
			window.draw(map);
			window.draw(mario.playersprite);
			window.draw(text);
			for (int i = 0; i < 100; i++) {
				if (coins[i].coinSprite.getPosition().x != 0 && coins[i].coinSprite.getPosition().y != 0) {
					window.draw(coins[i].coinSprite);
				}
			}
			mario.playersprite.move(0, -vy);

		}
		else if (menu.settingsBut == 1) {
			window.draw(settings.settingsSprite);
		}
		else if (menu.exitBut == 1) {
			window.close();
		}

		window.display();
	}
	return 0;
}
//to check mouse position in menu
void checkPos(Vector2i mousepos) {
	// to press start
	if (mousepos.x >= 426 && mousepos.x <= 770 && mousepos.y >= 270 && mousepos.y <= 405) {
		menu.startBut = 1;
	}
	// to open settings	
	else if (mousepos.x >= 427 && mousepos.x <= 760 && mousepos.y >= 410 && mousepos.y <= 533) {
		menu.settingsBut = 1;
	}
	// to exit
	else if (mousepos.x >= 427 && mousepos.x <= 760 && mousepos.y >= 539 && mousepos.y <= 672) {
		menu.exitBut = 1;
	}
}
void checkMusic(Vector2i musicposition) {
	// to press mute
	if (musicposition.x >= 802 && musicposition.x <= 898 && musicposition.y >= 200 && musicposition.y <= 300) {
		settings.muteBut = 0;
	}
	// to press unmute
	else if (musicposition.x >= 700 && musicposition.x <= 800 && musicposition.y >= 0 && musicposition.y <= 600) {
		settings.muteBut = 1;
	}
	//to press done
	else if (musicposition.x >= 100 && musicposition.x <= 1000 && musicposition.y >= 0 && musicposition.y <= 800) {
		settings.doneBut = 1;
	}
}
bool checkground() {
	if (mario.playersprite.getGlobalBounds().intersects(rec1.getGlobalBounds()))
		return 1;
	else if (mario.playersprite.getGlobalBounds().intersects(rec2.getGlobalBounds()))
		return 1;
	else if (mario.playersprite.getGlobalBounds().intersects(rec3.getGlobalBounds()))
		return 1;
	else if (mario.playersprite.getGlobalBounds().intersects(rec4.getGlobalBounds()))
		return 1;
	else
		return 0;
}
