#include "judge.h"
#include "value.h"

#define COLUMN 15
#define ROW 15
int black = 1;
int none = 0;

int directions[8][2] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

int judgeWin(int m[], int color)
{
	int nums[4];
	int i;
	for (i = 0; i < 4; i++) 
	{
		nums[i] = directionCount(m, color, i) + directionCount(m, color, i + 4);
	}
	int fiveInLine = (nums[0] > 4) || (nums[1] > 4) || (nums[2] > 4) || (nums[3] > 4);
	int longline = (nums[0] > 5) || (nums[1] > 5) || (nums[2] > 5) || (nums[3] > 5) || (color == BLACK);
}



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
 * @brief 禁手规则检查
 * @param[in] Board    棋盘二级指针
 * @param[in] x_row    要检查点的行坐标
 * @param[in] y_column 要检查点的列坐标
 * @retval 0 无禁手
 * @retval 1 三三禁手
 * @retval 2 四四禁手
 * @retval 3 长连禁手
 */
int BanMove(int x_row, int y_column)
{
	if (1 == LongBan(x_row, y_column)) //判断长连禁手
		return 3;

	if (1 == FourBan(x_row, y_column)) //判断四四禁手
		return 2;

	if (1 == ThreeBan(x_row, y_column)) //判断三三禁手
		return 1;

	return 0;  //没有禁手
}

/**
 * @brief 三三禁手检查
 * @param[in] Board    棋盘二级指针
 * @param[in] x_row    要检查点的行坐标
 * @param[in] y_column 要检查点的列坐标
 * @retval 0 无禁手
 * @retval 1 有三三禁手
 */
int ThreeBan(int x_row, int y_column)
{
    char chess[10]; //棋子周围情况, '0':空棋盘; '1':黑棋; '2':白棋; '4':无棋盘;
    int i, x, y, addr, count = 0, fakeflag; //x:行坐标; y:列坐标; addr:配对字符串相对地址;
    //count:活三/跳三的数,范围:0~4; fakeflag:假活三标志位

//'-'横着方向禁手规则
    x = x_row;          //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;   //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; y++, i++) {
        if (y < 0 || y >= COLUMN) //超出棋盘则跳出
            continue;
        chess[i] = Board[x][y]%10 + 48;
    }
    //检查"活三"的情况
    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    fakeflag = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        Board[x_row][y_column - 4 + addr] = black;   //"01110"的第一个"0"放黑棋
        if (0 != BanMove(x_row, y_column - 4 + addr)) {
            fakeflag = 1;
        }
        Board[x_row][y_column - 4 + addr] = none;   //恢复"01110"的第一个"0"
        Board[x_row][y_column + addr] = black;      //"01110"的第二个"0"放黑棋
        if (0 != BanMove(x_row, y_column + addr)) {
            fakeflag = 1;
        }
        Board[x_row][y_column + addr] = none;       //恢复"01110"的第二个"0"
        if (0 == fakeflag && y_column - 5 + addr >= 0 && 0 == Board[x_row][y_column - 5 + addr]) { //"01110"的前为空
            Board[x_row][y_column - 5 + addr] = black;
            if (0 == BanMove(x_row, y_column - 5 + addr)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row][y_column - 5 + addr] = none;
        }
        else if (0 == fakeflag && y_column + 1 + addr < COLUMN && 0 == Board[x_row][y_column + 1 + addr]) {//"01110"的后为空
            Board[x_row][y_column + 1 + addr] = black;
            if (0 == BanMove(x_row, y_column + 1 + addr)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row][y_column + 1 + addr] = none;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row][y_column - 2 + addr] = black;           //"010110"中间的"0"放黑棋
        if (0 == BanMove(x_row, y_column - 2 + addr)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row][y_column - 2 + addr] = none;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row][y_column - 1 + addr] = black;           //"011010"中间的"0"放黑棋
        if (0 == BanMove(x_row, y_column - 1 + addr)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row][y_column - 1 + addr] = none;            //恢复"011010"中间的"0"
    }

    //'|'竖着方向禁手规则
    x = x_row - 4;        //获取刚下棋坐标的开始循环坐标
    y = y_column;         //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, i++) {
        if (x < 0 || x >= ROW) //超出棋盘则跳出
            continue;
        chess[i] = Board[x][y] + 48;
    }
    //检查"活三"的情况
    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    fakeflag = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        Board[x_row - 4 + addr][y_column] = black;   //"01110"的第一个"0"放黑棋
        if (0 != BanMove(x_row - 4 + addr, y_column)) {
            fakeflag = 1;
        }
        Board[x_row - 4 + addr][y_column] = none;   //恢复"01110"的第一个"0"
        Board[x_row + addr][y_column] = black;      //"01110"的第二个"0"放黑棋
        if (0 != BanMove(x_row + addr, y_column)) {
            fakeflag = 1;
        }
        Board[x_row + addr][y_column] = none;       //恢复"01110"的第二个"0"
        if (0 == fakeflag && x_row - 5 + addr >= 0 && 0 == Board[x_row - 5 + addr][y_column]) { //"01110"的前为空
            Board[x_row - 5 + addr][y_column] = black;
            if (0 == BanMove(x_row - 5 + addr, y_column)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row - 5 + addr][y_column] = none;
        }
        else if (0 == fakeflag && x_row + 1 + addr < ROW && 0 == Board[x_row + 1 + addr][y_column]) {//"01110"的后为空
            Board[x_row + 1 + addr][y_column] = black;
            if (0 == BanMove(x_row + 1 + addr, y_column)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row + 1 + addr][y_column] = none;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 2 + addr][y_column] = black;           //"010110"中间的"0"放黑棋
        if (0 == BanMove(x_row - 2 + addr, y_column)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row - 2 + addr][y_column] = none;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 1 + addr][y_column] = black;           //"011010"中间的"0"放黑棋
        if (0 == BanMove(x_row - 1 + addr, y_column)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row - 1 + addr][y_column] = none;            //恢复"011010"中间的"0"
    }

    //'/'斜杠方向禁手规则
    x = x_row - 4;          //获取刚下棋坐标的开始循环坐标
    y = y_column + 4;       //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, y--, i++) {
        if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) //超出棋盘则跳出
            continue;
        chess[i] = Board[x][y] + 48;
    }
    //检查"活三"的情况
    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    fakeflag = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        Board[x_row - 4 + addr][y_column + 4 - addr] = black;   //"01110"的第一个"0"放黑棋
        if (0 != BanMove(x_row - 4 + addr, y_column + 4 - addr)) {
            fakeflag = 1;
        }
        Board[x_row - 4 + addr][y_column + 4 - addr] = none;   //恢复"01110"的第一个"0"
        Board[x_row + addr][y_column - addr] = black;      //"01110"的第二个"0"放黑棋
        if (0 != BanMove(x_row + addr, y_column - addr)) {
            fakeflag = 1;
        }
        Board[x_row + addr][y_column - addr] = none;       //恢复"01110"的第二个"0"
        if (0 == fakeflag && x_row - 5 + addr >= 0 && y_column + 5 - addr < COLUMN && 0 == Board[x_row - 5 + addr][y_column + 5 - addr]) { //"01110"的前为空
            Board[x_row - 5 + addr][y_column + 5 - addr] = black;
            if (0 == BanMove(x_row - 5 + addr, y_column + 5 - addr)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row - 5 + addr][y_column + 5 - addr] = none;
        }
        else if (0 == fakeflag && x_row + 1 + addr < ROW && y_column - 1 - addr >= 0 && 0 == Board[x_row + 1 + addr][y_column - 1 - addr]) {//"01110"的后为空
            Board[x_row + 1 + addr][y_column - 1 - addr] = black;
            if (0 == BanMove(x_row + 1 + addr, y_column - 1 - addr)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row + 1 + addr][y_column - 1 - addr] = none;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 2 + addr][y_column + 2 - addr] = black;           //"010110"中间的"0"放黑棋
        if (0 == BanMove(x_row - 2 + addr, y_column + 2 - addr)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row - 2 + addr][y_column + 2 - addr] = none;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 1 + addr][y_column + 1 - addr] = black;           //"011010"中间的"0"放黑棋
        if (0 == BanMove(x_row - 1 + addr, y_column + 1 - addr)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row - 1 + addr][y_column + 1 - addr] = none;            //恢复"011010"中间的"0"
    }

    //'\'反斜杠方向禁手规则
    x = x_row - 4;          //获取刚下棋坐标的开始循环坐标
    y = y_column - 4;       //x是行; y是列;
    strcpy_s(chess, sizeof(chess) / sizeof(chess[0]), "444444444");//初始化落子周围棋盘状态
    for (i = 0; i < 9; x++, y++, i++) {
        if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) //超出棋盘则跳出
            continue;
        chess[i] = Board[x][y] + 48;
    }
    //检查"活三"的情况
    addr = strstr(chess, "01110") - chess; //配对字符串在原字符串的下标
    fakeflag = 0;                          //假活三标志位
    if (addr >= 0 && addr <= 9) {
        //检查"01110"的"0"是否禁手 && "01110"的前后是否有个为空,且不是禁手
        Board[x_row - 4 + addr][y_column - 4 + addr] = black;   //"01110"的第一个"0"放黑棋
        if (0 != BanMove(x_row - 4 + addr, y_column - 4 + addr)) {
            fakeflag = 1;
        }
        Board[x_row - 4 + addr][y_column - 4 + addr] = none;   //恢复"01110"的第一个"0"
        Board[x_row + addr][y_column + addr] = black;      //"01110"的第二个"0"放黑棋
        if (0 != BanMove(x_row + addr, y_column + addr)) {
            fakeflag = 1;
        }
        Board[x_row + addr][y_column + addr] = none;       //恢复"01110"的第二个"0"
        if (0 == fakeflag && x_row - 5 + addr >= 0 && y_column - 5 + addr >= 0 && 0 == Board[x_row - 5 + addr][y_column - 5 + addr]) { //"01110"的前为空
            Board[x_row - 5 + addr][y_column - 5 + addr] = black;
            if (0 == BanMove(x_row - 5 + addr, y_column - 5 + addr)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row - 5 + addr][y_column - 5 + addr] = none;
        }
        else if (0 == fakeflag && x_row + 1 + addr < ROW && y_column + 1 + addr < COLUMN && 0 == Board[x_row + 1 + addr][y_column + 1 + addr]) {//"01110"的后为空
            Board[x_row + 1 + addr][y_column + 1 + addr] = black;
            if (0 == BanMove(x_row + 1 + addr, y_column + 1 + addr)) { //检查此点是否为禁手
                count++;
            }
            Board[x_row + 1 + addr][y_column + 1 + addr] = none;
        }
    }
    //检查"跳三"的情况1
    addr = strstr(chess, "010110") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 2 + addr][y_column - 2 + addr] = black;           //"010110"中间的"0"放黑棋
        if (0 == BanMove(x_row - 2 + addr, y_column - 2 + addr)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row - 2 + addr][y_column - 2 + addr] = none;            //恢复"010110"中间的"0"
    }
    //检查"跳三"的情况2
    addr = strstr(chess, "011010") - chess;
    if (addr >= 0 && addr <= 9) {
        Board[x_row - 1 + addr][y_column - 1 + addr] = black;           //"011010"中间的"0"放黑棋
        if (0 == BanMove(x_row - 1 + addr, y_column + 1 - addr)) { //检查此点是否为禁手
            count++;
        }
        Board[x_row - 1 + addr][y_column - 1 + addr] = none;            //恢复"011010"中间的"0"
    }

    return count > 1 ? 1 : 0;  //若超过1个活三/跳三, 返回1; 否则返回0

}