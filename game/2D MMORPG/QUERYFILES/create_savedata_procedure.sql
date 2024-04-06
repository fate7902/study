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

    -- 입력된 아이디와 비밀번호가 일치하는 행이 있는지 확인
    IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @UserID AND UserPW = @UserPW)
    BEGIN
        -- 일치하는 행이 존재하는 경우 해당 유저의 캐릭터 정보 업데이트
		UPDATE SIMSERVER.dbo.CharacterInfo 
		SET X = @CharacterX, Y = @CharacterY, Lv = @CharacterLv, Exp = @CharacterExp, HP = @CharacterHP
		WHERE UserID = @UserID
    END
    ELSE
    BEGIN
       SELECT 'UserInfo is incorrect.' AS Result;
    END
END
