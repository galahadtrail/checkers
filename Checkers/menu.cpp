    #include "menu.h"

void InstructionSettings(sf::RenderWindow& window) {
    Texture fon, whites, blacks;
    fon.loadFromFile("images/fon.jpg");
    whites.loadFromFile("images/white.jpg");
    blacks.loadFromFile("images/black.jpg");
    Sprite fons(fon), white(whites, IntRect(0, 0, 70, 39)), black(blacks, IntRect(0, 0, 70, 39));
    std::string rounds = "";
    white.setPosition(250, 250);
    black.setPosition(380, 250);
    white.setColor(Color(255, 255, 255, 84));
    black.setColor(Color(255, 255, 255, 84));
    bool isWhite = false;
    bool isBlack = false;
    std::string color = "";

    sf::RenderWindow windowDaugth(sf::VideoMode(600, 500), "Checker");
    sf::Font font;
    font.loadFromFile("Font//Deutsch Gothic.ttf");

    sf::Text textSettings(L"Настройки игры", font, 20);
    textSettings.setFillColor(sf::Color::Green);
    textSettings.setPosition(20, 50);

    sf::Text textAmount(L"Количество раундов: ", font, 20);
    textAmount.setFillColor(sf::Color::White);
    textAmount.setPosition(20, 150);
    sf::Text textOr(L"или", font, 20);
    textOr.setFillColor(sf::Color::White);
    textOr.setPosition(300, 150);
    sf::Text textFast(L"Быстрая игра", font, 20);
    textFast.setFillColor(sf::Color::White);
    textFast.setPosition(390, 150);
    bool isFast = false;

    sf::Text textVariants(L"Вариант игры: ", font, 20);
    textVariants.setFillColor(sf::Color::White);
    textVariants.setPosition(20, 200);
    sf::Text textRus(L"русские, ", font, 12);
    textRus.setStyle(sf::Text::Italic);
    textRus.setFillColor(sf::Color::White);
    textRus.setPosition(200, 210);
    sf::Text textEngl(L"английские, ", font, 12);
    textEngl.setStyle(sf::Text::Italic);
    textEngl.setFillColor(sf::Color::White);
    textEngl.setPosition(265, 210);
    sf::Text textGive(L"поддавки, ", font, 12);
    textGive.setStyle(sf::Text::Italic);
    textGive.setFillColor(sf::Color::White);
    textGive.setPosition(355, 210);
    sf::Text textInter(L"международные", font, 12);
    textInter.setFillColor(sf::Color::White);
    textInter.setStyle(sf::Text::Italic);
    textInter.setPosition(435, 210);
    bool isRus = false;
    bool isEn = false;
    bool isInter = false;
    bool isGive = false;
    std::string mode = "";

    sf::Text textColor(L"Цвет шашек: ", font, 20);
    textColor.setFillColor(sf::Color::White);
    textColor.setPosition(20, 250);

    sf::Text textStart(L"Начать игру!", font, 20);
    textStart.setFillColor(sf::Color::Red);
    textStart.setPosition(20, 350);
    bool isStart = false;

    sf::Text textEnd(L"Назад", font, 20);
    textEnd.setFillColor(sf::Color::Red);
    textEnd.setPosition(20, 450);
    bool isLeave = false;

    while (windowDaugth.isOpen())
    {
        sf::Event event;
        while (windowDaugth.pollEvent(event))
        {
            if (IntRect(200, 210, 60, 30).contains(Mouse::getPosition(window))) {
                isRus = true;
                textRus.setFillColor(sf::Color::Yellow);
            }
            else {
                textRus.setFillColor(sf::Color::White);
                isRus = false;
            }

            if (IntRect(265, 210, 80, 30).contains(Mouse::getPosition(window))) {
                isEn = true;
                textEngl.setFillColor(sf::Color::Yellow);
            }
            else {
                textEngl.setFillColor(sf::Color::White);
                isEn = false;
            }

            if (IntRect(345, 210, 80, 30).contains(Mouse::getPosition(window))) {
                isGive = true;
                textGive.setFillColor(sf::Color::Yellow);
            }
            else {
                textGive.setFillColor(sf::Color::White);
                isGive = false;
            }

            if (IntRect(435, 210, 120, 30).contains(Mouse::getPosition(window))) {
                isInter = true;
                textInter.setFillColor(sf::Color::Yellow);
            }
            else {
                textInter.setFillColor(sf::Color::White);
                isInter = false;
            }

            if (IntRect(250, 250, 70, 39).contains(Mouse::getPosition(window))) {
                isWhite = true;
                white.setColor(sf::Color::White);
            }
            else {
                white.setColor(Color(255, 255, 255, 84));
                isWhite = false;
            }

            if (IntRect(380, 250, 160, 30).contains(Mouse::getPosition(window))) {
                isBlack = true;
                black.setColor(sf::Color::White);
            }
            else {
                black.setColor(Color(255, 255, 255, 84));
                isBlack = false;
            }

            if (IntRect(390, 150, 160, 30).contains(Mouse::getPosition(window))) {
                isFast = true;
                textFast.setFillColor(sf::Color::Yellow);
            }
            else {
                isFast = false;
                textFast.setFillColor(sf::Color::White);
            }

            if (IntRect(20, 450, 80, 30).contains(Mouse::getPosition(window))) {
                isLeave = true;
                textEnd.setFillColor(sf::Color::Yellow);
            }
            else {
                textEnd.setFillColor(sf::Color::Red);
                isLeave = false;
            }

            if (IntRect(20, 350, 150, 30).contains(Mouse::getPosition(window))) {
                textStart.setFillColor(sf::Color::Yellow);
                isStart = true;
            }
            else {
                textStart.setFillColor(sf::Color::Red);
                isStart = false;
            }

            if (event.type == sf::Event::TextEntered) {
                textFast.setFillColor(sf::Color::White);
                isFast = false;
                if (event.text.unicode == 8 || event.text.unicode == 127) {
                    if (rounds.size() > 0) {
                        rounds.resize(rounds.size() - 1);
                    }
                }
                else {
                    rounds += char(event.text.unicode);
                }
                textAmount.setString(L"Количество раундов: " + rounds);
            }

            if (rounds == "1") {
                textFast.setFillColor(sf::Color::Yellow);
            }

            if (color == "white") {
                white.setColor(Color::White);
            }
            else if (color == "black") {
                black.setColor(Color::Black);
            }
            if (mode == "Russian") {
                textRus.setFillColor(sf::Color::Yellow);
            }
            if (mode == "Checkers") {
                textEngl.setFillColor(sf::Color::Yellow);
            }
            if (mode == "Giveaway") {
                textGive.setFillColor(sf::Color::Yellow);
            }
            if (mode == "International") {
                textInter.setFillColor(sf::Color::Yellow);
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (isLeave) {
                    windowDaugth.close();
                }

                if (isWhite) {
                    white.setColor(Color::White);
                    color = "white";
                }

                if (isBlack) {
                    black.setColor(Color::Black);
                    color = "black";
                }

                if (isRus) {
                    mode = "Russian";
                }

                if (isEn) {
                    mode = "Checkers";
                }

                if (isGive) {
                    mode = "Giveaway";
                }

                if (isInter) {
                    mode = "International";
                }

                if (isFast) {
                    rounds = "1";
                }

                if (isStart && mode != "" && rounds != "" && color != "") {
                    ofstream output("gameSettings.txt");
                    output << rounds << "|" << mode << "|" << color;
                    output.close();
                    windowDaugth.close();
                }
            }
        }
        windowDaugth.clear();
        windowDaugth.draw(fons);
        windowDaugth.draw(textSettings);
        windowDaugth.draw(textAmount);
        windowDaugth.draw(textColor);
        windowDaugth.draw(textStart);
        windowDaugth.draw(white);
        windowDaugth.draw(black);
        windowDaugth.draw(textEngl);
        windowDaugth.draw(textRus);
        windowDaugth.draw(textInter);
        windowDaugth.draw(textGive);
        if (rounds.size() == 0) {
            windowDaugth.draw(textOr);
        }
        windowDaugth.draw(textFast);
        windowDaugth.draw(textVariants);
        windowDaugth.draw(textEnd);
        windowDaugth.display();
    }
}

void UserSettings(sf::RenderWindow& window) {
    std::string userName = "";
    std::string theme = "default";

    Texture fon, hallowen, newYear;
    fon.loadFromFile("images/fon.jpg");
    hallowen.loadFromFile("images/haloween.jpg");
    hallowen.setSmooth(true);
    newYear.loadFromFile("images/new_year.jpg");
    newYear.setSmooth(true);
    CircleShape hallo;
    Sprite fons(fon), halo(hallowen, IntRect(0, 0, 70, 47)), newyear(newYear, IntRect(0, 0, 70, 46));

    sf::RenderWindow windowDaugth(sf::VideoMode(600, 500), "Checker");
    sf::Font font;
    font.loadFromFile("Font//Deutsch Gothic.ttf");
    sf::Text textStart(L"Пользовательские настройки", font, 20);
    textStart.setFillColor(sf::Color::Green);
    textStart.setPosition(20, 50);

    sf::Text textUser(L"Имя пользователя: ", font, 20);
    textUser.setFillColor(sf::Color::White);
    textUser.setStyle(sf::Text::Bold);
    textUser.setPosition(20, 100);

    sf::Text textTheme(L"Тема: ", font, 20);
    textTheme.setFillColor(sf::Color::White);
    textTheme.setPosition(20, 200);

    sf::Text textDefault(L"Default", font, 20);
    textDefault.setFillColor((Color(255, 255, 255, 84)));
    textDefault.setPosition(350, 200);
    halo.setPosition(150, 200);
    newyear.setPosition(250, 200);

    bool isDefault = false;
    bool isHalo = false;
    bool isNew = false;
    halo.setColor((Color(255, 255, 255, 84)));
    newyear.setColor((Color(255, 255, 255, 84)));

    bool save = false;
    sf::Text textFinish(L"Сохранить настройки", font, 20);
    textFinish.setFillColor(sf::Color::White);
    textFinish.setPosition(20, 350);

    sf::Text textExit(L"Отменить изменения", font, 20);
    textExit.setFillColor(sf::Color::Red);
    textExit.setPosition(20, 400);
    bool isExit = false;

    while (windowDaugth.isOpen())
    {
        sf::Event event;
        while (windowDaugth.pollEvent(event))
        {
            if (IntRect(20, 350, 300, 30).contains(Mouse::getPosition(window))) {
                textFinish.setFillColor(sf::Color::Yellow);
                save = true;
            }
            else {
                textFinish.setFillColor(sf::Color::White);
                save = false;
            }

            if (IntRect(150, 200, 70, 47).contains(Mouse::getPosition(window))) {
                halo.setColor(Color::White);
                isHalo = true;
            }
            else {
                isHalo = false;
                halo.setColor(Color(255, 255, 255, 84));
            }

            if (IntRect(350, 200, 140, 47).contains(Mouse::getPosition(window))) {
                textDefault.setFillColor(Color::White);
                isDefault = true;
            }
            else {
                isDefault = false;
                textDefault.setFillColor(Color(255, 255, 255, 84));
            }

            if (IntRect(250, 200, 70, 46).contains(Mouse::getPosition(window))) {
                newyear.setColor(Color::White);
                isNew = true;
            }
            else {
                newyear.setColor(Color(255, 255, 255, 84));
                isNew = false;
            }

            if (IntRect(20, 400, 300, 40).contains(Mouse::getPosition(window))) {
                isExit = true;
                textExit.setFillColor(Color::Yellow);
            }
            else {
                isExit = false;
                textExit.setFillColor(Color::Red);
            }

            if (theme == "Halloween") {
                halo.setColor(Color::White);
            }
            if (theme == "New_Year") {
                newyear.setColor(Color::White);
            }
            if (theme == "Default") {
                textDefault.setFillColor(Color::White);
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 || event.text.unicode == 127) {
                    if (userName.size() > 0) {
                        userName.resize(userName.size() - 1);
                    }
                }
                else {
                    userName += char(event.text.unicode);
                }
                textUser.setString(L"Имя пользователя: " + userName);
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (isHalo) {
                    halo.setColor(Color::White);
                    theme = "Halloween";
                }

                if (isNew) {
                    newyear.setColor(Color::White);
                    theme = "New_Year";
                }

                if (isDefault) {
                    textDefault.setFillColor(Color::White);
                    theme = "Default";
                }

                if (isExit) {
                    windowDaugth.close();
                }

                if (save && userName != "") {
                    ofstream output("user.txt");
                    output <<  userName << "|";
                    output  << theme;
                    output.close();
                    windowDaugth.close();
                }
            }
        }
        windowDaugth.clear();
        windowDaugth.draw(fons);
        windowDaugth.draw(halo);
        windowDaugth.draw(newyear);
        windowDaugth.draw(textTheme);
        windowDaugth.draw(textDefault);
        windowDaugth.draw(textFinish);
        windowDaugth.draw(textUser);
        windowDaugth.draw(textStart);
        windowDaugth.draw(textExit);
        windowDaugth.display();
    }
}

void ExitFunc(sf::RenderWindow& window) {
    window.setActive(false);
    Texture fon;
    fon.loadFromFile("images/fon.jpg");
    Sprite fons(fon);


    sf::RenderWindow windowDaugth(sf::VideoMode(600, 500), "Checker");
    sf::Font font;
    font.loadFromFile("Font//Deutsch Gothic.ttf");

    sf::Text textStart(L"Вы хотите выйти?", font, 30);
    textStart.setFillColor(sf::Color::White);
    textStart.setStyle(sf::Text::Bold);
    textStart.setPosition(150, 150);

    bool stay = false;
    sf::Text yes(L"Да", font, 30);
    yes.setFillColor(sf::Color::White);
    yes.setStyle(sf::Text::Bold);
    yes.setPosition(170, 210);

    bool leave = false;
    sf::Text no(L"Нет", font, 30);
    no.setFillColor(sf::Color::White);
    no.setStyle(sf::Text::Bold);
    no.setPosition(170, 280);

    while (windowDaugth.isOpen())
    {
        sf::Event event;
        while (windowDaugth.pollEvent(event))
        {
            if (IntRect(170, 210, 70, 30).contains(Mouse::getPosition(window))) {
                yes.setFillColor(sf::Color::Yellow);
                leave = true;
            }
            else {
                yes.setFillColor(sf::Color::White);
                leave = false;
            }

            if (IntRect(170, 280, 70, 30).contains(Mouse::getPosition(window))) {
                no.setFillColor(sf::Color::Yellow);
                stay = true;
            }
            else {
                no.setFillColor(sf::Color::White);
                stay = false;
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (leave) {
                    windowDaugth.close();
                    window.close();
                }

                if (stay) {
                    windowDaugth.close();
                }
            }

        }
        windowDaugth.clear();
        windowDaugth.draw(fons);
        windowDaugth.draw(textStart);
        windowDaugth.draw(yes);
        windowDaugth.draw(no);
        windowDaugth.display();
    }
}

void menu(sf::RenderWindow& window)
{
    Texture fon;
    fon.loadFromFile("images/fon.jpg");

    Sprite fons(fon);

    sf::Font font;
    font.loadFromFile("Font//Deutsch Gothic.ttf");

    sf::Text textStart(L"Начать!", font, 30);
    textStart.setFillColor(sf::Color::White);
    textStart.setStyle(sf::Text::Bold);
    textStart.setPosition(230, 150);

    bool isReadyOptions = false;
    sf::Text textInstr(L"Перейти к настройкам игры", font, 15);
    textInstr.setFillColor(sf::Color::White);
    textInstr.setStyle(sf::Text::Italic);
    textInstr.setPosition(150, 200);

    bool isReadyUserSettings = false;
    sf::Text textUserName(L"Перейти к настройкам пользователя", font, 15);
    textUserName.setFillColor(sf::Color::White);
    textUserName.setStyle(sf::Text::Italic);
    textUserName.setPosition(150, 250);

    bool isExit = false;
    sf::Text textExit(L"Выход из игры", font, 15);
    textExit.setFillColor(sf::Color::Red);
    textExit.setStyle(sf::Text::Italic);
    textExit.setPosition(240, 300);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

                window.setActive(false);
                sf::Thread newPollThread(ExitFunc, std::ref(window));
                newPollThread.launch();
                newPollThread.wait();
                window.setActive();
                isReadyOptions = false;
                isReadyUserSettings = false;
                isExit = false;
            }

            if (IntRect(150, 200, 300, 20).contains(Mouse::getPosition(window))) {
                textInstr.setFillColor(sf::Color::Yellow);
                isReadyOptions = true;
            }
            else {
                textInstr.setFillColor(sf::Color::White);
                isReadyOptions = false;
            }

            if (IntRect(150, 250, 300, 20).contains(Mouse::getPosition(window))) {
                textUserName.setFillColor(sf::Color::Yellow);
                isReadyUserSettings = true;
            }
            else {
                textUserName.setFillColor(sf::Color::White);
                isReadyUserSettings = false;
            }

            if (IntRect(240, 300, 300, 20).contains(Mouse::getPosition(window))) {
                textExit.setFillColor(sf::Color::Yellow);
                isExit = true;
            }
            else {
                textExit.setFillColor(sf::Color::Red);
                isExit = false;
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (isReadyOptions) {
                    ofstream out("gameSettings.txt");
                    out << "";
                    out.close();
                    window.setActive(false);
                    sf::Thread newPollThread(InstructionSettings, std::ref(window));
                    newPollThread.launch();
                    newPollThread.wait();
                    window.setActive();

                    Game game;
                    bool start = 1;
                    ifstream in("gameSettings.txt");
                    string str;
                    in >> str;
                    in.close();

                    while (window.isOpen() && str != "") {
                        game.assignValuesFromFile("gameSettings.txt");
                        Event event;

                        while (window.pollEvent(event)) {
                            if (event.type == sf::Event::Closed ||
                                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                window.setActive(false);
                                sf::Thread newPollThread(ExitFunc, std::ref(window));
                                newPollThread.launch();
                                newPollThread.wait();
                                window.setActive();
                            }
                            
                            game.make_move(window, event);
                        }

                        window.clear(Color(245, 210, 175));

                        if (start) {
                            game.start_game(window, event, start);
                        }

                        game.get_checkers_on_board().draw_checkers(window);//рисую поле и шашки

                        game.end_game(window, event);//рисую если конец игры	

                        window.display();
                    }
                }

                if (isReadyUserSettings) {
                    window.setActive(false);
                    sf::Thread newPollThread(UserSettings, std::ref(window));
                    newPollThread.launch();
                    newPollThread.wait();
                    window.setActive();
                }

                if (isExit) {
                    window.setActive(false);
                    sf::Thread newPollThread(ExitFunc, std::ref(window));
                    newPollThread.launch();
                    newPollThread.wait();
                    window.setActive();
                    if (!window.isOpen()) {
                        return;
                    }
                }
            }
        }
        window.clear();
        window.draw(fons);
        window.draw(textStart);
        window.draw(textInstr);
        window.draw(textUserName);
        window.draw(textExit);
        window.display();
    }

    return;
}