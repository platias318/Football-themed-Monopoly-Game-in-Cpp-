#include "game.h"
#include "defines.h"
#include <sgg/graphics.h>
#include <string>
#include "menu.h"
#include "player.h";
#include "Dice.h"
#include "event.h"
#include <iostream>

Game::~Game()
{

    for (auto player : m_players) {
        delete player;
    }
    for (auto card : m_cards) {
        delete card;
    }
    for (auto event : m_events) {
        delete event;
    }
    delete Menu;
    delete dice;
}


void Game::draw()
{
    graphics::Brush br;
    if (m_state == STATE_INIT) {
        drawInitScreen();//calls the specific method for drawing the init state screen
        return;
    }
    if (m_state == STATE_LOADING) {
        drawLoadingScreen();//calls the specific method for drawing the loading state screen
        return;

    }

    if (m_state == STATE_IDLE) {
        drawMainScreen();//calls the specific method for drawing the main state screen
        return;
    }

    if (m_state == STATE_PAUSED) {
        drawMainScreen();//calls the specific method for drawing the paused-menu pop state screen
        return;
    }

    if (m_state == STATE_PLAYING) {
        drawPlayingScreen();//calls the specific method for drawing the playing state screen
        return;
    }
    if (m_state == STATE_DONE) {
        drawEndScreen();//calls the specific method for drawing the ending state screen
        return;
    }
}

void Game::update()
{
    if (m_state == STATE_PAUSED) {
        updateStopScreen();//calls the method that updates the paused state-the state when the menu is pressed
        return;
    }



    if (m_state == STATE_INIT) {//calls the method that updates the init state
        updateInitScreen();
        return;
    }

    if (m_state == STATE_LOADING) {//calls the method that updates the loading state
        updateLoadingScreen();
        return;
    }

    if (m_state == STATE_IDLE) {//calls the method that updates the idle state
        updateMainScreen();
        return;
    }

    if (m_state == STATE_PLAYING) {//calls the method that updates the playing state
        updatePlayingScreen();
        if (m_players.size() == 1) { m_state = STATE_DONE; sleep(1000); }
        return;
    }
    if (m_state == STATE_DONE) {//calls the method that updates the ending state
        updateEndScreen();
        return;
    }
}

void Game::drawInitScreen() {
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    graphics::setFont(std::string(ASSET_PATH) + "Text2.ttf");
    br.texture = ASSET_PATH + std::string("Loading.png");
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawText(230, 280, 55, "Press Space", br);
    graphics::drawText(350, 370, 65, "OR", br);
    graphics::drawText(230, 450, 60, "Left click ", br);
}


void Game::drawLoadingScreen() {
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    br.texture = ASSET_PATH + std::string("Loading.png");
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    br.outline_opacity = 0.0f;
    p1Button->draw();
    p2Button->draw();
    graphics::drawText(100, 300, 35, "Choose the number of players", br);
    if (p1Button->isPressed()||p2Button->isPressed()) {
        graphics::drawText(100, 530, 35, "Write their names to Continue", br);
    }
}


void Game::drawMainScreen(){
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    br.texture = ASSET_PATH + std::string("MAIN.png");
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    startButton->draw();

    Menu->draw();
}

void Game::drawPlayingScreen() {
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    br.texture = ASSET_PATH + std::string("MAIN.png");
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    Menu->draw();
    for (auto player : m_players) {
        player->draw();}

    graphics::Brush br5;
    SETCOLOR(br5.fill_color, 1.49f, 2.03f, 0.64f);
    graphics::setFont(std::string(ASSET_PATH) + "Brick Comic.ttf");

    if (m_active_player != nullptr) {
        std::string x = std::string("Playing: ") + std::string(m_active_player->getName());
        graphics::drawText(CANVAS_WIDTH / 2.8, CANVAS_HEIGHT - 170, 35, x, br5);}

    dice->draw();

    if (m_active_player && m_active_player->hasRolled() && dice->isPressed() && m_active_player->Played() == false) {
        dice->drawDiceNumber(dice->getNumber());}

    for (auto card : m_cards) {
        card->draw();}

    if (m_active_player && m_active_player->hasRolled() && m_active_player->Played() == false && m_active_card && m_active_card->getOwner() == nullptr && m_active_card->getNum() != 1 && m_active_card->getNum() != 7 && m_active_card->getNum() != 19 && m_active_card->getNum() != 13) {
        buyButton->draw();}

    if (m_active_player && m_active_player->hasRolled() && m_active_player->Played() == false && m_active_card && (m_active_card->getOwner() == nullptr || m_active_card->getOwner() == m_active_player)) {
        skipButton-> draw();}

    if (m_active_player && m_active_player->hasRolled() && m_active_player->Played() == false && m_active_card && m_active_card->getOwner() != nullptr && m_active_card->getOwner() != m_active_player) {
        payButton->draw();}

    for (auto ev : m_events) {
        ev->draw();}
}

void Game::drawEndScreen() {
    graphics::Brush br;
    br.outline_opacity = 0.0f;
    graphics::setFont(ASSET_PATH + std::string("Brick Comic.ttf"));
    SETCOLOR(br.fill_color, 0.96f, 0.0f, 0.0f);
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
    SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
    graphics::drawText(CANVAS_WIDTH / 4.5, CANVAS_HEIGHT / 8, 45, std::string(m_players.front()->getName()) + " Won the game!", br);
    graphics::setFont(ASSET_PATH + std::string("Text2.ttf"));
    graphics::drawText(CANVAS_WIDTH / 4.5, CANVAS_HEIGHT / 1.10, 40, "Press  R  to Restart", br);

    graphics::Brush br1;
    br1.outline_opacity = 0.0f;
    br1.texture = ASSET_PATH + std::string("game-over.png");
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 1.5, CANVAS_HEIGHT / 1.5, br1);
}



void Game::updateInitScreen() {
    graphics::MouseState ms;
    graphics::getMouseState(ms);
    if (graphics::getKeyState(graphics::SCANCODE_SPACE) || ms.button_left_released) {
        m_state = STATE_LOADING;}
}

void Game::updateLoadingScreen() {
    p1Button->update();
    p2Button->update();
    if (p1Button->isPressed()) {
        m_num_players = 2;
        return;}
    else if (p2Button->isPressed()) {
        m_num_players = 3;
        return;}
    if (m_num_players == 0) {
        return;}

    init();
    m_state = STATE_IDLE;
}

void Game::init()
{//----creates all the cards and players used for the game!!!-----------------
    CreatePremierLeagueTeams();
    CreateSerieATeams();
    CreateSuperLeagueTeams();
    CreateLaLigaTeams();
    CreateSpecialCards();

   
    std::string name;
    for (int i = 0; i < m_num_players; i++) {
        std::cout << "\nWrite the name of player " << i + 1 <<":"<< std::endl;
        std::cin >> name;
        Player* p = new Player(name);
        p->setPosX(50 + i * 37);
        p->setPosY(45);
        m_players.push_back(p);
    }
    graphics::preloadBitmaps(ASSET_PATH);
    graphics::playMusic(std::string(ASSET_PATH) + "GameMusic.mp3", 0.1f, true);
}
//------------------------------------------------------------------


void Game::updateMainScreen() {
      updatePlayerMovement();
    Menu->update();
    if (Menu->isPressed()) {
        m_previous_state = m_state;
        m_state = STATE_PAUSED;
        return;}

     dice->update();
     startButton->update();

    if (startButton->isPressed()) {
        m_state = STATE_PLAYING;
        return;}
}

void Game::updateStopScreen() {
    Menu->update();
    if (Menu->getMenuSelection() == menu::menu_selection::RESUME) {
        m_state = m_previous_state;
        Menu->setPressed(false);
        Menu->setMenuSelection(menu::menu_selection::UNPRESSED);
        return;}

    else if (Menu->getMenuSelection() == menu::menu_selection::RESTART) {
        m_state = STATE_LOADING;
        Game::releaseInstance();
        Menu->setPressed(false);
        Menu->setMenuSelection(menu::menu_selection::UNPRESSED);
        return;}

    else if (Menu->getMenuSelection() == menu::menu_selection::RULES) {
        if (graphics::getKeyState(graphics::SCANCODE_TAB)) {
            m_state = m_previous_state;
            Menu->setMenuSelection(menu::menu_selection::UNPRESSED);
            return;}
    }

    else if (Menu->getMenuSelection() == menu::menu_selection::EXIT) {
        graphics::stopMessageLoop();
        Menu->setPressed(false);
        Menu->setMenuSelection(menu::menu_selection::UNPRESSED);
        return;}
}

void Game::updatePlayingScreen() {
    processEvents();
    updatePlayerMovement();

    Menu->update();
    if (Menu->isPressed()) {
        m_previous_state = m_state;
        m_state = STATE_PAUSED;
        return;}

    graphics::MouseState ms;
    graphics::getMouseState(ms);
    dice->update();
    if (dice->getHighlighted() && m_active_player && ms.button_left_pressed) {
        dice->setPressed(true);}

    if (dice->isPressed() && m_active_player && m_active_player->Played() == false && m_active_player->hasRolled() == false) {
        dice->setNumber(RAND1TO6());
        m_active_player->setRolled(true);
        return;}

    if (m_active_player && m_active_player->hasRolled() == true && m_active_player->hasMoved() == false) {
        for (auto card : m_cards) {
            card->PlayersOn.remove(m_active_player);
        }
        for (auto card : m_cards) {
            int  sum = dice->getNumber() + m_active_player->getCurrPos();
            if (sum > 24) { sum = sum - 24; }
            if (sum == card->getNum()) {
                if (card->getName() == std::string("GO TO PRISON")) {

                    m_active_player->setMoney(m_active_player->getMoney() - 30); // if someone goes in prison , he losses 30 euros
                    m_active_player->setCurrPos(19);

                    float x_in = m_active_player->getPosX();
                    float y_in = m_active_player->getPosY();
                    float x_out = 736.41;
                    float y_out = 46.0;

                    addEvent(new PlayerMotionEvent(x_in, y_in, x_out, y_out, m_active_player));
                    m_active_card = card;
                    m_active_player->setMoved(true);
                    break;
                }else {
                    m_active_player->setCurrPos(card->getNum());
                    if (!card->PlayersOn.empty()) {

                        float x_in = m_active_player->getPosX();
                        float y_in = m_active_player->getPosY();
                        float x_out = card->getPosX() + 20 - (card->PlayersOn.size() - 1) * 50;
                        float y_out = card->getPosY() + 30 - (card->PlayersOn.size() - 1) * 30;

                        addEvent(new PlayerMotionEvent(x_in, y_in, x_out, y_out, m_active_player));
                    }else {
                        m_active_player->setCurrPos(card->getNum());

                        float x_in = m_active_player->getPosX();
                        float y_in = m_active_player->getPosY();
                        float x_out = card->getPosX();
                        float y_out = card->getPosY();

                        addEvent(new PlayerMotionEvent(x_in, y_in, x_out, y_out, m_active_player));}

                    card->PlayersOn.push_back(m_active_player);
                    m_active_card = card;
                    m_active_player->setMoved(true);
                    break;
                }
            }
        }
    }
    buyButton->update();
    skipButton->update();
    payButton->update();

    if (buyButton->isPressed()) {
        if (m_active_player->getMoney() >= m_active_card->getPrice() && m_active_card->getOwner() == nullptr) {
            m_active_card->setOwner(m_active_player);
            m_active_player->m_cards.push_back(m_active_card);
            m_active_player->setMoney(m_active_player->getMoney() - m_active_card->getPrice());
           buyButton->setPressed(false);
            dice->setPressed(false);
            m_active_player->setPlayed(true);
            char info[40];
            sprintf_s(info, "%.2lf", m_active_card->getPrice());
            addEvent(new GameMessages(m_active_player, m_active_card, std::string(m_active_player->getName()) + " bought  " + std::string(m_active_card->getName() + " for " + info)));
            return;
        }else if (m_active_player->getMoney() < m_active_card->getPrice() && m_active_card->getOwner() == nullptr) {
            addEvent(new GameMessages(m_active_player, m_active_card, std::string(m_active_player->getName() + " is too low on cash")));
            buyButton->setPressed(false);
            m_active_player->setPlayed(true);
            dice->setPressed(false);
            return;
        }

    }else if (skipButton->isPressed()) {
        addEvent(new GameMessages(m_active_player, m_active_card, std::string("           " + m_active_player->getName() + "  skipped")));
        dice->setPressed(false);
        skipButton->setPressed(false);
        m_active_player->setPlayed(true);
        return;

    }else if (payButton->isPressed()) {
        m_active_player->setMoney(m_active_player->getMoney() - m_active_card->getRent());
        if (m_active_player->getMoney() <= 0) {
            addEvent(new GameMessages(m_active_player, m_active_card, std::string(m_active_player->getName() + " has  been   removed!")));
            m_active_player->setPlayed(true);
            dice->setPressed(false);
            payButton->setPressed(false);
            m_players.remove(m_active_player);
            return;

        }else {
            m_active_card->getOwner()->setMoney(m_active_card->getOwner()->getMoney() + m_active_card->getRent());
            char info[40];
            sprintf_s(info, "%.2lf", m_active_card->getRent());
            addEvent(new GameMessages(m_active_player, m_active_card, std::string(m_active_player->getName() + " paid " + std::string(info) + " to " + m_active_card->getOwner()->getName())));
            dice->setPressed(false);
            payButton->setPressed(false);
            m_active_player->setPlayed(true);
            return;
        }
    }
}

void Game::updatePlayerMovement() {
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);
    m_current = nullptr;
    for (auto player : m_players){
        if (player->contains(mx, my) && m_current == nullptr) {
            player->setHighlighted(true);
            m_current = player;
        }else {
            player->setHighlighted(false);
        }
    }
    for (auto player : m_players) {
        if (player->getHighlighted() && ms.button_left_pressed) {
            if (m_active_player == nullptr) {
                player->setActive(true);
                m_active_player = player;
            }else if (m_active_player && m_active_player->Played() && m_active_player != player) {
                player->setActive(true);
                m_active_player->setRolled(false);
                m_active_player->setPlayed(false);
                m_active_player->setMoved(false);
                m_active_player = player;
            }
        }else {
            player->setActive(false);
        }
    }
    graphics::MouseState ms1;
    graphics::getMouseState(ms1);
    for (auto player : m_players) {
        if (ms1.button_right_pressed && ms1.button_left_pressed == false && m_current == player) {
            if (player->getCurrPos() >= 1 && player->getCurrPos() < 7) {//if the right click was pressed AND his piece is on the left position of the table
                addEvent(new PlayerScoreEvent(player->getPosX() + 20, player->getPosY() - 20, player));

            }else if (player->getCurrPos() >= 7 && player->getCurrPos() <= 13) {//if the right click was pressed AND his piece is on the bottom dwon position of the table
                addEvent(new PlayerScoreEvent(player->getPosX() - 88, player->getPosY() - 120, player));

            }else if (player->getCurrPos() > 13 && player->getCurrPos() <= 19) {//if the right click was pressed AND his piece is on the right position of the table
                addEvent(new PlayerScoreEvent(player->getPosX() - 250, player->getPosY() + 20, player));

            }else {                                                                 //if the right click was pressed AND his piece is on the upper position of the table
                addEvent(new PlayerScoreEvent(player->getPosX() - 100, player->getPosY() + 68, player));
            }
        }
    }
}

void Game::updateEndScreen(){
    if (graphics::getKeyState(graphics::SCANCODE_R)) {
        m_state = STATE_LOADING;
        Game::releaseInstance();
        return;}
}



void Game::CreateLaLigaTeams(){//--------------------------------creates all the laliga teams----------------------------------------------------------
    GameCards::Color  y = GameCards::Color::yellow;
    int price = 300;
    int rent = 40;
    GameCards* g1 = new GameCards(std::string("Real Madrid"), y, price, rent, 736, 150.8, 18);
    m_cards.push_front(g1);
    GameCards* g2 = new GameCards(std::string("Barcelona"), y, price, rent, 736.0, 548, 14);
    m_cards.push_front(g2);
    GameCards* g3 = new GameCards(std::string("Bilbao"), y, price, rent, 399, 26.11, 22);
    m_cards.push_front(g3);
    GameCards* g4 = new GameCards(std::string("Atletico"), y, price, rent, 488.8, 644.2, 11);
    m_cards.push_front(g4);
    GameCards* g5 = new GameCards(std::string("Betis"), y, price, rent, 736.0, 454.0, 15);
    m_cards.push_front(g5);
}

void Game::CreatePremierLeagueTeams(){//----------------------creates all the Premier League teams--------------------------------------------------------
    GameCards::Color  b = GameCards::Color::red;
    int price = 350;
    int rent = 50;
    GameCards* g1 = new GameCards(std::string("Arsenal"), b, price, rent, 52.3, 156.2, 2);
    m_cards.push_front(g1);
    GameCards* g2 = new GameCards(std::string("West Ham"), b, price, rent, 52.4, 543.2, 6);
    m_cards.push_front(g2);
    GameCards* g3 = new GameCards(std::string("Man City"), b, price, rent, 376.4, 644.2, 10);
    m_cards.push_front(g3);
    GameCards* g4 = new GameCards(std::string("Chelsea"), b, price, rent, 736.0, 250.44, 17);
    m_cards.push_front(g4);
    GameCards* g5 = new GameCards(std::string("Man U"), b, price, rent, 503.0, 26.11, 21);
    m_cards.push_front(g5);
}

void Game::CreateSuperLeagueTeams(){//-------------------------creates all the SuperLeague teams----------------------------------------------------------
    GameCards::Color  g = GameCards::Color::green;
    int price = 200;
    int rent = 40;

    GameCards* g1 = new GameCards(std::string("Olympiakos"), g, price, rent, 52.4, 358, 4);
    m_cards.push_front(g1);
    GameCards* g2 = new GameCards(std::string("PAO"), g, price, rent, 607, 644.2, 12);
    m_cards.push_front(g2);
    GameCards* g3 = new GameCards(std::string("Paok"), g, price, rent, 302, 26.11, 23);
    m_cards.push_front(g3);
    GameCards* g4 = new GameCards(std::string("Aek Ath"), g, price, rent, 188.4, 644.2, 8);
    m_cards.push_front(g4);
    GameCards* g5 = new GameCards(std::string("Pas"), g, price, rent, 52.4, 459.3, 5);
    m_cards.push_front(g5);
}

void Game::CreateSerieATeams(){//-------------------------------creates all the SerieA teams-----------------------------------------------------------------
    GameCards::Color  r = GameCards::Color::red;
    int price = 250;
    int rent = 40;

    GameCards* g1 = new GameCards(std::string("Milan"), r, price, rent, 52.3, 247.7, 3);
    m_cards.push_front(g1);
    GameCards* g2 = new GameCards(std::string("Inter"), r, price, rent, 736.0, 355.3, 16);
    m_cards.push_front(g2);
    GameCards* g3 = new GameCards(std::string("Samptoria"), r, price, rent, 199, 26.11, 24);
    m_cards.push_front(g3);
    GameCards* g4 = new GameCards(std::string("Udineze"), r, price, rent, 617.7, 26.11, 20);
    m_cards.push_front(g4);
    GameCards* g5 = new GameCards(std::string("AS Roma"), r, price, rent, 281.3, 644.2, 9);
    m_cards.push_front(g5);
}



void Game::CreateSpecialCards(){//--------------------------------creates All the special cards----------------------------------------------------
    GameCards* g1 = new GameCards(std::string("START"), GameCards::Color::orange, 0, 0, 68.3, 46.0, 1);
    m_cards.push_front(g1);
    GameCards* g2 = new GameCards(std::string("FREE PASS"), GameCards::Color::orange, 0, 0, 72, 626.4, 7);
    m_cards.push_front(g2);
    GameCards* g3 = new GameCards(std::string("GO TO PRISON"), GameCards::Color::orange, 0, 0, 736.41, 654.0, 13);
    m_cards.push_front(g3);
    GameCards* g4 = new GameCards(std::string("PRISON"), GameCards::Color::orange, 0, 0, 736.41, 48.0, 19);
    m_cards.push_front(g4);
}
void Game::processEvents()
{
    for (auto e : m_events) {
        e->update();
    }
    m_events.remove_if([](Event* ev) {return !ev->active(); });
}

void Game::addEvent(Event* ev)
{
    m_events.push_front(ev);
}

Game* Game::getInstance()//dimiourgei ena instance MIA kai MONADIKI fora, kai mono apo edw pairnw 
{
    if (!m_instance)
        m_instance = new Game();
    return m_instance;
}

Game* Game::m_instance = nullptr;
