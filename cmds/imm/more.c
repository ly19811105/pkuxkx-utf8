                 // cat.c
#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);
void start_more(string *msg, int);
void more(string cmd, string *msg, int line, int bufind, int);

int main(object me, string arg)
{
        string file;
        string tmp;
        string *readbuf;
        object ob;
        int showline=0, ind, ind2, fs;
        seteuid(geteuid(me));
        if (!arg) return notify_fail("指令格式 : more <档名>|<物件名> \n");
        if(sscanf(arg,"%s %d",tmp,showline)==2)
                arg=tmp;
        file = resolve_path(me->query("cwd"), arg);
        if( (fs=file_size(file)) < 0 ) {
                ob = present(arg, me);
                if( !ob ) ob = present(arg, environment(me));
                if( !ob ) return notify_fail("没有这个档案。\n");
                file = base_name(ob) + ".c";
        }
        
        ind=0;
        ind2=0;
        readbuf=allocate(5000);
        while(1)
        {
          readbuf[ind2]=read_file(file, ind+1, 23*80);
          fs=fs-sizeof(readbuf[ind2]);
          if ( !readbuf[ind2] ) 
          	break;
          ind=ind+23*80;
          ind2++;
        }
        start_more(readbuf, ind2);
        return 1;
}

void more(string cmd, string *msg, int line, int bufind, int totalseg)
{
    int i;
    string *text,*buf;
    text=explode(msg[bufind], "\n");
    switch(cmd) {
    case "n":
    	  line=0;
    	  bufind++;
    	  if( !msg[bufind] )
    	  	return;
    	  break;
    case "b":
        line = line - 46;
        if(line<0) line=0;
		write(ESC+"[1A"+ESC+"[200D"+ESC+"[K\n\n"); 
        for(i=line + 23; line < i;line++)
        write(text[line]+"\n");
        break;
    case "q":
        write(ESC+"[1A"+ESC+"[200D"+ESC+"[K\n\n");
        return;
    default:
        write(ESC+"[1A"+ESC+"[200D"+ESC+"[K");
        for(i=line + 23; line<sizeof(text) && line<i; line++)
            write(text[line] + "\n");
        if( line>=sizeof(text) ) 
        {
        	line=0;
        	bufind++;
        	if( !msg[bufind] )
            return;
        }
        break;
    }
    write(sprintf("== 未完继续 " HIY "%d/%d %d%%" NOR " == ("+HIC+"q"+NOR+" 离开，"+HIC+"b"+NOR+" 前一页，"+HIC+"n"+NOR+"下一段，其他继续下一页)\n",
        bufind+1, totalseg, (line*100/sizeof(text)) ));
    input_to("more", msg, line, bufind, totalseg);
}

void start_more(string *msg, int totalseg)
{
     write("\n");
     more("", msg, 0, 0, totalseg);
}

int help(object me)
{
write(@HELP
指令格式 : more <档案>|<物件名>
 
分页显示档案内容，对于大文件，由于采用23×80行为一段分页，
最后一段可能由于读取溢出导致多读取一部分数据，请自己注意。
 
more 模式下的指令:
q      : 离开 more.
b      : 显示前一页的内容.
[ENTER]: 显示下一页的内容.

HELP
    );
    return 1;
}

