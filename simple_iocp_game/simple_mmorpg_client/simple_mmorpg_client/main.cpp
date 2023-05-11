#include "stdafx.h"
#include "sfml.h"
#include "object.h"

int g_x = 0, g_y = 0;
Object players[MAX_USER];

int main() {
	Sfml sfml;
	sfml.Loop(players);
}