#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "btree.h"

static struct termios orig_termios;  /* TERMinal I/O Structure */

#define BACKSP_LINE "\b \b"
#define M 50

// BEGIN AUTO COMPLETED
int strhead(const char *a,const char *b,int x)	/*kiểm tra x chữ cái đầu của xâu có giống nhau ko */
{
	int i;
	for(i=0;i<x;i++)
		if((a[i])!=b[i]) return 0;
	return 1*(x>0);
}

void fatal(char *message)
{
	fprintf(stderr,"fatal error: %s\n",message);
	exit(1);
}

int tty_reset(void)
{
	/* flush and reset */
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios)<0) return -1;
	return 0;
}

/* exit handler for tty reset */
void tty_atexit(void)  /* NOTE: If the program terminates due to a signal   */
{                      /* this code will not run.  This is for exit()'s     */
	tty_reset();        /* only.  For resetting the terminal after a signal, */
}                      /* a signal handler which calls tty_reset is needed. */

/* reset tty - useful also for restoring the terminal when this process
   wishes to temporarily relinquish the tty
*/


/* Cài đặt ubuntu ở chế độ raw */
void tty_raw(void)
{
	struct termios raw;

	raw = orig_termios;  /* copy original and then modify below */

	/* input modes - clear indicated ones giving: no break, no CR to NL,
	   no parity check, no strip char, no start/stop output (sic) control */
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	/* output modes - clear giving: no post processing such as NL to CR+NL */
	raw.c_oflag &= ~(OPOST);

	/* control modes - set 8 bit chars */
	raw.c_cflag |= (CS8);

	/* local modes - clear giving: echoing off, canonical off (no erase with
	   backspace, ^U,...),  no extended functions, no signal chars (^Z,^C) */
	raw.c_lflag &= ~(ECHO |ICANON | IEXTEN | ISIG);

	/* control chars - set return condition: min number of bytes and timer */
	raw.c_cc[VMIN] = 5; raw.c_cc[VTIME] = 8; /* after 5 bytes or .8 seconds
												after first byte seen      */
	raw.c_cc[VMIN] = 0; raw.c_cc[VTIME] = 0; /* immediate - anything       */
	raw.c_cc[VMIN] = 2; raw.c_cc[VTIME] = 0; /* after two bytes, no timer  */
	raw.c_cc[VMIN] = 0; raw.c_cc[VTIME] = 8; /* after a byte or .8 seconds */

	/* put terminal in raw mode after flushing */
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw)<0) fatal("can't set raw mode");
}


/* Read and write from tty - this is just toy code!!
   Prints T on timeout, quits on q input, prints Z if z input, goes up
   if u input, prints * for any other input character
*/

int screenio(BTA* btfile,char *key)//hàm xử lý kí tự nhập từ bộ đệm gồm cả dấu tab
{
	BTint x;
	int bytesread,i=0,j,n;
  key[i]='\0';
  char c_in,back_space[]=BACKSP_LINE,sugg[M];
  for(;;)
    {
      bytesread=read(STDIN_FILENO,&c_in,1); /* Đọc 1 byte ki tự */
      if(bytesread<0) fatal("read error");
      if(bytesread==0) c_in=0;   /* Ko đọc đc byte nào thì bỏ qua */
      switch(c_in)         /* Khi đọc đc 1 byte */
	{
	case '\r' : printf("\n\r");  /* Khi gặp dấu ENTER hoặc ESC thì kết thúc */
	case 27 : return 0;
	case 127:					/*Xử lý khi bấm phím BACKSPACE */
	  i=strlen(key);
	  if(i>0)
	    {
	      key[--i]='\0';
	      bfndky(btfile,key,&x);
	      write(STDOUT_FILENO,back_space,3);
	    }
	  break;
	case '\t':	      /* Gợi ý và in ra từ  khi bấm phím TAB */
	  j=strlen(key);
	  while(j-->0) write(STDOUT_FILENO,back_space,3);
	  n=bnxtky(btfile,sugg,&x);
	  if(n==0&&strhead(key,sugg,i)!=0)
	    strcpy(key,sugg);
	  else
	    {
	      key[i]='\0';
	      bfndky(btfile,key,&x);
	    }
	  write(STDOUT_FILENO,key,strlen(key));
	  break;
	default:
	  if(' '<=c_in&&c_in<='~')
	    {		/* In ra các kí tự nhận vào như bt */
	      i=strlen(key);
	      key[i++]=tolower(c_in);
	      key[i]='\0';
	      bfndky(btfile,key,&x);
	      write(STDOUT_FILENO, &c_in, 1);
	    }
	}
    }
}



int tab_complete(BTA *btfile,char *key)    /* Hàm này kích hoạt terminal ở chế độ raw rồi xử lý kí tự*/
{
  /* check that input is from a tty */
  if (! isatty(STDIN_FILENO)) fatal("not on a tty");

  /* store current tty settings in orig_termios */
  if (tcgetattr(STDIN_FILENO,&orig_termios) < 0) fatal("can't get tty settings");

  /* register the tty reset with the exit handler */
  if (atexit(tty_atexit) != 0) fatal("atexit: can't register tty reset");

  tty_raw();      /* put tty in raw mode */
  screenio(btfile,key);
  tty_atexit();   /* run application code */
  return 0;       /* tty_atexit will restore terminal */
}
// END AUTO COMPLETE
