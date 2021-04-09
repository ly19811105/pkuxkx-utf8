//Cracked by Roath
// Room: /d/dali/nanbei.c

inherit ROOM;

void create()
{
	set("short", "南诏德化碑");
	set("long", @LONG
南诏阁逻风于大唐天宝年间，同大唐两次交战，歼唐军十六万。过后，阁逻
风有悔意，为一时交恶，“岂顾前非，而忘大礼”。于是，派人收拾唐军阵亡将
士，“祭而葬之，以存恩旧”，同时，令人撰文，详记天宝战争的近因和结果，
表达不得已而叛唐的苦衷，将它刻成巨碑（bei），于天宝十一年立于王都
太和城国门外。
LONG);

        set("item_desc", ([
                "bei" : "这是一块古碑，不过看起来似乎有些什么古怪。\n",
                ]));

	set("exits", ([
		"northeast" : __DIR__"guandao.c",
		"south" : __DIR__"taihec.c",
		]));
	set("cost", 2);
	set("no_clean_up", 0);
	set("outdoors", "dali");
	setup();
}
void init()
{
        add_action("do_push", "push");
        add_action("do_push", "tui");
}

int valid_leave(object me, string dir)
{
//    if ((dir == "west")&& !userp(me)) return 0;
    return ::valid_leave(me, dir);
}

int do_push(string arg)
{
        object me;
        mapping fam;

        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="bei" || arg=="古碑")
        {
                        message_vision("$N推开石碑，只见泥沙纷纷跌落，地面上露出一个小洞。\n", me);
                        message("vision",
                                me->name() + "运起丐帮缩骨功，一弯腰往洞里钻了进去。\n",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/dlandao6");
                        message("vision",
                                me->name() + "从洞里走了进来。\n",
                                environment(me), ({me}) );
                        return 1;
        }
}       

