#include "stdafx.h"
#include "database.h"

Database::Database()
{
    connectDatabase();
}

Database::~Database()
{
    if (m_hdbc != SQL_NULL_HANDLE) {
        SQLDisconnect(m_hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
    }
    if (m_henv != SQL_NULL_HANDLE) {
        SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
    }
}

void Database::errorDisplay(SQLHANDLE handle, SQLSMALLINT type, RETCODE retCode)
{
    SQLSMALLINT iRec = 0;
    SQLINTEGER iError;
    WCHAR wszMessage[1000];
    WCHAR wszState[SQL_SQLSTATE_SIZE + 1];
    if (SQL_INVALID_HANDLE == retCode) {
        fwprintf(stderr, L"Invalid handle!\n");
        return;
    }
    while (SQLGetDiagRec(type, handle, ++iRec, wszState, &iError, wszMessage,
        (SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)), (SQLSMALLINT*)NULL) == SQL_SUCCESS) {
        if (wcsncmp(wszState, L"01004", 5)) {
            fwprintf(stderr, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
        }
    }
}

void Database::connectDatabase()
{
    int retryCount = 3;

    while (retryCount > 0) {
        m_ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
        if (m_ret != SQL_SUCCESS && m_ret != SQL_SUCCESS_WITH_INFO) {
            cout << "[SQL] ODBC ȯ�� �ڵ� �Ҵ� ����. ��õ��մϴ�...\n";
            continue;
        }

        m_ret = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
        if (m_ret != SQL_SUCCESS && m_ret != SQL_SUCCESS_WITH_INFO) {
            cout << "[SQL] ODBC ȯ�� �ڵ� �Ӽ� ���� ����. ��õ��մϴ�...\n";
            SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
            continue;
        }

        m_ret = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
        if (m_ret != SQL_SUCCESS && m_ret != SQL_SUCCESS_WITH_INFO) {
            cout << "[SQL] DB ���� ��� �Ҵ� ����. ��õ��մϴ�...\n";
            SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
            continue;
        }

        SQLSetConnectAttr(m_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
        m_ret = SQLConnect(m_hdbc, (SQLWCHAR*)L"SIMSERVER", SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);
        if (m_ret == SQL_SUCCESS || m_ret == SQL_SUCCESS_WITH_INFO) {
            cout << "[SQL] DB ���� ����!\n";            
            return;
        }
        else {
            cout << "[SQL] DB ���� ����. ��õ��մϴ�...\n";
            SQLDisconnect(m_hdbc);
            SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
            retryCount--;

            // ��õ� ������ 3�ʷ� �����ϰ�, ��õ� ���� �� ���
            this_thread::sleep_for(seconds(3));
        }
    }

    cout << "[SQL] DB ���� �ִ�õ��� �Ѱ� �����߽��ϴ�.\n";
}

bool Database::login(CHARACTERINFO& characterInfo)
{
    wstring query = L"EXEC UserLogin ?, ?";
    SQLCHAR* sqlUserID = (SQLCHAR*)characterInfo.ID.c_str();
    SQLCHAR* sqlUserPW = (SQLCHAR*)characterInfo.PW.c_str();

    m_ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
    if (m_ret != SQL_SUCCESS && m_ret != SQL_SUCCESS_WITH_INFO) {
        cout << "[SQL] �ڵ� �Ҵ� ���з� ���� �α��� �õ� ����.\n";
        return false;
    }

    SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, sqlUserID, characterInfo.ID.size(), NULL);
    SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, sqlUserPW, characterInfo.PW.size(), NULL);
    m_ret = SQLExecDirect(m_hstmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    if (m_ret != SQL_SUCCESS && m_ret != SQL_SUCCESS_WITH_INFO) {
        cout << "[SQL] ���ν��� ���� ����.\n" << endl;
        errorDisplay(m_hstmt, SQL_HANDLE_STMT, m_ret);
        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
        return false;
    }

    //m_ret = SQLFetch(m_hstmt);
    if (m_ret == SQL_SUCCESS || m_ret == SQL_SUCCESS_WITH_INFO) {
        SQLLEN characterX, characterY, characterLv, characterExp, characterHP;
        m_ret = SQLBindCol(m_hstmt, 2, SQL_C_LONG, &characterInfo.x, sizeof(int), &characterX);
        m_ret = SQLBindCol(m_hstmt, 3, SQL_C_LONG, &characterInfo.y, sizeof(int), &characterY);
        m_ret = SQLBindCol(m_hstmt, 4, SQL_C_LONG, &characterInfo.lv, sizeof(int), &characterLv);
        m_ret = SQLBindCol(m_hstmt, 5, SQL_C_LONG, &characterInfo.exp, sizeof(int), &characterExp);
        m_ret = SQLBindCol(m_hstmt, 6, SQL_C_LONG, &characterInfo.hp, sizeof(int), &characterHP);
        for (int i = 0; ; i++) {
            m_ret = SQLFetch(m_hstmt);
            if (m_ret == SQL_ERROR) errorDisplay(m_hstmt, SQL_HANDLE_STMT, m_ret);
            if (m_ret == SQL_SUCCESS || m_ret == SQL_SUCCESS_WITH_INFO) {
                cout << "[SQL] DB Ž�� �Ϸ�.\n";
            }
            else
                break;
        }

        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
        if (characterInfo.lv == 0) {
            cout << "[SQL] ��ġ�ϴ� ���� ������ �������� �ʽ��ϴ�.\n";
            return false;
        }
        return true;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
        cout << "[SQL] ��ġ�ϴ� ���� ������ �������� �ʽ��ϴ�.\n";
        return false;
    }
}

void Database::saveData(CHARACTERINFO characterInfo)
{
    wstring query = L"EXEC SaveData ?, ?, ?, ?, ?, ?, ?";
    SQLCHAR* sqlUserID = (SQLCHAR*)characterInfo.ID.c_str();
    SQLCHAR* sqlUserPW = (SQLCHAR*)characterInfo.PW.c_str();

    m_ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
    if (m_ret != SQL_SUCCESS && m_ret != SQL_SUCCESS_WITH_INFO) {
        cout << "[SQL] �ڵ� �Ҵ� ���з� ���� ������ ���� ����.\n";
        return;
    }

    m_ret = SQLPrepare(m_hstmt, (SQLWCHAR*)query.c_str(), SQL_NTS);
    if (m_ret != SQL_SUCCESS && m_ret != SQL_SUCCESS_WITH_INFO) {
        cout << "[SQL] ���ν��� ȣ�� �غ� ����.\n";
        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
        return;
    }

    SQLBindParameter(m_hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 20, 0, sqlUserID, characterInfo.ID.size(), NULL);
    SQLBindParameter(m_hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 100, 0, sqlUserPW, characterInfo.PW.size(), NULL);
    SQLBindParameter(m_hstmt, 3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &characterInfo.x, 0, NULL);
    SQLBindParameter(m_hstmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &characterInfo.y, 0, NULL);
    SQLBindParameter(m_hstmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &characterInfo.lv, 0, NULL);
    SQLBindParameter(m_hstmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &characterInfo.exp, 0, NULL);
    SQLBindParameter(m_hstmt, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &characterInfo.hp, 0, NULL);
    m_ret = SQLExecute(m_hstmt);
    if (SQL_SUCCESS == m_ret || SQL_SUCCESS_WITH_INFO == m_ret) {
        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
    }
    else {
        cout << "[SQL] ������ ���� ����\n";
        errorDisplay(m_hstmt, SQL_HANDLE_STMT, m_ret);
        SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
        return;
    }    
}
