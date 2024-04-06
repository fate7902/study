CREATE PROCEDURE DeleteAccount
    @InputID VARCHAR(20),
    @InputPW VARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;

    -- 해당 아이디와 비밀번호로 회원이 존재하는지 확인
    IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @InputID AND UserPW = @InputPW)
    BEGIN
        -- 해당 회원의 캐릭터 정보 삭제
        DELETE FROM SIMSERVER.dbo.CharacterInfo
        WHERE UserID = @InputID;

        -- 해당 회원 정보 삭제
        DELETE FROM SIMSERVER.dbo.UserInfo
        WHERE UserID = @InputID;

        PRINT '회원 정보가 삭제되었습니다.';
    END
    ELSE
    BEGIN
        PRINT '입력한 아이디 또는 비밀번호가 잘못되었습니다.';
    END
END
