#include "stdafx.h"
#include "iocp.h"

int main() {
	Iocp server(4000);
	server.initialize();
}