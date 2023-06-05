#pragma once
#include <list>
#include "menu.h"
#include "GameCards.h"
#include "Dice.h"
#include "event.h"
#include "button.h"
class Game {
	unsigned int  m_num_players = 0; // the total number of players
	static Game* m_instance;
	std::list<Event*>m_events; // a list with the total events
	std::list< class Player*> m_players; // a list with the created players
	std::list<GameCards*> m_cards; // a list with the total cards
	GameCards* m_active_card = nullptr; // the card that the currently playing player is on
	class Player* m_current = nullptr; // the current player the mouse in on
	class Player* m_active_player = nullptr; // the player that is currently playing
	

	public:
		enum game_state{STATE_INIT,STATE_LOADING,STATE_IDLE,STATE_PLAYING,STATE_PAUSED,STATE_DONE};
protected:

	game_state m_previous_state;//the previous state before the current, used for the MENU
	game_state  m_state = STATE_INIT; // the current state

//---------methods for drawing and updating each state diferrently--------
	void drawMainScreen();
	void drawLoadingScreen();
	void drawPlayingScreen();
	void drawInitScreen();
	void drawEndScreen();

	void updateInitScreen();
	void updateLoadingScreen();
	void updateMainScreen();
	void updateStopScreen();
	void updatePlayerMovement();
	void updatePlayingScreen();
	void updateEndScreen();

//--------------------------------------------------------------------/	
	//methods for creating the cards used for the game
	void CreateLaLigaTeams();
	void CreatePremierLeagueTeams();
	void CreateSuperLeagueTeams();
	void CreateSerieATeams();
	void CreateSpecialCards();

	Game() {};
public:
	//all the items we need
	menu* Menu = new menu();
	Dice* dice = new Dice();
	button* buyButton = new button(CANVAS_WIDTH / 2.2f, CANVAS_HEIGHT / 4.9, 80, 80,20, "buy.png");
	button* skipButton = new button(CANVAS_WIDTH / 1.8f, CANVAS_HEIGHT / 5.4, 57, 57,20, "next-track.png");
	button* payButton = new button(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 1.5f, 80, 80,20, "pay.png");
	button* p1Button = new button(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 2 + 150, CANVAS_HEIGHT / 2 + 150,80, "button1.png");
	button* p2Button = new button(CANVAS_WIDTH / 1.5f, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 2 + 150, CANVAS_HEIGHT / 2 + 150,80, "button2.png");
	button* startButton = new button(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 4.9, 100, 100, 30, "start.png");

	void draw();
	void update();
	void init();
	~Game();

	void processEvents();
	void addEvent(Event * ev);

	static Game* getInstance();//dimiourgei mia monadiki fora to m_instance
	static void releaseInstance() { if (m_instance)delete m_instance; m_instance = nullptr; }
};