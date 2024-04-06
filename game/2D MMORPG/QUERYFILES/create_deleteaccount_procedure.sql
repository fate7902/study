CREATE PROCEDURE DeleteAccount
    @InputID VARCHAR(20),
    @InputPW VARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;

    -- �ش� ���̵�� ��й�ȣ�� ȸ���� �����ϴ��� Ȯ��
    IF EXISTS (SELECT 1 FROM SIMSERVER.dbo.UserInfo WHERE UserID = @InputID AND UserPW = @InputPW)
    BEGIN
        -- �ش� ȸ���� ĳ���� ���� ����
        DELETE FROM SIMSERVER.dbo.CharacterInfo
        WHERE UserID = @InputID;

        -- �ش� ȸ�� ���� ����
        DELETE FROM SIMSERVER.dbo.UserInfo
        WHERE UserID = @InputID;

        PRINT 'ȸ�� ������ �����Ǿ����ϴ�.';
    END
    ELSE
    BEGIN
        PRINT '�Է��� ���̵� �Ǵ� ��й�ȣ�� �߸��Ǿ����ϴ�.';
    END
END
