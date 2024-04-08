#pragma once
class Database
{
private:
	SQLHENV					m_henv;
	SQLHDBC					m_hdbc;
	SQLHSTMT				m_hstmt;
	SQLRETURN				m_ret;

public:
	Database();
	~Database();

	void errorDisplay(SQLHANDLE handle, SQLSMALLINT type, RETCODE retCode);
	void connectDatabase();

	bool login(CHARACTERINFO& characterInfo);
	void saveData(CHARACTERINFO characterInfo);
};

