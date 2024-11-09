#include "judge.h"
#include "value.h"

#define COLUMN 15
#define ROW 15
int black = 1;
int none = 0;

int directions[8][2] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

/**
 * @brief �ж����Ӻ��ʤ��
 * @param m (x,y)����
 * @param color ������ɫ������BLACK or WHITE��
 * @retval 0 ��ʱ��ʤ��
 * @retval 1 �����������ӣ�ʤ��
 * @retval 2 �����������ӣ�ʤ��
 * @retval 3 �����³����֣�����ʤ
 */
int judgeWin(int m[], int color)
{
    int ban = 0;
    if (color == BLACK)
        ban = BanMove(m[0], m[1]);
    if (ban != 0)return 3;
	int nums[4];
	int i;
	for (i = 0; i < 4; i++) 
	{
		nums[i] = directionCount(m, color, i) + directionCount(m, color, i + 4);
	}
	int fiveInLine = (nums[0] > 3) || (nums[1] > 3) || (nums[2] > 3) || (nums[3] > 3);
    if (fiveInLine == 0) {
        return 0;
    }
    else if (fiveInLine == 1) {
        if (color == BLACK)
            return 1;
        else
            return 2;
    }
}


/**
 * @brief ����ĳһ�����ϵ���������
 * @param[in] m (x,y)����
 * @param[in] color ������ɫ������BLACK or WHITE��
 * @param[in] dir ��������ķ���Ϊ0-7�˸�����
 * @retval ��������
 */
int directionCount(int m[], int color, int dir)
{
	int num = 0;
	int x = m[0];
	int y = m[1];

	while (Board[x][y] == color && x<15 && x>-1 && y<15 && y>-1)
	{
		num++;
		x += directions[dir][0];
		y += directions[dir][1];
	}
	return num - 1;
}


/**
 * @brief ���ֹ�����
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 ��������
 * @retval 2 ���Ľ���
 * @retval 3 ��������
 */
int BanMove(int x_row, int y_column)
{
	if (1 == LongBan(x_row, y_column)) //�жϳ�������
		return 3;

	if (1 == FourBan(x_row, y_column)) //�ж����Ľ���
		return 2;

	if (1 == ThreeBan(x_row, y_column)) //�ж���������
		return 1;

	return 0;  //û�н���
}

/**
 * @brief �������ּ��
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 ����������
 */
int ThreeBan(int x_row, int y_column)
{
    char chess[10]; //������Χ���, '0':������; '1':����; '2':����; '4':������;
    int i, x, y, addr, count = 0, fakeflag; //x:������; y:������; addr:����ַ�����Ե�ַ;
    //count:����/��������,��Χ:0~4; fakeflag:�ٻ�����־λ

//'-'���ŷ�����ֹ���
    x = x_row;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;   //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; y++, i++) {
        if (y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if (addr >= 0 && addr <= 9) {
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        Board[x_row][y_column - 4 + addr] = black;   //"01110"�ĵ�һ��"0"�ź���
        if (0 != BanMove(x_row, y_column - 4 + addr)) {
            fakeflag = 1;
        }
        Board[x_row][y_column - 4 + addr] = none;   //�ָ�"01110"�ĵ�һ��"0"
        Board[x_row][y_column + addr] = black;      //"01110"�ĵڶ���"0"�ź���
        if (0 != BanMove(x_row, y_column + addr)) {
            fakeflag = 1;
        }
        Board[x_row][y_column + addr] = none;       //�ָ�"01110"�ĵڶ���"0"
        if (0 == fakeflag && y_column - 5 + addr >= 0 && 0 == Board[x_row][y_column - 5 + addr]) { //"01110"��ǰΪ��
            Board[x_row][y_column - 5 + addr] = black;
            if (0 == BanMove(x_row, y_column - 5 + addr)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row][y_column - 5 + addr] = none;
        }
        else if (0 == fakeflag && y_column + 1 + addr < COLUMN && 0 == Board[x_row][y_column + 1 + addr]) {//"01110"�ĺ�Ϊ��
            Board[x_row][y_column + 1 + addr] = black;
            if (0 == BanMove(x_row, y_column + 1 + addr)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row][y_column + 1 + addr] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row][y_column - 2 + addr] = black;           //"010110"�м��"0"�ź���
        if (0 == BanMove(x_row, y_column - 2 + addr)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row][y_column - 2 + addr] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row][y_column - 1 + addr] = black;           //"011010"�м��"0"�ź���
        if (0 == BanMove(x_row, y_column - 1 + addr)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row][y_column - 1 + addr] = none;            //�ָ�"011010"�м��"0"
    }

    //'|'���ŷ�����ֹ���
    x = x_row - 4;        //��ȡ����������Ŀ�ʼѭ������
    y = y_column;         //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; x++, i++) {
        if (x < 0 || x >= ROW) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if (addr >= 0 && addr <= 9) {
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        Board[x_row - 4 + addr][y_column] = black;   //"01110"�ĵ�һ��"0"�ź���
        if (0 != BanMove(x_row - 4 + addr, y_column)) {
            fakeflag = 1;
        }
        Board[x_row - 4 + addr][y_column] = none;   //�ָ�"01110"�ĵ�һ��"0"
        Board[x_row + addr][y_column] = black;      //"01110"�ĵڶ���"0"�ź���
        if (0 != BanMove(x_row + addr, y_column)) {
            fakeflag = 1;
        }
        Board[x_row + addr][y_column] = none;       //�ָ�"01110"�ĵڶ���"0"
        if (0 == fakeflag && x_row - 5 + addr >= 0 && 0 == Board[x_row - 5 + addr][y_column]) { //"01110"��ǰΪ��
            Board[x_row - 5 + addr][y_column] = black;
            if (0 == BanMove(x_row - 5 + addr, y_column)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row - 5 + addr][y_column] = none;
        }
        else if (0 == fakeflag && x_row + 1 + addr < ROW && 0 == Board[x_row + 1 + addr][y_column]) {//"01110"�ĺ�Ϊ��
            Board[x_row + 1 + addr][y_column] = black;
            if (0 == BanMove(x_row + 1 + addr, y_column)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row + 1 + addr][y_column] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 2 + addr][y_column] = black;           //"010110"�м��"0"�ź���
        if (0 == BanMove(x_row - 2 + addr, y_column)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row - 2 + addr][y_column] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 1 + addr][y_column] = black;           //"011010"�м��"0"�ź���
        if (0 == BanMove(x_row - 1 + addr, y_column)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row - 1 + addr][y_column] = none;            //�ָ�"011010"�м��"0"
    }

    //'/'б�ܷ�����ֹ���
    x = x_row - 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column + 4;       //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; x++, y--, i++) {
        if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if (addr >= 0 && addr <= 9) {
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        Board[x_row - 4 + addr][y_column + 4 - addr] = black;   //"01110"�ĵ�һ��"0"�ź���
        if (0 != BanMove(x_row - 4 + addr, y_column + 4 - addr)) {
            fakeflag = 1;
        }
        Board[x_row - 4 + addr][y_column + 4 - addr] = none;   //�ָ�"01110"�ĵ�һ��"0"
        Board[x_row + addr][y_column - addr] = black;      //"01110"�ĵڶ���"0"�ź���
        if (0 != BanMove(x_row + addr, y_column - addr)) {
            fakeflag = 1;
        }
        Board[x_row + addr][y_column - addr] = none;       //�ָ�"01110"�ĵڶ���"0"
        if (0 == fakeflag && x_row - 5 + addr >= 0 && y_column + 5 - addr < COLUMN && 0 == Board[x_row - 5 + addr][y_column + 5 - addr]) { //"01110"��ǰΪ��
            Board[x_row - 5 + addr][y_column + 5 - addr] = black;
            if (0 == BanMove(x_row - 5 + addr, y_column + 5 - addr)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row - 5 + addr][y_column + 5 - addr] = none;
        }
        else if (0 == fakeflag && x_row + 1 + addr < ROW && y_column - 1 - addr >= 0 && 0 == Board[x_row + 1 + addr][y_column - 1 - addr]) {//"01110"�ĺ�Ϊ��
            Board[x_row + 1 + addr][y_column - 1 - addr] = black;
            if (0 == BanMove(x_row + 1 + addr, y_column - 1 - addr)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row + 1 + addr][y_column - 1 - addr] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 2 + addr][y_column + 2 - addr] = black;           //"010110"�м��"0"�ź���
        if (0 == BanMove(x_row - 2 + addr, y_column + 2 - addr)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row - 2 + addr][y_column + 2 - addr] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 1 + addr][y_column + 1 - addr] = black;           //"011010"�м��"0"�ź���
        if (0 == BanMove(x_row - 1 + addr, y_column + 1 - addr)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row - 1 + addr][y_column + 1 - addr] = none;            //�ָ�"011010"�м��"0"
    }

    //'\'��б�ܷ�����ֹ���
    x = x_row - 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;       //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; x++, y++, i++) {
        if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    //���"����"�����
    addr = strstr(chess, "01110") - chess; //����ַ�����ԭ�ַ������±�
    fakeflag = 0;                          //�ٻ�����־λ
    if (addr >= 0 && addr <= 9) {
        //���"01110"��"0"�Ƿ���� && "01110"��ǰ���Ƿ��и�Ϊ��,�Ҳ��ǽ���
        Board[x_row - 4 + addr][y_column - 4 + addr] = black;   //"01110"�ĵ�һ��"0"�ź���
        if (0 != BanMove(x_row - 4 + addr, y_column - 4 + addr)) {
            fakeflag = 1;
        }
        Board[x_row - 4 + addr][y_column - 4 + addr] = none;   //�ָ�"01110"�ĵ�һ��"0"
        Board[x_row + addr][y_column + addr] = black;      //"01110"�ĵڶ���"0"�ź���
        if (0 != BanMove(x_row + addr, y_column + addr)) {
            fakeflag = 1;
        }
        Board[x_row + addr][y_column + addr] = none;       //�ָ�"01110"�ĵڶ���"0"
        if (0 == fakeflag && x_row - 5 + addr >= 0 && y_column - 5 + addr >= 0 && 0 == Board[x_row - 5 + addr][y_column - 5 + addr]) { //"01110"��ǰΪ��
            Board[x_row - 5 + addr][y_column - 5 + addr] = black;
            if (0 == BanMove(x_row - 5 + addr, y_column - 5 + addr)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row - 5 + addr][y_column - 5 + addr] = none;
        }
        else if (0 == fakeflag && x_row + 1 + addr < ROW && y_column + 1 + addr < COLUMN && 0 == Board[x_row + 1 + addr][y_column + 1 + addr]) {//"01110"�ĺ�Ϊ��
            Board[x_row + 1 + addr][y_column + 1 + addr] = black;
            if (0 == BanMove(x_row + 1 + addr, y_column + 1 + addr)) { //���˵��Ƿ�Ϊ����
                count++;
            }
            Board[x_row + 1 + addr][y_column + 1 + addr] = none;
        }
    }
    //���"����"�����1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 2 + addr][y_column - 2 + addr] = black;           //"010110"�м��"0"�ź���
        if (0 == BanMove(x_row - 2 + addr, y_column - 2 + addr)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row - 2 + addr][y_column - 2 + addr] = none;            //�ָ�"010110"�м��"0"
    }
    //���"����"�����2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 1 + addr][y_column - 1 + addr] = black;           //"011010"�м��"0"�ź���
        if (0 == BanMove(x_row - 1 + addr, y_column + 1 - addr)) { //���˵��Ƿ�Ϊ����
            count++;
        }
        Board[x_row - 1 + addr][y_column - 1 + addr] = none;            //�ָ�"011010"�м��"0"
    }

    return count > 1 ? 1 : 0;  //������1������/����, ����1; ���򷵻�0

}

/**
 * @brief ���Ľ��ּ��
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 �����Ľ���
 */
int FourBan(int x_row, int y_column)
{
    char chess[10]; //������Χ���, 0:������; 1:����; 2:����; 4:������;
    int i, x, y, count = 0; //countΪ����/��������, ��Χ: 0~4

    //'-'���ŷ�����ֹ���
    x = x_row;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;   //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; y++, i++) {
        if (y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'|'���ŷ�����ֹ���
    x = x_row - 4;        //��ȡ����������Ŀ�ʼѭ������
    y = y_column;         //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; x++, i++) {
        if (x < 0 || x >= ROW) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'/'б�ܷ�����ֹ���
    x = x_row - 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column + 4;       //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; x++, y--, i++) {
        if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    //'\'��б�ܷ�����ֹ���
    x = x_row - 4;          //��ȡ����������Ŀ�ʼѭ������
    y = y_column - 4;       //x����; y����;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//��ʼ��������Χ����״̬
    for (i = 0; i < 9; x++, y++, i++) {
        if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) //��������������
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    if (NULL != strstr(chess, "011110") || NULL != strstr(chess, "10111") || NULL != strstr(chess, "11011") || \
        NULL != strstr(chess, "11101") || NULL != strstr(chess, "011112") || NULL != strstr(chess, "011114") || \
        NULL != strstr(chess, "211110") || NULL != strstr(chess, "411110")) {
        count++;
    }

    return count > 1 ? 1 : 0;  //������1������/����/����, ����1; ���򷵻�0
}

/**
 * @brief �������ּ��
 * @param[in] x_row    Ҫ�����������
 * @param[in] y_column Ҫ�����������
 * @retval 0 �޽���
 * @retval 1 �г�������
 */
int LongBan(int x_row, int y_column)
{
    int m[2] = {x_row,y_column};
    int nums[4];
    int i;
    for (i = 0; i < 4; i++)
    {
        nums[i] = directionCount(m, BLACK, i) + directionCount(m, BLACK, i + 4);
    }
    int longline = (nums[0] > 4) || (nums[1] > 4) || (nums[2] > 4) || (nums[3] > 4);
    if (longline == 1)
        return 1;
    else 
        return 0;
}

