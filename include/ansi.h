#ifndef ANSI_H
#define ANSI_H

 
//	File	:  /include/ansi.h
//	Creator	:  Gothic@TMI-2  
//
//	The standard set of ANSI codes for mudlib use.
 
#define ESC	""
#define CSI	ESC + "["
 
                /*  Foreground Colors  */
 
#define BLK ESC+"[30m"          /* Black    黑*/
#define RED ESC+"[31m"          /* Red      酱红*/
#define GRN ESC+"[32m"          /* Green    浅绿*/
#define YEL ESC+"[33m"          /* Yellow   黄褐*/
#define BLU ESC+"[34m"          /* Blue     浅蓝*/
#define MAG ESC+"[35m"          /* Magenta  紫色*/
#define CYN ESC+"[36m"          /* Cyan     天蓝*/
#define WHT ESC+"[37m"          /* White    灰白*/
 
                /*   Hi Intensity Foreground Colors   */
#define HIK	ESC "[1;30m"	      /* Black    浅黑*/ 
#define HIR ESC+"[1;31m"        /* Red      红色*/
#define HIG ESC+"[1;32m"        /* Green    绿色*/
#define HIY ESC+"[1;33m"        /* Yellow   黄色*/
#define HIB ESC+"[1;34m"        /* Blue     蓝色*/
#define HIM ESC+"[1;35m"        /* Magenta  粉红*/
#define HIC ESC+"[1;36m"        /* Cyan     青色*/
#define HIW ESC+"[1;37m"        /* White    白色*/
#define BNK ESC+"[1;5m"         /* Blink    */

                /* High Intensity Background Colors  */

#define HBRED ESC+"[41;1m"       /* Red      */
#define HBGRN ESC+"[42;1m"       /* Green    */
#define HBYEL ESC+"[43;1m"       /* Yellow   */
#define HBBLU ESC+"[44;1m"       /* Blue     */
#define HBMAG ESC+"[45;1m"       /* Magenta  */
#define HBCYN ESC+"[46;1m"       /* Cyan     */
#define HBWHT ESC+"[47;1m"       /* White    */
 
                /*  Background Colors  */
 
#define BBLK ESC+"[40m"          /* Black    */
#define BRED ESC+"[41m"          /* Red      */
#define BGRN ESC+"[42m"          /* Green    */
#define BYEL ESC+"[43m"          /* Yellow   */
#define BBLU ESC+"[44m"          /* Blue     */
#define BMAG ESC+"[45m"          /* Magenta  */
#define BCYN ESC+"[46m"          /* Cyan     */
// #define BWHT ESC+"[47m"          /* White    */

#define NOR ESC+"[2;37;0m"      /* Puts everything back to normal */
 
/*  Additional ansi Esc codes added to ansi.h by Gothic  april 23,1993 */
/* Note, these are Esc codes for VT100 terminals, and emmulators */
/*       and they may not all work within the mud               */
 
#define BOLD ESC+"[1m"          /* Turn on bold mode */
#define LINEB		ESC+"[4m"			  // 底线
#define CLR ESC+"[2J"           /* Clear the screen  */
#define HOME ESC+"[H"           /* Send cursor to home position */
#define REF CLR+HOME            /* Clear screen and home cursor */
#define BIGTOP ESC+"#3"         /* Dbl height characters, top half */
#define BIGBOT ESC+"#4"         /* Dbl height characters, bottem half */
#define SAVEC ESC+"[s"           /* Save cursor position */
#define REST ESC+"[u"            /* Restore cursor to saved position */
#define SAVECA		ESC "7"				// Save cursor & attribute
#define RESTCA		ESC "8"				// Restore cursor & attribute

//#define REVINDEX ESC+"M"        /* Scroll screen in opposite direction */
#define SINGW ESC+"#5"          /* Normal, single-width characters */
#define DBL ESC+"#6"            /* Creates double-width characters */
#define FRTOP ESC+"[2;25r"      /* Freeze top line */
#define FRBOT ESC+"[1;24r"      /* Freeze bottom line */
#define UNFR ESC+"[r"           /* Unfreeze top and bottom lines */
#define BLINK ESC+"[5m"         /* Initialize blink mode */
#define U ESC+"[4m"             /* Initialize underscore mode */
#define REV ESC+"[7m"           /* Turns reverse video mode on */
#define HIREV ESC+"[1,7m"       /* Hi intensity reverse video  */

#define MV(x,y)     ESC "["+x+";"+y+"H"
#define UP(n)		ESC "["+n+"A"		// 游标上移 n 列(line),<已至萤幕顶端则无效>
#define DOWN(n)		ESC "["+n+"B"		// 游标下移 n 列(line),<已至萤幕底端则无效>
#define RIGHT(n)	ESC "["+n+"C"		// 游标向右移 n 列(line),<已至萤幕最右则无效>
#define LEFT(n)		ESC "["+n+"D"		// 游标向左移 n 列(line),<已至萤幕最左则无效>

#define R(t,b)		ESC "["+t+";"+b+"r" // 设置萤幕大小

// 一个用线画的行，专为Windows NT兼容而设计。
// by yiru@hero

#define SPACE_LINE "                \n"

#define DASH_LINE "------------------------------------------------------------------------"

#define DASH_LINE_LF "------------------------------------------------------------------------\n"


// 一个用线画的行，专为Windows NT兼容而设计。
// by yiru@hero

#define SPACE_LINE "                \n"

#define DASH_LINE "------------------------------------------------------------------------"

#define DASH_LINE_LF "------------------------------------------------------------------------\n"

// cursor correction by yiru@hero
#define CUR256D ESC+"[256D"          /* 前对齐 */

#endif
