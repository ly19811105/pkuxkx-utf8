// workroom.c -> for pretty's 书房

inherit ROOM;
#include <ansi.h>
int* a=({1,3,5,2,4,6});
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
        
        set("no_steal", 1);
        set("no_drop", 1);
        set("valid_startroom", 1);
        set("valid_sleeproom",1);
        set("sleep_room",1);

        set("exits", ([
                "west"   : __DIR__"zhanchang/entry",
                "south"   : "/d/rjdtest/rjdtest_begin",
                "southeast"   : "/d/wizard/wizard_room_whuan",
        ]));

        setup();
}

void init()
{
add_action("do_test","aaa");
add_action("do_out","out");
add_action("do_update","upd");
add_action("do_rnd","random");
add_action("do_testb","bbb");
}
void do_move()
{
shout(this_object()->name());
}
void do_rnd()
{
	int i;
	a+=({10});
	for (i=0;i<sizeof(a);i++)
		write(CHINESE_D->chinese_number(a[i]) + "\n");
}
int do_testb()
{
    object obj = new("/task/obj/mujian1");
    object cui = load_object("/d/city/npc/cui");
    obj->move(cui);
    return 1;
}
int do_testbold(string arg)
{
                        
                        int j;
                        mapping skills,skills_old;
                        mixed *skl;
                        object usr = this_player();

                        skills = usr->query_skills();
                        if (usr->query_temp("last_skill_checked") != 0)
                        {
                                skills_old = usr->query_temp("last_skill_checked");
                                skl = keys(skills);
                                for (j=0;j<sizeof(skills);j++)
                                {
                                        write(skills[skl[j]]-skills_old[skl[j]] + "\n");
                                        if (((int)(skills[skl[j]]) - (int)(skills_old[skl[j]])) > 5)
                                                write(skills[skl[j]] + ">5\n");
                                }
                        }
                        skills_old = ([]);
                        for (j=0;j<sizeof(skills);j++)
                                skills_old += ([skl[j]:skills[skl[j]]]);

                        usr->set_temp("last_skill_checked",skills_old);

                        return 1;



}
int do_update(string file)
{
object me = this_player();
object obj;
object* inv;
int i;
string err;

seteuid(ROOT_UID);
file = resolve_path(me->query("cwd"), file);
if( !sscanf(file, "%*s.c") ) file += ".c"; 
        me->set("cwf", file);

        if (obj = find_object(file)) {
                if( obj==environment(me) ) {
                        if( file_name(obj)==VOID_OB )
                        

                        i = sizeof(inv);
                        while(i--)
                                if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
                                else inv[i] = 0;
                }
                destruct(obj);
        }
        if (obj) return notify_fail("无法清除旧程式码。\n");

    write("重新编译 " + file + "：");
        err = catch( call_other(file, "???") );
        if (err)
                printf( "发生错误：\n%s\n", err );
        else {
                write("成功！\n");
                if( (i=sizeof(inv)) && (obj = find_object(file))) {
                        while(i--)
                                if( inv[i] && userp(inv[i]) ) inv[i]->move(obj, 1);
                }
        }

return 1;
}

int do_test(string arg)
{
int intday;
string weekday,mon,day,etc;
object me = this_player();
object obj;
int i;
//me->set("rank_info/rank",HIC+"【 永远的 】"+NOR);
if (!arg) write(time()+"\n");
if (arg) write(ctime(atoi(arg)) + "\n");
sscanf(ctime(time()),"%s %s %s %s",weekday,mon,day,etc);
write(weekday + "," + mon + "," + day + "\n");
sscanf(day,"%d",intday);
write((intday+1) + "\n");
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
