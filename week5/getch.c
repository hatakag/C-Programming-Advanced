#include <termios.h>
#include <unistd.h>
#include <stdio.h>
 
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
 
/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
 
// nhap vao 1 dong chu, khi gap tu "ketthuc" thi dung lai ma khong can an enter
// Su dung ham getche();
int main(){
    char x;
    char kt[] = "ketthuc";
    int i = 0;
    while(1){
        x = getche();
        if (x == kt[i]) i++;
        else i = 0;
        if (i==7) break;
    }
    return 0;
}
