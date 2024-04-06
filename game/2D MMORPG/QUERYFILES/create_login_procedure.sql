CREATE PROCEDURE UserLogin 
    @UserID VARCHAR(20),
    @UserPW VARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;

    -- 입력된 아이디와 비밀번호가 일치하는 행이 있는지 확인
    IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @UserID AND UserPW = @UserPW)
    BEGIN
        -- 일치하는 행이 존재하는 경우 해당 유저의 캐릭터 정보 반환
        SELECT * FROM SIMSERVER.dbo.CharacterInfo WHERE UserID = @UserID;
    END
    ELSE
    BEGIN
        -- 아이디만 일치하는 행이 있는지 확인
        IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @UserID)
        BEGIN
            -- 아이디만 일치하는 경우 로그인 실패 반환
            SELECT 'Login Failed. Password is incorrect.' AS Result;
        END
        ELSE
        BEGIN
            -- 일치하는 행이 없는 경우 새로운 회원 정보 및 캐릭터 정보 추가 후 반환
            INSERT INTO SIMSERVER.dbo.UserInfo (UserID, UserPW) VALUES (@UserID, @UserPW);
            INSERT INTO SIMSERVER.dbo.CharacterInfo(UserID, X, Y, Lv, Exp, HP) VALUES (@UserID, 0, 0, 1, 0, 100);
            SELECT * FROM SIMSERVER.dbo.CharacterInfo WHERE UserID = @UserID;
        END
    END
END
