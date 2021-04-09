// workroom.c -> for pretty's 书房

inherit ROOM;
#include <ansi.h>

void create()
{
     set("short","桂桂窝");
        set("long", @LONG
一进入这间小屋，你不禁眼前为之一亮。小屋不大，却布置得
雅致而脱俗。屋内没有那些多余的东西，墙上几幅写意的山水画，
窗前的一张檀木案，一张圆凳以及靠墙的一个小书架构成了这间书
房的全部。窗外几竿绿竹掩映，更为这间小屋增添了无数的情趣。
在这里，你会忘记尘世中的一切。
LONG
        );
        set("objects",([
                "/u/icer/obj/yinzhen":1,
                ]));
 
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_drop", 1);
        set("valid_startroom", 1);

        set("exits", ([
              "east" :__DIR__"workroom.c",
        ]));

        setup();
}

void init()
{
add_action("do_test","aaa");
//  add_action("do_out","out");
}
int do_test(string arg)
{
object me = this_player();
object obj;
int i;
if (!arg) write(time()+"\n");
if (arg) write(ctime(atoi(arg)) + "\n");
return 1;
}

int do_out(string arg)
{
        object where;
        string path;
        string longstr;
        string *sep;
        object me = this_player(1);
        where = environment(me);
        if (arg) return 0;
//   me->set("job_title",HIW"邪派"BNK + HIR"妖女"NOR);
        tell_object(me,(string)file_name(where));
        path = me->query_save_file();
        sep = explode(path,"/");
        tell_object(me,sep[sizeof(sep)-1]);
      longstr = "\n
$HIW$              , ,   _)\\      ;--.
$BNK$$HIR$       .$HIY$ '$HIW$ . $NOR$$HIW$  \\_\\-'   |   .'    \\
$BNK$$HIC$      -$HIG$=$NOR$$HIB$ *$BNK$$CYN$ =$HIM$-$NOR$$HIW$  (.-,    /  /       |
$BNK$$MAG$       '$GRN$ .$NOR$$HIW$\\$BNK$$HIR$'$NOR$$HIW$    ). `))/ .'   _/\\ /
           \\_   \\_  /( /     \\ /(
           /_\\ .--'   `-.    //  \\
           ||\\/        , '._//    |
           ||/ /`(_ (_,;`-._/     /
           \\_.'$MAG$-''$HIW$)   /`\\       .'
$MAG$          /   ('$HIW$.' .  |  ;.   /`
$MAG$          \\    `-'',-.$HIW$|   `.(
$MAG$           '-.,__,._., `'\_$HIW$  ' 
              |   | / $MAG$\\    '`;.,_...$HIW$
              |   |' $MAG$  '...      .`$HIW$
           __/'  /   $MAG$      `._  ($HIW$
       _ .'  _.-`    $MAG$         ``\"`$HIW$
    _.` `.-;`/
   /_.-'` / /
         | /
        ( /
       /_/$NOR$\n";




        longstr = replace_string(longstr, "$BLK$", BLK);
        longstr = replace_string(longstr, "$RED$", RED);
        longstr = replace_string(longstr, "$GRN$", GRN);
        longstr = replace_string(longstr, "$YEL$", YEL);
        longstr = replace_string(longstr, "$BLU$", BLU);
        longstr = replace_string(longstr, "$MAG$", MAG);
        longstr = replace_string(longstr, "$CYN$", CYN);
        longstr = replace_string(longstr, "$WHT$", WHT);
        longstr = replace_string(longstr, "$HIR$", HIR);
        longstr = replace_string(longstr, "$HIG$", HIG);
        longstr = replace_string(longstr, "$HIY$", HIY);
        longstr = replace_string(longstr, "$HIB$", HIB);
        longstr = replace_string(longstr, "$HIM$", HIM);
        longstr = replace_string(longstr, "$HIC$", HIC);
        longstr = replace_string(longstr, "$HIW$", HIW);
        longstr = replace_string(longstr, "$NOR$", NOR);
        longstr = replace_string(longstr, "$BNK$", BNK);
        longstr = replace_string(longstr, "$REV$", REV);

        me->set("long",longstr);

        me->move("/d/city/guangchang");
        return 1;
}
