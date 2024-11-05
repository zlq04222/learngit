#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <deque>
#include <queue>
#include <random>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 20;
const float SPEED = 0.1f;
// const int SIZE = 2;

class Menu {
public:
    Menu();
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    void setselectedItemIndex();
    int getPressedItem() const { return selectedItemIndex; }
    void reset();
    void draw_a(float width, float height);

private:
    int selectedItemIndex;
    std::vector<sf::Text> menuItems;
    std::vector<sf::Text> settingItems;
    std::vector<sf::Text> colorItems;
    sf::Font font;
};

Menu::Menu() {
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf")) {
    }

    menuItems.emplace_back("Start Game", font, 50);
    menuItems.emplace_back("Settings", font, 50);
    menuItems.emplace_back("Exit", font, 50);
    selectedItemIndex = 0;
}

void Menu::reset() {
    while (!menuItems.empty()) {
        menuItems.pop_back();
    }

    menuItems.emplace_back("Green", font, 50);
    menuItems.emplace_back("Blue", font, 50);
    menuItems.emplace_back("Yellow", font, 50);

    selectedItemIndex = 0;
}

void Menu::draw_a(float width, float height) {
    for (size_t i = 0; i < menuItems.size(); i++) {
        menuItems[i].setPosition(
            width / 2 - menuItems[i].getGlobalBounds().width / 2,
            height / float(menuItems.size() + 1) * float(i + 1));
        menuItems[i].setFillColor(sf::Color::White);

        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::draw(sf::RenderWindow &window) {
    for (const auto &item : menuItems) {
        window.draw(item);
    }
}

void Menu::setselectedItemIndex() { selectedItemIndex = 0; }

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (float(selectedItemIndex + 1) < float(menuItems.size())) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

enum Direction { Up, Down, Left, Right };

struct Snake {
    std::deque<sf::Vector2i> body;
    Direction dir;
};

void resetSnake(Snake &snake) {

    snake.body.clear();
    snake.body.emplace_back(10, 10);
    snake.dir = Right;
}

void moveSnake(Snake &snake) {
    sf::Vector2i newHead = snake.body.front();

    switch (snake.dir) {
    case Up:
        newHead.y--;
        break;
    case Down:
        newHead.y++;
        break;
    case Left:
        newHead.x--;
        break;
    case Right:
        newHead.x++;
        break;
    }

    snake.body.push_front(newHead);
    snake.body.pop_back();
}

bool isCollision(const Snake &snake) {
    const sf::Vector2i &head = snake.body.front();

    if (head.x < 0 || head.x >= WIDTH / CELL_SIZE || head.y < 0 || head.y >= HEIGHT / CELL_SIZE)
        return true;

    for (size_t i = 1; i < snake.body.size(); ++i) {
        if (snake.body[i] == head)
            return true;
    }

    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game");
    Snake snake;
    std::queue<Direction> Myqueue;
    int ge = 0;
    sf::Color snakeColor = sf::Color::Green;
    std::random_device rd;  // 获取随机数种子
    std::mt19937 gen(rd()); // 初始化梅森旋转算法的生成器

    // 定义范围
    std::uniform_int_distribution<int> distX(0, WIDTH / CELL_SIZE - 1);
    std::uniform_int_distribution<int> distY(0, HEIGHT / CELL_SIZE - 1);

    Menu menu;
    bool inMenu = true;

    resetSnake(snake);
    sf::Clock clock;
    sf::Vector2i food(distX(gen), distY(gen));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (inMenu) {
                menu.draw_a(float(window.getSize().x), float(window.getSize().y));
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.moveUp();
                    } else if (event.key.code == sf::Keyboard::Down) {
                        menu.moveDown();
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        switch (menu.getPressedItem() + ge) {
                        case 0:
                            inMenu = false;
                            break;
                        case 1:
                            window.clear();
                            ge += 3;
                            menu.reset();
                            break;
                        case 2:
                            window.close();
                            break;
                        case 3:
                            inMenu = false;
                            break;
                        case 4:
                            snakeColor = sf::Color::Blue;
                            inMenu = false;
                            break;
                        case 5:
                            snakeColor = sf::Color::Yellow;
                            inMenu = false;
                            break;
                        }
                    }
                }
            }
        }

        window.clear();
        if (inMenu) {
            menu.draw(window);
        } else {

            if (clock.getElapsedTime().asSeconds() > SPEED) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if ((Myqueue.empty() && Myqueue.size() < 2 && snake.dir != Down &&
                         snake.dir != Up) ||
                        (Myqueue.front() != Down && Myqueue.size() == 1 && Myqueue.front() != Up)) {
                        Myqueue.push(Up);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if ((Myqueue.empty() && Myqueue.size() < 2 && snake.dir != Down &&
                         snake.dir != Up) ||
                        (Myqueue.front() != Down && Myqueue.size() == 1 && Myqueue.front() != Up)) {
                        Myqueue.push(Down);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    if ((Myqueue.empty() && Myqueue.size() < 2 && snake.dir != Left &&
                         snake.dir != Right) ||
                        (Myqueue.front() != Left && Myqueue.size() == 1 &&
                         Myqueue.front() != Right)) {
                        Myqueue.push(Left);
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if ((Myqueue.empty() && Myqueue.size() < 2 && snake.dir != Left &&
                         snake.dir != Right) ||
                        (Myqueue.front() != Left && Myqueue.size() == 1 &&
                         Myqueue.front() != Right)) {
                        Myqueue.push(Right);
                    }
                }

                if (!Myqueue.empty()) {
                    snake.dir = Myqueue.front();
                    Myqueue.pop();
                }

                moveSnake(snake);

                if (isCollision(snake)) {
                    resetSnake(snake);
                } else if (snake.body.front() == food) {
                    snake.body.push_back(snake.body.back());
                    std::uniform_int_distribution<int> distX(0, WIDTH / CELL_SIZE - 1);
                    std::uniform_int_distribution<int> distY(0, HEIGHT / CELL_SIZE - 1);

                    food = sf::Vector2i(distX(gen), distY(gen));
                }
                clock.restart();
            }

            window.clear();
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

            for (const auto &segment : snake.body) {
                cell.setPosition(float(segment.x) * CELL_SIZE, float(segment.y) * CELL_SIZE);
                cell.setFillColor(snakeColor);
                window.draw(cell);
            }

            cell.setPosition(float(food.x) * CELL_SIZE, float(food.y) * CELL_SIZE);
            cell.setFillColor(sf::Color::Red);
            window.draw(cell);
        }

        window.display();
    }

    return 0;
}
