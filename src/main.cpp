#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <Keys.hpp>
#include <Game.hpp>
#include <Time.hpp>
#include <Interface.hpp>

Game *			g_game = NULL;
pthread_mutex_t	g_updateMutex = PTHREAD_MUTEX_INITIALIZER;

void	*updateThreadFunction(void *ptr) {
	(void)ptr;
	bool run = true;
	while (run) {
		pthread_mutex_lock(&g_updateMutex);
		if (g_game != NULL && !g_game->isPaused()) {
			run = g_game->update();
		}
		pthread_mutex_unlock(&g_updateMutex);
	}
	return (0);
}

void	signalInt(int sig) {
	(void)sig;
	pthread_mutex_lock(&g_updateMutex);
	delete g_game;
	if (sig == SIGSEGV) {
		exit(EXIT_FAILURE);
	} else {
		exit(EXIT_SUCCESS);
	}
}

int		main(int argc, char *argv[]) {
	int					key;
	pthread_t			updateThread;
	int					eps = ENEMIES_PER_SEC;
	int					emd = ENEMIES_MOVE_DELAY;

	if (argc == 2) {
		std::string arg(argv[1]);
		if (arg.compare("-h") == 0) {
			std::cout << "Usage: " << argv[0] << " [enemiesPerSecond] [enemiesMoveDelay]" << std::endl;
			return (EXIT_SUCCESS);
		} else {
			eps = atoi(argv[1]);
		}
	} else if (argc >= 3) {
		eps = atoi(argv[1]);
		emd = atoi(argv[2]);
	}
	srand(time(0));
	signal(SIGINT, signalInt);
	signal(SIGWINCH, signalInt);
	signal(SIGSEGV, signalInt);
	if (eps < 2 || eps > 10) {
		eps = ENEMIES_PER_SEC;
	}
	if (emd < 10 || emd > 40) {
		emd = ENEMIES_MOVE_DELAY;
	}
	g_game = new Game(eps, emd);
	g_game->updateHUD();
	if (pthread_create(&updateThread, NULL, updateThreadFunction, (void*)0) != 0) {
		return (EXIT_FAILURE);
	}
	while (42) {
		key = g_game->getInterface().getPressedKey();
		if (key == KEY_ESC) {
			signalInt(0);
		}
		pthread_mutex_lock(&g_updateMutex);
		if (key == KEY_RETURN && !g_game->isEnded()) {
			g_game->setPaused(!g_game->isPaused());
			g_game->updateHUD();
		} else if (!g_game->isPaused()) {
			if (key == KEY_UP)
				g_game->getPlayer().moveY(g_game->getInterface(), false);
			else if (key == KEY_DOWN)
				g_game->getPlayer().moveY(g_game->getInterface(), true);
			else if (key == KEY_LEFT)
				g_game->getPlayer().moveX(g_game->getInterface(), false);
			else if (key == KEY_RIGHT)
				g_game->getPlayer().moveX(g_game->getInterface(), true);
			else if (key == KEY_SPACE && !g_game->isEnded())
				g_game->shoot();
			else if (g_game->isEnded()) {
				pthread_mutex_unlock(&g_updateMutex);
				signalInt(0);
			}
		}
		pthread_mutex_unlock(&g_updateMutex);
	}
	return (EXIT_SUCCESS);
}
