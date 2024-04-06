CREATE PROCEDURE SaveData 
    @UserID VARCHAR(20),
    @UserPW VARCHAR(100),
	@CharacterX INT,
	@CharacterY INT,	
	@CharacterLv INT,
	@CharacterExp INT,
	@CharacterHP INT
AS
BEGIN
    SET NOCOUNT ON;

    -- �Էµ� ���̵�� ��й�ȣ�� ��ġ�ϴ� ���� �ִ��� Ȯ��
    IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @UserID AND UserPW = @UserPW)
    BEGIN
        -- ��ġ�ϴ� ���� �����ϴ� ��� �ش� ������ ĳ���� ���� ������Ʈ
		UPDATE SIMSERVER.dbo.CharacterInfo 
		SET X = @CharacterX, Y = @CharacterY, Lv = @CharacterLv, Exp = @CharacterExp, HP = @CharacterHP
		WHERE UserID = @UserID
    END
    ELSE
    BEGIN
       SELECT 'UserInfo is incorrect.' AS Result;
    END
END
