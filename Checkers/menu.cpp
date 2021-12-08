#include "menu.h"
#include "Game.h"

class PauseOption {
private:
    int option = 0;
    int pauseTime = 0;
    int delayTime = 0;

public:
    int getOption() { return this->option; }
    void setOption(int val) { this->option = val; }
    int getTime() { return this->pauseTime; }
    void setTime(int val) { this->pauseTime = val; }
    int getDelayTime() { return this->delayTime; }
    void setDelayTime(int val) { this->delayTime = val; }
};

PauseOption pauseOption;

void InstructionSettings(sf::RenderWindow& window) {
    Texture fon, whites, blacks;
    fon.loadFromFile("images/fon4.jpg");
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

    sf::RenderWindow windowDaugth(sf::VideoMode(960, 600), "Checkers");
    sf::Font font1;
    font1.loadFromFile("Font//Deutsch Gothic.ttf");
    sf::Font font2;
    font2.loadFromFile("Font//bahnschrift.ttf");

    sf::Text textSettings(L"Настройки игры", font1, 35);
    textSettings.setFillColor(sf::Color::Black);
    textSettings.setStyle(sf::Text::Bold);
    textSettings.setPosition(20, 50);

    sf::Text textAmount(L"Количество раундов: ", font2, 23);
    textAmount.setFillColor(sf::Color::Black);
    textAmount.setStyle(sf::Text::Bold);
    textAmount.setOutlineColor(sf::Color::White);
    textAmount.setOutlineThickness(1);
    textAmount.setPosition(20, 150);

    sf::Text textOr(L"или", font2, 23);
    textOr.setFillColor(sf::Color::Black);
    textOr.setOutlineColor(sf::Color::White);
    textOr.setOutlineThickness(1);
    textOr.setStyle(sf::Text::Bold);
    textOr.setPosition(322, 150);

    sf::Text textFast(L"Быстрая игра", font2, 23);
    textFast.setFillColor(sf::Color::Black);
    textFast.setStyle(sf::Text::Bold);
    textFast.setOutlineColor(sf::Color::White);
    textFast.setOutlineThickness(1);
    textFast.setPosition(370, 150);
    bool isFast = false;

    sf::Text textVariants(L"Вариант игры: ", font2, 23);
    textVariants.setFillColor(sf::Color::Black);
    textVariants.setStyle(sf::Text::Bold);
    textVariants.setOutlineColor(sf::Color::White);
    textVariants.setOutlineThickness(1);
    textVariants.setPosition(20, 200);

    sf::Text textRus(L"Русские  ", font1, 13);
    textRus.setFillColor(sf::Color::Black);
    textRus.setPosition(200, 210);
    textRus.setOutlineColor(sf::Color::White);
    textRus.setOutlineThickness(1);

    sf::Text textEngl(L"Английские  ", font1, 13);
    textEngl.setFillColor(sf::Color::Black);
    textEngl.setPosition(265, 210);
    textEngl.setOutlineColor(sf::Color::White);
    textEngl.setOutlineThickness(1);

    sf::Text textGive(L"Поддавки  ", font1, 13);
    textGive.setFillColor(sf::Color::Black);
    textGive.setOutlineColor(sf::Color::White);
    textGive.setOutlineThickness(1);
    textGive.setPosition(355, 210);

    sf::Text textInter(L"Международные", font1, 13);
    textInter.setFillColor(sf::Color::Black);
    textInter.setOutlineColor(sf::Color::White);
    textInter.setOutlineThickness(1);
    textInter.setPosition(435, 210);

    bool isRus = false;
    bool isEn = false;
    bool isInter = false;
    bool isGive = false;
    std::string mode = "";

    sf::Text textColor(L"Цвет шашек: ", font2, 23);
    textColor.setFillColor(sf::Color::Black);
    textColor.setStyle(sf::Text::Bold);
    textColor.setOutlineColor(sf::Color::White);
    textColor.setOutlineThickness(1);
    textColor.setPosition(20, 250);

    sf::Text textStart(L"Начать игру", font1, 23);
    textStart.setFillColor(sf::Color::Black);
    textStart.setStyle(sf::Text::Bold);
    textStart.setOutlineColor(sf::Color::White);
    textStart.setOutlineThickness(1);
    textStart.setPosition(20, 500);
    bool isStart = false;

    sf::Text textEnd(L"Назад", font1, 23);
    textEnd.setFillColor(sf::Color::Red);
    textEnd.setStyle(sf::Text::Bold);
    textEnd.setOutlineColor(sf::Color::White);
    textEnd.setOutlineThickness(1);
    textEnd.setPosition(20, 600);
    bool isLeave = false;

    sf::Text textRegime(L"Режим игры: ", font2, 23);
    textRegime.setFillColor(sf::Color::Black);
    textRegime.setStyle(sf::Text::Bold);
    textRegime.setOutlineColor(sf::Color::White);
    textRegime.setOutlineThickness(1);
    textRegime.setPosition(20, 400);

    sf::Text textComp(L"vs. Computer", font2, 23);
    textComp.setFillColor(sf::Color::Black);
    textComp.setStyle(sf::Text::Bold);
    textComp.setOutlineColor(sf::Color::White);
    textComp.setOutlineThickness(1);
    textComp.setPosition(200, 400);
    bool vsComputer = false;

    sf::Text textPVP(L"PvP", font2, 23);
    textPVP.setFillColor(sf::Color::Black);
    textPVP.setStyle(sf::Text::Bold);
    textPVP.setOutlineColor(sf::Color::White);
    textPVP.setOutlineThickness(1);
    textPVP.setPosition(400, 400);
    bool pvp = false;
    wstring regime = L"";

    sf::Text textGuest(L"Guest name:", font2, 23);
    textGuest.setFillColor(sf::Color::Black);
    textGuest.setStyle(sf::Text::Bold);
    textGuest.setOutlineColor(sf::Color::White);
    textGuest.setOutlineThickness(1);
    textGuest.setPosition(20, 450);
    wstring guestName = L"";

    while (windowDaugth.isOpen())
    {
        sf::Event event;
        while (windowDaugth.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                windowDaugth.close();
            }

            if (IntRect(200, 400, 120, 30).contains(Mouse::getPosition(windowDaugth))) {
                vsComputer = true;
                textComp.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                textComp.setFillColor(sf::Color::Black);
                vsComputer = false;
            }

            if (IntRect(400, 400, 120, 30).contains(Mouse::getPosition(windowDaugth))) {
                pvp = true;
                textPVP.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                textPVP.setFillColor(sf::Color::Black);
                pvp = false;
            }

            if (IntRect(200, 210, 60, 30).contains(Mouse::getPosition(windowDaugth))) {
                isRus = true;
                textRus.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                textRus.setFillColor(sf::Color::Black);
                isRus = false;
            }

            if (IntRect(265, 210, 80, 30).contains(Mouse::getPosition(windowDaugth))) {
                isEn = true;
                textEngl.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                textEngl.setFillColor(sf::Color::Black);
                isEn = false;
            }

            if (IntRect(345, 210, 80, 30).contains(Mouse::getPosition(windowDaugth))) {
                isGive = true;
                textGive.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                textGive.setFillColor(sf::Color::Black);
                isGive = false;
            }

            if (IntRect(435, 210, 120, 30).contains(Mouse::getPosition(windowDaugth))) {
                isInter = true;
                textInter.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                textInter.setFillColor(sf::Color::Black);
                isInter = false;
            }

            if (IntRect(250, 250, 70, 39).contains(Mouse::getPosition(windowDaugth))) {
                isWhite = true;
                white.setColor(sf::Color::White);
            }
            else {
                white.setColor(Color(255, 255, 255, 84));
                isWhite = false;
            }

            if (IntRect(380, 250, 160, 30).contains(Mouse::getPosition(windowDaugth))) {
                isBlack = true;
                black.setColor(sf::Color::Black);
            }
            else {
                black.setColor(Color(0, 0, 0, 84));
                isBlack = false;
            }

            if (IntRect(370, 150, 160, 30).contains(Mouse::getPosition(windowDaugth))) {
                isFast = true;
                textFast.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                isFast = false;
                textFast.setFillColor(sf::Color::Black);
            }

            if (IntRect(20, 400, 80, 30).contains(Mouse::getPosition(windowDaugth))) {
                isLeave = true;
                textEnd.setFillColor(sf::Color::Color(160, 70, 0));
            }
            else {
                textEnd.setFillColor(sf::Color::Red);
                isLeave = false;
            }

            if (IntRect(20, 500, 150, 30).contains(Mouse::getPosition(windowDaugth))) {
                textStart.setFillColor(sf::Color::Color(160, 70, 0));
                isStart = true;
            }
            else {
                textStart.setFillColor(sf::Color::Black);
                isStart = false;
            }

            if (event.type == sf::Event::TextEntered || event.key.code == sf::Keyboard::Delete) {
                textFast.setFillColor(sf::Color::Black);
                isFast = false;

                if (event.text.unicode == 8 || event.key.code == sf::Keyboard::Delete) {
                    if (rounds.size() > 0 && event.text.unicode == 8) {
                        rounds.resize(rounds.size() - 1);
                    }
                    if (guestName.size() > 0 && event.key.code == sf::Keyboard::Delete) {
                        guestName.resize(guestName.size() - 1);
                    }
                }
                else if (event.text.unicode >= 49 && event.text.unicode <= 58){
                    rounds += char(event.text.unicode);
                } else {
                    guestName += wchar_t(event.text.unicode);
                }
                textGuest.setString(L"Guest name: " + guestName);
                textAmount.setString(L"Количество раундов:   " + rounds);
            }

            if (rounds == "1") {
                textFast.setFillColor(sf::Color::Color(160, 70, 0));
            }

            if (color == "white") {
                white.setColor(Color::White);
            }
            else if (color == "black") {
                black.setColor(Color::Black);
            }
            if (mode == "Russian") {
                textRus.setFillColor(sf::Color::Color(160, 70, 0));
            }
            if (mode == "Checkers") {
                textEngl.setFillColor(sf::Color::Color(160, 70, 0));
            }
            if (mode == "Giveaway") {
                textGive.setFillColor(sf::Color::Color(160, 70, 0));
            }
            if (mode == "International") {
                textInter.setFillColor(sf::Color::Color(160, 70, 0));
            }
            if (regime == L"Computer") {
                textComp.setFillColor(sf::Color::Color(160, 70, 0));
            }
            if (regime == L"PvP") {
                textPVP.setFillColor(sf::Color::Color(160, 70, 0));
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (isLeave) {
                    windowDaugth.close();
                }
                if (vsComputer) {
                    regime = L"Computer";
                }
                if (pvp) {
                    regime = L"PvP";
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
                    textAmount.setString(L"Количество раундов:   1");
                }

                if (isStart && mode != "" && rounds != "" && color != "" && regime != L"" && guestName != L"") {
                    ofstream output("gameSettings.txt");
                    output << rounds << "|" << mode << "|" << color;
                    output.close();
                    wofstream outpu("regime.txt");
                    outpu << regime <<L"|"<< guestName;
                    outpu.close();
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
        windowDaugth.draw(textComp);
        windowDaugth.draw(textRegime);
        windowDaugth.draw(textPVP);
        windowDaugth.draw(textGuest);
        windowDaugth.draw(textEnd);
        windowDaugth.display();
    }
}

void UserSettings(sf::RenderWindow& window) {
    std::locale::global(std::locale(""));
    std::wstring userName = L"";
    std::wstring theme = L"Default";

    Texture fon, hallowen, newYear;
    fon.loadFromFile("images/fon3.jpg");
   
    CircleShape hallo;
    Sprite fons(fon);

    sf::RenderWindow windowDaugth(sf::VideoMode(960, 600), "Checkers");
    sf::Font font1;
    font1.loadFromFile("Font//Deutsch Gothic.ttf");
    sf::Font font2;
    font2.loadFromFile("Font//Bahnschrift.ttf");

    sf::Text textStart(L"Настройки", font1, 35);
    textStart.setFillColor(sf::Color::Black);
    textStart.setStyle(sf::Text::Bold);
    textStart.setPosition(20, 50);

    sf::Text textUser(L"Имя пользователя: ", font2, 23);
    textUser.setFillColor(sf::Color::Black);
    textUser.setStyle(sf::Text::Bold);
    textUser.setOutlineColor(sf::Color::White);
    textUser.setOutlineThickness(1);
    textUser.setPosition(20, 100);

    sf::Text textTheme(L"Тема: ", font2, 23);
    textTheme.setFillColor(sf::Color::Black);
    textTheme.setStyle(sf::Text::Bold);
    textTheme.setOutlineColor(sf::Color::White);
    textTheme.setOutlineThickness(1);
    textTheme.setPosition(20, 200);

    sf::Text bw(L"Black&White", font1, 23);
    bw.setFillColor((Color(0, 0, 0, 84)));
    bw.setStyle(sf::Text::Bold);
    bw.setOutlineColor(sf::Color::White);
    bw.setOutlineThickness(1);
    bw.setPosition(150, 200);

    sf::Text textDefault(L"Default", font1, 23);
    textDefault.setFillColor((Color(0, 0, 0, 255)));
    textDefault.setStyle(sf::Text::Bold);
    textDefault.setOutlineColor(sf::Color::White);
    textDefault.setOutlineThickness(1);
    textDefault.setPosition(350, 200);

    bool isDefault = true;
    bool isBW = false;

    bool save = false;
    sf::Text textFinish(L"Сохранить настройки", font1, 23);
    textFinish.setFillColor(sf::Color::Black);
    textFinish.setStyle(sf::Text::Bold);
    textFinish.setOutlineColor(sf::Color::White);
    textFinish.setOutlineThickness(1);
    textFinish.setPosition(20, 350);

    sf::Text textExit(L"Отменить изменения", font1, 23);
    textExit.setFillColor(sf::Color::Red);
    textExit.setStyle(sf::Text::Bold);
    textExit.setOutlineColor(sf::Color::White);
    textExit.setOutlineThickness(1);
    textExit.setPosition(20, 400);
    bool isExit = false;

    while (windowDaugth.isOpen())
    {
        sf::Event event;
        while (windowDaugth.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                windowDaugth.close();
            }

            if (IntRect(20, 350, 300, 30).contains(Mouse::getPosition(windowDaugth))) {
                textFinish.setFillColor(sf::Color::Color(165, 70, 0));
                save = true;
            }
            else {
                textFinish.setFillColor(sf::Color::Black);
                save = false;
            }

            if (IntRect(350, 200, 67, 47).contains(Mouse::getPosition(windowDaugth))) {
                textDefault.setFillColor(Color::Black);
                isDefault = true;
            }
            else {
                isDefault = false;
                textDefault.setFillColor(Color(0, 0, 0, 84));
            }

            if (IntRect(150, 200, 113, 46).contains(Mouse::getPosition(windowDaugth))) {
                bw.setFillColor(Color::Black);
                isBW = true;
            }
            else {
                bw.setFillColor(Color(0, 0, 0, 84));
                isBW = false;
            }

            if (IntRect(20, 400, 300, 40).contains(Mouse::getPosition(windowDaugth))) {
                isExit = true;
                textExit.setFillColor(Color::Color(165, 70, 0));
            }
            else {
                isExit = false;
                textExit.setFillColor(Color::Red);
            }


            if (theme == L"BlackWhite") {
                bw.setFillColor(Color::Black);
            }
            if (theme == L"Default") {
                textDefault.setFillColor(Color::Black);
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 || event.text.unicode == 46) {
                    if (userName.size() > 0) {
                        userName.resize(userName.size() - 1);
                    }
                }
                else {
                    userName += wchar_t(event.text.unicode);
                }
                textUser.setString(L"Имя пользователя: " + userName);
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {


                if (isBW) {
                    bw.setFillColor(Color::Black);
                    theme = L"BlackWhite";
                }

                if (isDefault) {
                    textDefault.setFillColor(Color::Black);
                    theme = L"Default";
                }

                if (isExit) {
                    windowDaugth.close();
                }

                if (save && userName != "") {

                    wofstream output("user.txt");
                    output << L"Name:" << userName << L"|";
                    output << L"Theme:" << theme;

                    output.close();
                    windowDaugth.close();
                }
            }
        }
        windowDaugth.clear();
        windowDaugth.draw(fons);
        windowDaugth.draw(bw);
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
    pauseOption.setDelayTime(clock());
    Texture fon;
    fon.loadFromFile("images/fon2.jpg");
    Sprite fons(fon);


    sf::RenderWindow windowDaugth(sf::VideoMode(960, 600), "Checkers");
    sf::Font font1;
    font1.loadFromFile("Font//Deutsch Gothic.ttf");
    sf::Font font2;
    font2.loadFromFile("Font//Bahnschrift.ttf");

    sf::Text textStart(L"Вы хотите выйти?", font1, 35);
    textStart.setFillColor(sf::Color::Black);
    textStart.setStyle(sf::Text::Bold);
    textStart.setPosition(200, 150);

    bool stay = false;
    sf::Text yes(L"Да", font2, 23);
    yes.setFillColor(sf::Color::Black);
    yes.setOutlineColor(sf::Color::White);
    yes.setOutlineThickness(1);
    yes.setStyle(sf::Text::Bold);
    yes.setPosition(170, 210);

    bool leave = false;
    sf::Text no(L"Нет", font2, 23);
    no.setFillColor(sf::Color::Black);
    no.setOutlineColor(sf::Color::White);
    no.setOutlineThickness(1);
    no.setStyle(sf::Text::Bold);
    no.setPosition(170, 260);

    while (windowDaugth.isOpen())
    {
        sf::Event event;
        while (windowDaugth.pollEvent(event))
        {
            if (IntRect(170, 210, 70, 30).contains(Mouse::getPosition(windowDaugth))) {
                yes.setFillColor(sf::Color::Color(165, 70, 0));
                leave = true;
            }
            else {
                yes.setFillColor(sf::Color::Black);
                leave = false;
            }

            if (IntRect(170, 260, 70, 30).contains(Mouse::getPosition(windowDaugth))) {
                no.setFillColor(sf::Color::Color(165, 70, 0));
                stay = true;
            }
            else {
                no.setFillColor(sf::Color::Black);
                stay = false;
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (leave) {
                    windowDaugth.close();
                    pauseOption.setOption(4);
                    window.close();
                }

                if (stay) {
                    windowDaugth.close();
                    pauseOption.setTime(pauseOption.getTime() + clock() - pauseOption.getDelayTime());
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

void Pause(sf::RenderWindow& window) {
    window.setActive(false);
    pauseOption.setDelayTime(clock());
    Texture fon;
    fon.loadFromFile("images/fon5.jpg");
    Sprite fons(fon);


    sf::RenderWindow windowDaugth(sf::VideoMode(960, 600), "Checkers");
    sf::Font font1;
    font1.loadFromFile("Font//Deutsch Gothic.ttf");
    sf::Font font2;
    font2.loadFromFile("Font//bahnschrift.ttf");

    sf::Text textStart(L"Пауза", font1, 35);
    textStart.setFillColor(sf::Color::Black);
    textStart.setStyle(sf::Text::Bold);
    textStart.setPosition(350, 150);

    bool stay = false;
    sf::Text yes(L"Вернуться", font2, 23);
    yes.setFillColor(sf::Color::Black);
    yes.setStyle(sf::Text::Bold);
    yes.setOutlineColor(sf::Color::White);
    yes.setOutlineThickness(1);
    yes.setPosition(170, 200);

    bool leave = false;
    sf::Text no(L"Выйти в меню", font2, 23);
    no.setFillColor(sf::Color::Black);
    no.setOutlineColor(sf::Color::White);
    no.setOutlineThickness(1);
    no.setStyle(sf::Text::Bold);
    no.setPosition(170, 250);

    bool restart = false;
    sf::Text res(L"Рестарт", font2, 23);
    res.setFillColor(sf::Color::Black);
    res.setOutlineColor(sf::Color::White);
    res.setOutlineThickness(1);
    res.setStyle(sf::Text::Bold);
    res.setPosition(170, 300);

    while (windowDaugth.isOpen())
    {
        sf::Event event;
        while (windowDaugth.pollEvent(event))
        {
            if (IntRect(170, 200, 120, 30).contains(Mouse::getPosition(windowDaugth))) {
                yes.setFillColor(sf::Color::Color(160, 70, 0));
                leave = true;
            }
            else {
                yes.setFillColor(sf::Color::Black);
                leave = false;
            }

            if (IntRect(170, 250, 170, 30).contains(Mouse::getPosition(windowDaugth))) {
                no.setFillColor(sf::Color::Color(160, 70, 0));
                stay = true;
            }
            else {
                no.setFillColor(sf::Color::Black);
                stay = false;
            }
            if (IntRect(170, 300, 150, 30).contains(Mouse::getPosition(windowDaugth))) {
                res.setFillColor(sf::Color::Color(160, 70, 0));
                restart = true;
            }
            else {
                res.setFillColor(sf::Color::Black);
                restart = false;
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (leave) {
                    windowDaugth.close();
                    pauseOption.setOption(1);
                    pauseOption.setTime(pauseOption.getTime() + clock() - pauseOption.getDelayTime()); 
                    return;
                }

                if (stay) {
                    pauseOption.setOption(0);
                    window.close();
                    windowDaugth.close();
                    menu();
                }
                if (restart) {
                    windowDaugth.close();
                    pauseOption.setOption(2);
                    playGame(window);
                }
            }

        }
        windowDaugth.clear();
        windowDaugth.draw(fons);
        windowDaugth.draw(textStart);
        windowDaugth.draw(yes);
        windowDaugth.draw(no);
        windowDaugth.draw(res);
        windowDaugth.display();
    }
}

void playGame(sf::RenderWindow& window) {
    wifstream input("user.txt");
    wstring bulk;
    getline(input, bulk);
    int theme;
    input.close();

    int index = bulk.rfind(':') + 1;
    if (bulk[index] == 'D') {
        theme = 0;
    }
    else {
        theme = 1;
    }
    
    Game game;
    bool start = 1;

    ifstream in("gameSettings.txt");
    string str;
    in >> str;
    in.close();


    pauseOption.setTime(clock());

    while (window.isOpen() && str != "") {
        game.assignValuesFromFile("gameSettings.txt");
        game.assignRegimeFromFile("regime.txt");
        Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.setActive(false);
                sf::Thread newPollThread(ExitFunc, std::ref(window));
                newPollThread.launch();
                newPollThread.wait();
                window.setActive();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.setActive(false);
                Pause(window);

                window.setActive();
                switch (pauseOption.getOption()) {
                case 0:
                {
                    pauseOption.setOption(4);
                    window.close();
                    return;
                    break;
                }
                case 1:
                {

                    break;
                }
                }
            }

            ofstream out("ligth.txt");
            out << game.getAmountSteps() << "|" << game.getColor() << "|" << game.getMode();
            out.close();

            game.set_who_can_move();
            if(((game.getWhoCanMove() == 0 && game.getColor() == "black") || 
                (game.getWhoCanMove() == 1 && game.getColor() == "white")) && game.getRegime() == "Computer")
            {
                game.bot_make_move();
            }

            else
            {
                game.make_move(window, event);
            }
        }

        if (theme == 0) {
            window.clear(Color(245, 210, 175));
        }
        else {
            window.clear(Color(110, 110, 110));
        }

        if (start) {
            game.start_game(window, event, start);
        }

        ifstream in("ligth.txt");

        std::string raw_result;
        in >> raw_result;
        in.close();
        size_t first = raw_result.find('|');
        size_t second = raw_result.find('|', first + 1);
        int i = 0;
        std::string temp;
        while (i < first)
        {
            temp += raw_result[i];
            i++;
        }

        string amountSteps = temp;
        temp = "";
        i = first + 1;
        while (i < second)
        {
            temp += raw_result[i];
            i++;
        }

        string masterColor = temp;
        temp = "";
        i = second + 1;
        while (i < raw_result.size())
        {
            temp += raw_result[i];
            i++;
        }
        string regime = temp;
        bool master = false;
        if (regime != "Checkers") {
            if (stoi(amountSteps) % 2 == 1 && masterColor == "white") {
                master = true;
            }
            else if (stoi(amountSteps) % 2 == 1 && masterColor == "black") {
                master = false;
            }
            else if (stoi(amountSteps) % 2 == 0 && masterColor == "black") {
                master =true;
            }
            else {
                master = false;
            }
        }
        else {
            if (stoi(amountSteps) % 2 == 1 && masterColor == "black") {
                master = true;
            }
            else if (stoi(amountSteps) % 2 == 0 && masterColor == "black") {
                master = false;
            }
            else if (stoi(amountSteps) % 2 == 1 && masterColor == "white") {
                master = false;
            }
            else {
                master = true;
            }
        }

        if (game.end_game(window, event))
            if (game.getMode() == "International")
                game.get_checkers_on_board_inter().draw_checkers(window, pauseOption.getTime(), master);//рисую поле и шашки для международного режима
            else
                game.get_checkers_on_board().draw_checkers(window, pauseOption.getTime(), master);
        else
            game.end_game(window, event);//рисую если конец игры

        window.display();
    }
}

void menu()
{
    RenderWindow window(sf::VideoMode(960, 600), "Checkers");
    Texture fon;
    fon.loadFromFile("images/fon1.jpg");

    Sprite fons(fon);

    Font font1;
    font1.loadFromFile("Font//Deutsch Gothic.ttf");
    Font font2;
    font2.loadFromFile("Font//bahnschrift.ttf");

    sf::Text textStart(L"Шашки by AkTeam", font1, 35);
    textStart.setFillColor(sf::Color::Black);
    textStart.setStyle(sf::Text::Bold);
    textStart.setPosition(300, 50);


    bool isReadyOptions = false;
    sf::Text textInstr(L"Выбор режима и старт игры", font2, 23);
    textInstr.setFillColor(sf::Color::Black);
    textInstr.setOutlineColor(sf::Color::White);
    textInstr.setOutlineThickness(1);
    textInstr.setStyle(sf::Text::Bold);
    textInstr.setPosition(150, 100);

    bool isReadyUserSettings = false;
    sf::Text textUserName(L"Настройки", font2, 23);
    textUserName.setFillColor(sf::Color::Black);
    textUserName.setOutlineColor(sf::Color::White);
    textUserName.setOutlineThickness(1);
    textUserName.setStyle(sf::Text::Bold);
    textUserName.setPosition(150, 150);

    bool isExit = false;
    sf::Text textExit(L"Выход", font1, 23);
    textExit.setFillColor(sf::Color::Red);
    textExit.setOutlineColor(sf::Color::White);
    textExit.setOutlineThickness(1);
    textExit.setStyle(sf::Text::Bold);
    textExit.setPosition(150, 220);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            wifstream input("user.txt");
            wstring bulk;
            getline(input, bulk);
            int theme;
            input.close();

            int index = bulk.rfind(':') + 1;
            if (bulk[index] == 'D') {
                theme = 0;
            }
            else {
                theme = 1;
            }

            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {

                window.setActive(false);
                sf::Thread newPollThread(ExitFunc, std::ref(window));
                newPollThread.launch();
                newPollThread.wait();
                window.setActive();
                isReadyOptions = false;
                isReadyUserSettings = false;
                isExit = false;
            }

            if (IntRect(150, 100, 300, 20).contains(Mouse::getPosition(window))) {
                textInstr.setFillColor(sf::Color::Color(165, 70, 0));
                isReadyOptions = true;
            }
            else {
                textInstr.setFillColor(sf::Color::Black);
                isReadyOptions = false;
            }

            if (IntRect(150, 150, 300, 20).contains(Mouse::getPosition(window))) {
                textUserName.setFillColor(sf::Color::Color(165, 70, 0));
                isReadyUserSettings = true;
            }
            else {
                textUserName.setFillColor(sf::Color::Black);
                isReadyUserSettings = false;
            }

            if (IntRect(150, 220, 300, 20).contains(Mouse::getPosition(window))) {
                textExit.setFillColor(sf::Color::Color(165, 70, 0));
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
                    wofstream output("regime.txt");
                    output << "";
                    output.close();
                    ofstream ouT("ligth.txt");
                    ouT << "";
                    ouT.close();
                    window.setActive(false);
                    sf::Thread newPollThread(InstructionSettings, std::ref(window));
                    newPollThread.launch();
                    newPollThread.wait();
                    window.setActive();
                    ofstream iN("score.txt");
                    iN << "";
                    iN.close();

                    playGame(window);
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

    if (pauseOption.getOption() == 0) {
        window.close();
        return;
    }
}
