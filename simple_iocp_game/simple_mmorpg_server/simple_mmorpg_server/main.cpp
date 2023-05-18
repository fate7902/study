#include "stdafx.h"
#include "iocp.h"

CLIENT clients[MAX_USER]{};
MONSTER monsters[MAX_MONSTER]{};

int main() {		
	IOCP iocp;
	iocp.Initialize(clients, monsters);
}