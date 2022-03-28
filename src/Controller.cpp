#include "Controller.h"

Controller::Controller()//Controller constructor 
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP), "Dangerous Dave", sf::Style::Titlebar | sf::Style::Close),
    m_numOfLevel(FIRSTLEVEL), m_currentView(0, m_window.getSize().y / 2), m_menu(STARTM), m_duringMenu(DURINGM)
    , m_gameoverMenu(GAMEOVERM), m_exitMenu(false), m_levelended(false)
{
    m_window.setFramerateLimit(60);
    m_board = std::make_unique<Board>();
    m_playerView.reset(sf::FloatRect(0, 0, m_window.getSize().x, m_window.getSize().y));
    m_playerView.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));
    m_stats = std::make_unique<Stats>();
    m_gameoverStats = std::make_unique<Stats>();
    m_bar = std::make_unique<JetBar>();
    m_help.setTexture(Textures::instance().getTexture(HELP));
    m_help.setScale((WINDOW_WIDTH / 1.25) / m_help.getGlobalBounds().width,
        (WINDOW_HEIGHT / 1.25) / m_help.getGlobalBounds().height);
}//end Controller constructor

void Controller::run()
{
    runMenu();
}//end run

void Controller::runGame()
{
    clocksResrtart();
    while (m_window.isOpen())
    {
        this->handleView();
        this->draw();
        gameEventHandle();//handle keyboard and mouse events
        m_board->enemyShoot(m_enemyShot);
        m_board->update(m_move.restart().asSeconds());
        if (m_board->getPlayer().getVelocity().y > 0)
            m_board->getPlayer().setAbleToJump(false);
        m_board->updateJetTime(m_jet, *m_bar, m_currentView);
        m_board->handleCollisions();
        m_board->addDeads();
        m_board->deleteNeed2BDeleteObjects();
        this->checkLevelFinish();//check if level finish
    }
}//end runGame

void Controller::draw()
{
    m_window.clear();
    m_board->draw(m_window);
    m_stats->updateData(sf::Vector2f(m_currentView.x, m_currentView.y),
        m_board->getPlayer().getScore(), m_numOfLevel,
        m_board->getPlayer().getLives(), m_board->getPlayer().getGotTrophy(),
        m_board->getPlayer().getGun(), m_board->getPlayer().getJet(), false, true);
    m_stats->draw(m_window);
    if (m_board->getPlayer().getJet() && !m_bar->isEmpty())
    {
        m_bar->setposition(m_currentView);
        m_bar->draw(m_window);
    }
    m_window.display();
}//end draw

void Controller::handleView()
{//set the view by the player posision
    if (m_board->getPlayer().getPosition().x + 10.f > m_window.getSize().x / 2)
    {
        if (m_board->getPlayer().getPosition().x < WINDOW_LONG)
            m_currentView.x = m_board->getPlayer().getPosition().x + 10;
        else
            m_currentView.x = WINDOW_LONG;
    }
    else
        m_currentView.x = (float)m_window.getSize().x / 2;
    m_playerView.setCenter(m_currentView);
    m_window.setView(m_playerView);
}//end handleView

void Controller::runMenu()
{//print menu,and wait until user press button
    while (m_window.isOpen())
    {
        m_window.clear();
        m_menu.draw(m_window);
        m_window.display();
        menuEventHandle(m_menu);
    }
}//end runMenu

void Controller::menuDuring()
{//print menu during the game 
    Sounds::instance().stopPlaying(true);
    m_duringMenu.updatePosition(sf::Vector2f(m_currentView.x - 700.f, 0));
    while (m_window.isOpen())
    {
        m_window.clear();
        m_board->draw(m_window);//for gameboard to draw on the menu background
        m_stats->draw(m_window);
        m_duringMenu.draw(m_window);
        m_window.display();
        menuEventHandle(m_duringMenu);
        if (m_exitMenu)//if we press on RESUME button we want to exit menu
        {              //end back to the game
            m_exitMenu = false;
            return;
        }
    }
}//end menuDuring

void Controller::runGameoverMenu(gameStatus status)
{//status is whether gameover due to finish game or due to player 'died'
    if (status)
        --m_numOfLevel;//because we try to load a new level we add 1 to num of level, and only while it's failed
                       //we finish game successfully, so need to reduce 1 from the num of level to get the curect level.
    m_gameoverMenu.setDrawBackground(status);
    m_gameoverStats->updateData(sf::Vector2f(m_currentView.x, m_currentView.y),
        m_board->getPlayer().getScore(), m_numOfLevel, m_board->getPlayer().getLives(), false, false, false, true, false);
    m_gameoverMenu.updatePosition(sf::Vector2f(m_currentView.x - 850.f, 0));
    m_gameoverStats->setGameoverStatus(status);
    while (m_window.isOpen())
    {
        m_window.clear();
        m_board->draw(m_window);
        m_gameoverMenu.draw(m_window);
        m_gameoverStats->draw(m_window);
        m_window.display();
        this->menuEventHandle(m_gameoverMenu);
        if (m_exitMenu)
        {//if we press 'Resume' we just want to exit menu
            m_exitMenu = false;
            this->clocksResrtart();
            return;
        }
    }
}//end runGameoverMenu

void Controller::checkLevelFinish()
{
    //when player 'dead' if left some life, restart level.
     //otherwise gameover with strike(failed)
    if (m_board->getPlayer().getDead())
    {
        m_board->getPlayer().playerDied();
        while (!m_board->hasDeadObjEnded())
        {
            m_board->update();
            this->draw();
        }
        if (m_board->getPlayer().getLives() == 0)
            this->runGameoverMenu(Failed);//when life = 0, game over (failed)
        this->restartLevel();//if left some life, restart level
    }
    else if (m_board->getPlayer().isLevelFinished())
    {//if the player finish successfully the level
        int lives = m_board->getPlayer().getLives();
        int score = m_board->getPlayer().getScore();
        m_board->clearVectors();
        if (!m_board->loadLevel(++m_numOfLevel, true))//try to load new level, if no new level left
            this->runGameoverMenu(Finish);            //successfully finish game, so game over successfully
        else//load the next level
        {
            m_bar = std::make_unique<JetBar>();
            m_board->getPlayer().setLives(lives);
            m_board->getPlayer().setScore(score);
        }
    }
    m_board->hasDeadObjEnded();
}//end checkLevelFinish

void Controller::restartLevel()
{
    m_board->restartLevel();
    this->clocksResrtart();
}//end restartLevel

void Controller::restartGame()
{//start a new game(start the over from beginning)
    m_board->clearVectors();
    if (m_numOfLevel == 1)//if it already first level we dont need to load again from file
        m_board->loadLevel(FIRSTLEVEL, false);
    else
        m_board->loadLevel(FIRSTLEVEL, true);
    m_bar = std::make_unique<JetBar>();
    m_numOfLevel = FIRSTLEVEL;
}//end restartGame

void Controller::clocksResrtart()
{
    m_move.restart();
    m_enemyShot.restart();
    m_jet.restart();
}//end clocksResrtart

void Controller::help()
{
    (m_currentView.x) ? m_help.setPosition(m_currentView.x - 800.f, 100.f) : m_help.setPosition(m_currentView.x + 150.f, 100.f);
    while (true)
    {
        m_window.draw(m_help);
        m_window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            break;
    }
}//end help

void Controller::handleButtonsPress(ButtonName button)
{
    if (button == Play)
        runGame();
    else if (button == Newgame)
    {
        restartGame();
        m_exitMenu = true;
    }
    else if (button == Resume)
    {
        m_exitMenu = true;
    }
    else if (button == Help)
    {
        help();
    }
    else if (button == Exit)
    {
        m_window.close();
        exit(0);
    }
}//end handleButtonsPress

void Controller::menuEventHandle(Menu& menuKind)
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
            exit(0);
        }
        if (event.type == sf::Event::MouseMoved)
        {
            auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            menuKind.handleMouse(location);//handle buttons changing color when mouse on it
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            auto answer = menuKind.whoIsPressed(location);//check wich button pressed
            handleButtonsPress(answer);//handle the pressing due to button kind
        }
    }
}//end menuEventHandle

void Controller::gameEventHandle()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyReleased:
        {
            m_board->playerShoot(event);
            m_board->playerJet(event, m_jet);
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            m_stats->handleSoundStatus(location);
        }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        menuDuring();
        clocksResrtart();
    }
}//end gameEventHandle
