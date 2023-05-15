#include "stdafx.h"
#include "iocp.h"

CLIENT clients[MAX_USER]{};

int main() {		
	IOCP iocp;
	iocp.Initialize(clients);
}