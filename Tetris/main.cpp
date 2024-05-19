#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 25;
//Виды фигур
const int Z_TETROMINO = 0;
const int L_TETROMINO = 1;
const int O_TETROMINO = 2;
const int S_TETROMINO = 3;
const int I_TETROMINO = 4;
const int J_TETROMINO = 5;
const int T_TETROMINO = 6;

int board[HEIGHT][WIDTH] = { 0 };

vector <int> generateNewBag() {//СОЗДАНИЕ ФИГУРЫ

	vector <int> template_bag;

	for (int i = 0; i < 7; i++) {

		template_bag.push_back(i);
	}

	vector <int> new_bag;

	while (template_bag.size() > 0) {

		int index = rand() % template_bag.size();
		int choose_piece = template_bag.at(index);
		template_bag.erase(template_bag.begin() + index);
		new_bag.push_back(choose_piece);
	}

	return new_bag;
}

class Piece {//Элемент падающей фигуры

public:

	int x;
	int y;
	int rotation = 1;

	void Rotate(Piece center, int direction) {//Поворот

		int x = this->y - center.y;
		int y = this->x - center.x;
		this->x = center.x + (x * -direction);
		this->y = center.y + (y * direction);

		this->rotation += direction;

		if (this->rotation > 4) this->rotation = 1;
		if (this->rotation < 1) this->rotation = 4;
	}
};

Piece piece[4], cache[4], ghost[4];

int pieces[7][4] = {//координаты фигур

	{3, 4, 5, 6},
	{2, 4, 6, 7},
	{2, 3, 4, 5},
	{2, 4, 5, 7},
	{1, 3, 5, 7},
	{3, 5, 6, 7},
	{2, 4, 5, 6}
};



class Particle { //частицы

public: Particle(int x, int y, int speed, int direction) {

	this->x = x;
	this->y = y;
	this->direction = direction;
	this->speed = speed;
}

	  double x;
	  double y;
	  int direction;
	  double speed;
	  double alpha = 255;
	  RectangleShape shape;

	  void update(double time_per_frame) {

		  double angle = this->direction * (speed / 180); //error
		  this->x += this->speed * cos(angle) * time_per_frame;
		  this->y += this->speed * sin(angle) * time_per_frame;
		  this->alpha -= 400 * time_per_frame;
		  this->speed += 100 * ((-this->speed) / 15) * time_per_frame;
	  }

	  void draw(RenderWindow* window) {

		  this->shape.setSize(Vector2f(2, 2));
		  this->shape.setFillColor(Color(255, 255, 255, max((double)0, (double)this->alpha)));
		  this->shape.setPosition(this->x, this->y);
		  window->draw(this->shape);
	  }
};
vector <Particle> particles;





bool isCollidedGhost() {//Проверяет сталкивается ли "призрачная" фигура с другими эл игрового поля или границами

	for (int i = 0; i < 4; i++) {

		if (ghost[i].y >= HEIGHT) return false;
		else if (board[ghost[i].y][ghost[i].x]) return false;
	}
}

bool isCollided() {//Проверка фигур на сталкивание с другими фигурами или границами поля

	for (int i = 0; i < 4; i++) {

		if (piece[i].x < 0 || piece[i].x >= WIDTH || piece[i].y >= HEIGHT) return false;
		else if (board[piece[i].y][piece[i].x]) return false;
	}
	return 1;
}

bool isDead() {

	for (int i = 0; i < 4; i++) if (board[piece[i].y][piece[i].x]) return true;
	return false;
}

int main() {


	RenderWindow window(VideoMode(600, 720), "TETRIS!", Style::Close);



	//Блоки
	Texture t;
	t.loadFromFile("Tet\\sprite/jstris1.png");
	int texture_size = 30;
	Sprite s(t);
	s.setTextureRect(IntRect(0, 0, texture_size, texture_size));

	//Ghost
	Texture t_ghost;
	t_ghost.loadFromFile("Tet\\sprite/ghost.png");
	Sprite s_ghost(t_ghost);
	s_ghost.setTextureRect(IntRect(0, 0, texture_size, texture_size));


	//Доска
	Texture board_t;
	board_t.loadFromFile("Tet\\sprite/board.png");
	Sprite board_s(board_t);

	//Font
	Font font;
	font.loadFromFile("Tet\\font/Minecraft.ttf");


	int rotate;
	int color;
	int holded;
	int move_left;
	int move_right;

	Clock clock;
	Clock game_elapsed_time;

	double timer;
	double delay;
	vector <int> seven_bag;
	vector <int> seven_bag_next;

restart:

	//Handling control // Проверяется, нажата ли клавиша "Вверх" и флаг is_rotate_cw не установлен
	double das = 8;
	double lock_delay = 0.5;// Задержка перед фиксацией фигуры
	double fastdrop_delay = 0;// Задержка для быстрого падения
	int lock_count = 14; // Количество кадров перед фиксацией

	int all_line_count = 0;// Счетчик очищенных линий
	int all_piece_count = 0;// Счетчик всех фигур


	int lock_count_value = lock_count;
	double das_value = das;
	double lock_delay_value = lock_delay;

	for (int i = 0; i < HEIGHT; i++)// Инициализация игрового поля
		for (int j = 0; j < WIDTH; j++)
			board[i][j] = 0;
	// Сброс таймеров и переменных
	timer = 0;
	delay = 0.5;
	color = 0;
	rotate = 0;
	move_left = 0;
	move_right = 0;
	seven_bag = generateNewBag(); // Генерация нового мешка для текущей фигуры
	seven_bag_next = generateNewBag();// Генерация нового мешка для следующей фигуры

	double piece_indicator_shape_alpha = 0;
	double board_wobble = 0; // Величина колебания игрового поля


	//Выбор первой фигуры 
	int choose_piece = seven_bag.at(0);
	seven_bag.erase(seven_bag.begin());//Удаление выбранной фигуры из списка

	color = choose_piece;//установка цвета фигуры
	for (int i = 0; i < 4; i++) {
		// Расчет начальных координат и поворота для каждой клетки фигуры

		piece[i].x = pieces[choose_piece][i] % 2 + 4;
		piece[i].y = pieces[choose_piece][i] / 2 + 3;
		piece[i].rotation = 0;
		// Корректировка координат для фигуры J
		if (color == J_TETROMINO) piece[i].x--;
	}
	for (int i = 0; i < 4; i++) {
		// Определение начального поворота для каждой фигуры
		Piece center = piece[1];
		if (color == I_TETROMINO) piece[i].Rotate(center, 1);
		if (color == T_TETROMINO) piece[i].Rotate(center, -1);
		if (color == S_TETROMINO) piece[i].Rotate(center, -1);
		if (color == Z_TETROMINO) piece[i].Rotate(center, -1);
		if (color == L_TETROMINO) piece[i].Rotate(center, -1);
		if (color == J_TETROMINO) piece[i].Rotate(center, 1);
	}

	int is_rotate_cw = 0;// Флаг для управления поворотом по часовой стрелке
	int is_right = 0;// Флаг для управления движением вправо
	int is_left = 0;// Флаг для управления движением влево
	

	int key_right = 0;// Флаг для управления движением вправо по клавише
	int key_left = 0;// Флаг для управления движением влево по клавише
	bool is_on_focus = true;// Флаг, указывающий, находится ли окно в фокусе

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asSeconds();// Получение времени с последнего вызова

		for (int i = 0; i < 4; i++) {

			cache[i] = piece[i];
			piece[i].y++;
		}
		if (!isCollided()) {
			lock_delay_value -= time;

			if (lock_delay_value <= 0) {

				for (int i = 0; i < 4; i++) piece[i] = cache[i];
			}
		}
		for (int i = 0; i < 4; i++) piece[i] = cache[i];

		timer += time;// Накопление времени
		clock.restart();// Сброс таймера

		Event e;
		while (window.pollEvent(e)) {

			if (e.type == Event::GainedFocus) is_on_focus = true;// Установка флага фокуса при получении фокуса
			if (e.type == Event::LostFocus) is_on_focus = false;// Сброс флага фокуса при потере фокуса

			if (is_on_focus && e.type == Event::KeyReleased) {
				// Сброс флагов управления при отпускании клавиш
				if (e.key.code == Keyboard::Up) is_rotate_cw = 0;
				if (e.key.code == Keyboard::Left) is_left = 0;
				if (e.key.code == Keyboard::Right) is_right = 0;
			}

			if (e.type == Event::Closed) {

				window.close();// Закрытие окна при нажатии на крестик
			}
		}

		if (is_on_focus) {

			//Key Fixed
			if ((Keyboard::isKeyPressed(Keyboard::Up)) && is_rotate_cw == 0) {

				is_rotate_cw = -1;
				rotate = -1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) && is_left == 0) {

				is_left = -1;
				move_left = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) && is_right == 0) {

				is_right = -1;
				move_right = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::R) ) {

				goto restart;
			}

			//Dead
			if (isDead()) {

				goto restart;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) delay = fastdrop_delay; //"быстрое падение"

			//========================= Движение ========================= 
			key_left = Keyboard::isKeyPressed(Keyboard::Left);
			key_right = Keyboard::isKeyPressed(Keyboard::Right);
			if (!key_left && !key_right) das_value = das;

			if (move_right) 
			{

				for (int i = 0; i < 4; i++) {

					cache[i] = piece[i];
					piece[i].x += 1;
				}

				if (!isCollided()) for (int i = 0; i < 4; i++) piece[i] = cache[i];
				else {

					if (lock_count_value > 0) {

						lock_count_value--;
						lock_delay_value = lock_delay;
					}
				}

				das_value = das;
			}
			if (move_left) {

				for (int i = 0; i < 4; i++) {

					cache[i] = piece[i];
					piece[i].x -= 1;
				}

				if (!isCollided()) for (int i = 0; i < 4; i++) piece[i] = cache[i];
				else {

					if (lock_count_value > 0) {

						lock_count_value--;
						lock_delay_value = lock_delay;
					}
				}

				das_value = das;
			}

			if (das_value <= 0) {

				if (!isCollided()) {

					
					for (int i = 0; i < 4; i++) piece[i] = cache[i];
				}
				else {

					
					if (lock_count_value > 0) {

						lock_count_value--;
						lock_delay_value = lock_delay;
					}

				}
			}
			das_value -= clock.getElapsedTime().asSeconds() * 75;



			//Вращение фигуры Rotate
			if (rotate != 0) {//Проверяется, если `rotate` не равно 0, то выполняется вращение фигуры.

				int before_rotation, after_rotation;//Объявляются переменные `before_rotation` и `after_rotation` для хранения состояния вращения до и после операции.
				for (int i = 0; i < 4; i++) {

					cache[i] = piece[i];
					before_rotation = piece[i].rotation;
					if (color == I_TETROMINO) {

						if (piece[i].rotation == 1) {

							if (rotate == 1) {
								if (i == 0) { piece[i].x -= 1, piece[i].y -= 1; };
								if (i == 2) { piece[i].x += 1, piece[i].y += 1; };
								if (i == 3) { piece[i].x += 2, piece[i].y += 2; };
							}
							else {
								if (i == 0) { piece[i].x -= 2, piece[i].y += 2; };
								if (i == 1) { piece[i].x -= 1, piece[i].y += 1; };
								if (i == 3) { piece[i].x += 1, piece[i].y -= 1; };
							}
						}
						if (piece[i].rotation == 2) {

							if (rotate == 1) {
								if (i == 0) { piece[i].x -= 2, piece[i].y += 2; };
								if (i == 1) { piece[i].x -= 1, piece[i].y += 1; };
								if (i == 3) { piece[i].x += 1, piece[i].y -= 1; };
							}
							else {
								if (i == 0) { piece[i].x += 1, piece[i].y += 1; };
								if (i == 2) { piece[i].x -= 1, piece[i].y -= 1; };
								if (i == 3) { piece[i].x -= 2, piece[i].y -= 2; };
							}
						}
						if (piece[i].rotation == 3) {

							if (rotate == 1) {
								if (i == 0) { piece[i].x += 1, piece[i].y += 1; };
								if (i == 2) { piece[i].x -= 1, piece[i].y -= 1; };
								if (i == 3) { piece[i].x -= 2, piece[i].y -= 2; };
							}
							else {
								if (i == 0) { piece[i].x += 2, piece[i].y -= 2; };
								if (i == 1) { piece[i].x += 1, piece[i].y -= 1; };
								if (i == 3) { piece[i].x -= 1, piece[i].y += 1; };
							}
						}
						if (piece[i].rotation == 4) {

							if (rotate == 1) {
								if (i == 0) { piece[i].x += 2, piece[i].y -= 2; };
								if (i == 1) { piece[i].x += 1, piece[i].y -= 1; };
								if (i == 3) { piece[i].x -= 1, piece[i].y += 1; };
							}
							else {
								if (i == 0) { piece[i].x -= 1, piece[i].y -= 1; };
								if (i == 2) { piece[i].x += 1, piece[i].y += 1; };
								if (i == 3) { piece[i].x += 2, piece[i].y += 2; };
							}
						}
						piece[i].rotation += rotate;
					}
					else if (color != O_TETROMINO) piece[i].Rotate(piece[1], rotate);

					if (piece[i].rotation > 4) piece[i].rotation = 1;
					if (piece[i].rotation < 1) piece[i].rotation = 4;

					after_rotation = piece[i].rotation;
				}


			}

			//Обновление игры
			if (timer > delay) {// Если таймер превысил задержку, выполняем следующие действия:



				for (int i = 0; i < 4; i++) {

					cache[i] = piece[i];
					piece[i].y++;
				}

				if (!isCollided() && lock_delay_value < 0) {

					board_wobble = 7; //Включаем дрожь игрового поля
					all_piece_count++;
					
					for (int i = 0; i < 4; i++) board[cache[i].y][cache[i].x] = color + 1;
					int choose_piece = seven_bag.at(0);
					seven_bag.erase(seven_bag.begin());
					if (seven_bag.size() == 0) {
						seven_bag = seven_bag_next;
					}

					color = choose_piece;//Установка цвета новой фигуры 
					for (int i = 0; i < 4; i++) {

						piece[i].x = pieces[choose_piece][i] % 2 + 4;
						piece[i].y = pieces[choose_piece][i] / 2 + 2;
						piece[i].rotation = 0;

						if (color == J_TETROMINO) piece[i].x--;
						if (color == I_TETROMINO) piece[i].y++;
					}
					for (int i = 0; i < 4; i++) {
						//Применяем поворот для каждой фигуры
						Piece center = piece[1];
						if (color == I_TETROMINO) piece[i].Rotate(center, 1);
						if (color == T_TETROMINO) piece[i].Rotate(center, -1);
						if (color == S_TETROMINO) piece[i].Rotate(center, -1);
						if (color == Z_TETROMINO) piece[i].Rotate(center, -1);
						if (color == L_TETROMINO) piece[i].Rotate(center, -1);
						if (color == J_TETROMINO) piece[i].Rotate(center, 1);
						piece[i].rotation = 1;
					}

					lock_delay_value = lock_delay;
					lock_count_value = lock_count;

					//=====================Очистка линий========================
					int line_clear_count = 0;
					int checkLine = HEIGHT - 1;
					for (int i = HEIGHT - 1; i > 0; i--) {

						int count = 0;
						for (int j = 0; j < WIDTH; j++) {//удаление полных линий

							if (board[i][j]) count++;
							board[checkLine][j] = board[i][j];
						}
						if (count < WIDTH) checkLine--;
						else line_clear_count++;
					}
					if (line_clear_count != 0) {
						all_line_count += line_clear_count;//посчет полных линий
					}
					

					

				}
				else if (!isCollided()) {

					for (int i = 0; i < 4; i++) piece[i] = cache[i];
				}
				else {

					lock_count_value = lock_count;
				}

				timer = 0;
			}
			board_wobble += 100 * ((-board_wobble) / 15) * time;

			//Обновление "призрачных " фигур
			for (int i = 0; i < 4; i++) {

				ghost[i].x = piece[i].x;
				ghost[i].y = piece[i].y;
			}
			for (int i = 0; i < 4; i++) {

				while (isCollidedGhost()) {

					for (int i = 0; i < 4; i++) ghost[i].y++;
				}

				for (int i = 0; i < 4; i++) ghost[i].y--;
			}


			rotate = 0;
			delay = 0.5;
			move_left = 0;
			move_right = 0;

			window.clear(Color::Black);

			//Поле
			RectangleShape backboard_shape;
			backboard_shape.setSize(Vector2f(320, 650));
			backboard_shape.setFillColor(Color::White);
			backboard_shape.setPosition(140, 20 + board_wobble);
			window.draw(backboard_shape);

			//Рисуем сетку
			board_s.setPosition(150, -30 + board_wobble);
			window.draw(board_s);

			// Шкала времени

			float das_progress = max((double)0, (double)(lock_delay_value / lock_delay));

			RectangleShape das_bar_shape;
			das_bar_shape.setSize(Vector2f(das_progress * 320, 8));
			das_bar_shape.setFillColor(Color::White);
			das_bar_shape.setPosition(140, 700 + board_wobble);
			window.draw(das_bar_shape);



			//Отрисовка следующей фигуры
			s.setColor(Color(255, 255, 255, 255));
			for (int i = 0; i < seven_bag.size() + seven_bag_next.size(); i++) {

				if (i < 5) {

					Piece next_piece[4];
					int next_piece_choose;
					if (i < seven_bag.size()) next_piece_choose = seven_bag.at(i);
					else next_piece_choose = seven_bag_next.at(i - seven_bag.size());

					int next_color = next_piece_choose;
					for (int j = 0; j < 4; j++) {

						next_piece[j].x = pieces[next_piece_choose][j] % 2 + 4;
						next_piece[j].y = pieces[next_piece_choose][j] / 2 + 3;

						if (next_color == J_TETROMINO) next_piece[j].x--;
					}
					for (int j = 0; j < 4; j++) {

						Piece center = next_piece[1];
						if (next_color == I_TETROMINO) next_piece[j].Rotate(center, 1);
						if (next_color == T_TETROMINO) next_piece[j].Rotate(center, -1);
						if (next_color == S_TETROMINO) next_piece[j].Rotate(center, -1);
						if (next_color == Z_TETROMINO) next_piece[j].Rotate(center, -1);
						if (next_color == L_TETROMINO) next_piece[j].Rotate(center, -1);
						if (next_color == J_TETROMINO) next_piece[j].Rotate(center, 1);
					}

					for (int j = 0; j < 4; j++) {

						s.setTextureRect(IntRect(next_color * texture_size, 0, texture_size, texture_size));
						int x_offset = 0;
						if (next_color == I_TETROMINO || next_color == O_TETROMINO) x_offset = 15;
						s.setPosition(next_piece[j].x * texture_size + 395 - x_offset, next_piece[j].y * texture_size - 10 + (90 * i));
						window.draw(s);
					}
				}
			}

			//Отрисовка упавших фигур
			for (int i = 0; i < HEIGHT; i++) {

				for (int j = 0; j < WIDTH; j++) {

					s.setColor(Color(255, 255, 255, 255));
					if (board[i][j] == 0) continue;
					s.setTextureRect(IntRect((board[i][j] - 1) * texture_size, 0, texture_size, texture_size));
					s.setPosition(j * texture_size + 150, i * texture_size - 90 + board_wobble);
					window.draw(s);
				}
			}


			//Отрисовка "призрачной" фигуры
			s_ghost.setTextureRect(IntRect(color * texture_size, 0, texture_size, texture_size));
			for (int i = 0; i < 4; i++) {

				s_ghost.setPosition(piece[i].x * texture_size + 150, ghost[i].y * texture_size - 90 + board_wobble);
				window.draw(s_ghost);
			}

			//Падающей фигуры
			piece_indicator_shape_alpha = (sin(game_elapsed_time.getElapsedTime().asSeconds() * 10) + 1) * 30;
			RectangleShape piece_indicator_shape;
			piece_indicator_shape.setSize(Vector2f(30, 30));
			piece_indicator_shape.setFillColor(Color(255, 255, 255, piece_indicator_shape_alpha));

			float piece_alpha = max((double)0, (double)(lock_delay_value / lock_delay));
			for (int i = 0; i < 4; i++) {

				s.setTextureRect(IntRect(color * texture_size, 0, texture_size, texture_size));
				s.setColor(Color(255, 255, 255, piece_alpha * 255));
				s.setPosition(piece[i].x * texture_size + 150, piece[i].y * texture_size - 90 + board_wobble);
				window.draw(s);

				piece_indicator_shape.setPosition(piece[i].x * texture_size + 150, piece[i].y * texture_size - 90 + board_wobble);
				window.draw(piece_indicator_shape);
			}

			//Блестки
			for (int i = 0; i < particles.size(); i++) {

				particles.at(i).update(time);
				particles.at(i).draw(&window);
				if (particles.at(i).alpha <= 0) particles.erase(particles.begin() + i);
			}

			//Игровая доска
			backboard_shape.setSize(Vector2f(320, 20));
			backboard_shape.setFillColor(Color::Black);
			backboard_shape.setPosition(140, 0 + board_wobble);
			window.draw(backboard_shape);

			backboard_shape.setSize(Vector2f(320, 10));
			backboard_shape.setFillColor(Color::White);
			backboard_shape.setPosition(140, 10 + board_wobble);
			window.draw(backboard_shape);

			//Текст
			Text text;
			text.setFont(font); //Установка шрифта для текста
			text.setCharacterSize(35);//Размер символов
			text.setFillColor(Color::White);//Цвет

			text.setString("NEXT");
			text.setPosition(480, 30);
			window.draw(text);

			text.setString("control:");
			text.setPosition(7, 30);
			window.draw(text);

			text.setString("R-reset");
			text.setPosition(7, 80);
			window.draw(text);

			RectangleShape text_box; //Прямоугольник под текстом
			FloatRect text_rect = text.getLocalBounds();;
			text_box.setFillColor(Color::White);

			text.setFillColor(Color::Black);
			text.setCharacterSize(25);
			text.setString("LINES");
			text_rect = text.getLocalBounds();
			text.setPosition(120 - text_rect.width, 400 + board_wobble);
			text_box.setSize(Vector2f(text_rect.width + 40, text_rect.height * 2 - 4));
			text_box.setOrigin(Vector2f(20, 0));
			text_box.setPosition(text.getPosition());
			window.draw(text_box);
			window.draw(text);

			text.setFillColor(Color::White);
			text.setCharacterSize(30);
			text.setString(to_string(all_line_count));
			text_rect = text.getLocalBounds();
			text.setPosition(120 - text_rect.width, 450 + board_wobble);
			window.draw(text);

			text.setFillColor(Color::Black);
			text.setCharacterSize(25);
			text.setString("PIECES");
			text_rect = text.getLocalBounds();
			text.setPosition(120 - text_rect.width, 510 + board_wobble);
			text_box.setSize(Vector2f(text_rect.width + 40, text_rect.height * 2 - 4));
			text_box.setOrigin(Vector2f(20, 0));
			text_box.setPosition(text.getPosition());
			window.draw(text_box);
			window.draw(text);

			text.setFillColor(Color::White);
			text.setCharacterSize(30);
			text.setString(to_string(all_piece_count));
			text_rect = text.getLocalBounds();
			text.setPosition(120 - text_rect.width, 560 + board_wobble);
			window.draw(text);

			window.display();

		}
	}
	return 0;
}