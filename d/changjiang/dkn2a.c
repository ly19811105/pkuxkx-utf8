//Zine 25 Nov 2010

#include <room.h>
#include <ansi.h>
inherit ROOM;
#include "cj-pass.h"
string look_boat();
void create()
{
        set("short", "采石矶");
        set("long", @LONG
这里是长江南岸的渡口，南边就是重镇建康府了，大宋水师在这里放了几艘
快船(boat)。
LONG
        );
        set("exits", ([
             "west" : __DIR__"cjn8",
             "east" : __DIR__"dkn2",
        ]));
       
		set("item_desc",
        ([
        "boat":(:look_boat:),
        ]));
        set("boatvalue",80);
        set("pin","2a");
		set("dasong_shuishi_boat",1);
        set("objects", ([
        "/d/changjiang/npc/shaogong" : 1,
        ]) );

        set("no_clean_up", 0);
        set("outdoors", "changjiang");
//渡船属性
        set("boat","/d/changjiang/duchuan2a"); //船
        set("waittime",5); //等船时间
        set("arrivetime",10); //船行时间
        set("passtime",5);//放板时间
        set("destination","/d/changjiangnorth/dkb2a"); //目的地
        set("ticket","2a");
		set("npc_forbidden_dirs",({}));
        setup();
}
string look_boat()
{
	object me=this_player();
	if (!me->query("song/pro"))
	return "守船的水师士兵喝住了你：“再看，绑起来砍了！”\n";
	else if (DASONG_D->identification(me,({"水师大都督","龙卫上护军","龙卫上将军"}))||me->query("id")=="zine")
	return "你可以登上快船(board boat)，去到对岸！\n";
	else return "你不由感叹大宋国力日盛，水师壮大了，终有一日会恢复汉家故土。\n";
}
