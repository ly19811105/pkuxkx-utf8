#include <command.h>
#include <ansi.h>

int main(object me, string arg)
{
        int i;
        object test;string *args,str;mixed result;
        seteuid(getuid());
        if( ! arg )
                return notify_fail("Synatx:test string \n");

        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
        arg = replace_string(arg, "$BLINK$", BLINK);

     //if(!rm("/temp.c")) return notify_fail("删除/temp.c失败！\n");
       if(!write_file("/temp.c","#include <ansi.h> \nmixed test_func(){return("+arg+");}\n",1)) 
              return notify_fail("档案创建失败！\n");
       if(test=find_object("/temp")) destruct(test);
       if(!test=load_object("/temp")) 
              return notify_fail("档案载入失败!\n");            
      if(!catch("/temp")) 
       tell_object(me,sprintf("执行的%s结果是:\n%O\n",arg,test->test_func()));
        return 1;
        
}

int help(object me)
{
    write(@HELP
指令格式：ttry <arg>
 
这个指令允许你直接检验一段表达式的运行，string必须合乎语法规范。
HELP
    );
        return 1;
}
