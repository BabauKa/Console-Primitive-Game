#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Параметры игрока
struct Player
{
	string name;
	int health;
	int damage;
};

// Параметры противника
struct Enemy
{
	string name;
	int health;
	int damage;
};

// Создание экземпляра
Player player;
Enemy enemy;

class Game
{
	private:
	// Класс игрока
		Player murderer { "Убийца", 450, 30 };
		Player sniper	{ "Меткий глаз", 200, 50 };
		Player skilful	{ "Умелец", 320, 40 };
	// Противники
		Enemy rat		{ "Крыса", 100, 15 };
		Enemy bandit	{ "Бандит", 350, 30 };
		Enemy robot		{ "Штурмовой робот", 650, 50 };
	// Игровые параметры
		int select, i = 1;				// Выбор
		int beat_player, beat_enemy;	// Удар
		int shield_player, shield_enemy;// Блок
		int beat[3] = { 10, 15, 20 };

	public:
		// Метод информации о классе
		void printInfoClass(Player classes)
		{
			cout << i << ")" << classes.name << ": " << classes.health << " здоровья и " << classes.damage << " урона \n";
		}
		void printInfoEnemy(Enemy currentEnemy)
		{
			cout << currentEnemy.name << ": " << currentEnemy.health << " здоровья и " << currentEnemy.damage << " урона\n";
		}

		// Выбор класса
		Game()
		{
			cout << "Выберите персонажа: \n";
			printInfoClass(murderer);
			i++;
			printInfoClass(sniper);
			i++;
			printInfoClass(skilful);
			cin >> select;
			switch (select)
			{
				case 1:
					// Задаем класс игроку
					player = murderer;
					break;
				case 2:
					// Задаем класс игроку
					player = sniper;
					break;
				case 3:
					// Задаем класс игроку
					player = skilful;
					break;
				default:
					cout << "Ой, кажется вы где-то ошиблись! Попробуйте повторить ввод!\n";
					Game();	// Вызов метода
			}
		}

		// Выбор противника (случайно)
		void selectEnemy()
		{
			cout << "Ваш противник: \n";
			select = (1 + rand() % 2);
			switch (select)
			{
				case 1:
					// Задаем класс противнику
					enemy = rat;
					printInfoEnemy(rat);
					break;
				case 2:
					// Задаем класс противнику
					enemy = bandit;
					printInfoEnemy(bandit);
					break;
				case 3:
					// Задаем класс противнику
					enemy = robot;
					printInfoEnemy(robot);
					break;
			}
		}

		// Текущий статус у объектов (Здоровье)
		void playersStatus()
		{
			cout << "У вас здоровья: " << player.health << "\n";
			cout << "У противника здоровья: " << enemy.health << "\n";
		}

		// Система нанесения урона
		int playerBeat()
		{
			cout << "Выберите куда нанести удар: \n";
			cout << "Голова - 1 \n";
			cout << "Туловище - 2 \n";
			cout << "Ноги - 3 \n";
			cin >> beat_player;
			cout << "Выберите где хотите защититься: \n";
			cout << "Голова - 1 \n";
			cout << "Туловище - 2\n";
			cout << "Ноги - 3 \n";
			cin >> shield_player;
			return beat_player, shield_player;
		}

		int enemyBeat()
		{
			beat_enemy = (1 + rand() % 2);
			shield_enemy = (1 + rand() % 2);
			return beat_enemy, shield_enemy;
		}

		// Проверка урона
		void checkBeat()
		{
			// Проверка на совпадения значений удара-защиты (Игрок противнику)
			if (beat_player == shield_enemy)
			{
				beat_player = 0;
				cout << "Ваш противник заблокировал удар. Вы нанесли 0 урона\n";
			}
			else
			{
				beat_player = beat[--beat_player] + player.damage;
				cout << "Вы нанесли противнику " << beat_player << " урона!\n";
				enemy.health -= beat_player;
			}

			// Проверка на совпадений значений удара-защиты (Противник игроку)
			if (beat_enemy == shield_player)
			{
				beat_enemy = 0;
				cout << "Вы заблокировали удар противника. Вам нанесли 0 урона\n";
			}
			else
			{
				beat_enemy = beat[--beat_enemy] + enemy.damage;
				cout << "Ваш противник нанес " << beat_enemy << " урона\n";
				player.health -= beat_enemy;
			}

			// Обнуляем значения
			beat_player	= 0;
			beat_enemy	= 0;
		}
};

int main()
{
	setlocale(LC_ALL, "russian");
	srand(time(0));	// Стартовое рандомное значение (Зависит от времени)
	string startGame;
	Game game;
	game.selectEnemy();
	cout << "Нажмите любую клавишу для начала игры . . . ";
	cin >> startGame;

	while (player.health > 0 && enemy.health > 0)
	{
		game.playersStatus();
		game.playerBeat();
		game.enemyBeat();
		game.checkBeat();
	}

	if (player.health <= 0 && enemy.health > 0)
	{
		cout << "\n Вы проиграли!";
	}
	else if (player.health > 0 && enemy.health <= 0)
	{
		cout << "\n Вы победили!";
	}
	else
	{
		cout << "\nНичья!";
	}

	return 0;
}