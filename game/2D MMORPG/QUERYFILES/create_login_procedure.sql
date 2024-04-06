CREATE PROCEDURE UserLogin 
    @UserID VARCHAR(20),
    @UserPW VARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;

    -- �Էµ� ���̵�� ��й�ȣ�� ��ġ�ϴ� ���� �ִ��� Ȯ��
    IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @UserID AND UserPW = @UserPW)
    BEGIN
        -- ��ġ�ϴ� ���� �����ϴ� ��� �ش� ������ ĳ���� ���� ��ȯ
        SELECT * FROM SIMSERVER.dbo.CharacterInfo WHERE UserID = @UserID;
    END
    ELSE
    BEGIN
        -- ���̵� ��ġ�ϴ� ���� �ִ��� Ȯ��
        IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @UserID)
        BEGIN
            -- ���̵� ��ġ�ϴ� ��� �α��� ���� ��ȯ
            SELECT 'Login Failed. Password is incorrect.' AS Result;
        END
        ELSE
        BEGIN
            -- ��ġ�ϴ� ���� ���� ��� ���ο� ȸ�� ���� �� ĳ���� ���� �߰� �� ��ȯ
            INSERT INTO SIMSERVER.dbo.UserInfo (UserID, UserPW) VALUES (@UserID, @UserPW);
            INSERT INTO SIMSERVER.dbo.CharacterInfo(UserID, X, Y, Lv, Exp, HP) VALUES (@UserID, 0, 0, 1, 0, 100);
            SELECT * FROM SIMSERVER.dbo.CharacterInfo WHERE UserID = @UserID;
        END
    END
END
