//anbian.c
//by zoom
//2004.3.29

inherit ROOM;

void create()
{
    set("short", "岸边");
    set("long", @LONG
这里是池塘的北边，俯身就能划到水，因为是岸边，没长荷花，
却可以清楚地看到小鱼儿(fish)。
LONG
    );
        set("item_desc", ([
                "fish"   : "游来游去的小鱼儿，不知道能不能抓住(catch)。\n",
                ]));

    set("exits", ([
                "southeast" : __DIR__"xiaoqiao",
    ]));
    
    set("outdoors", "train");
    setup();

}

void init()
{
        add_action("do_catch", "catch");
}

int do_catch(string arg)
{
        object me,fish;
        me=this_player();
        if(!arg) return notify_fail("你要抓什么？");
        if(arg == "fish")
 	{
		if(!me->query_temp("mark/catchfish_train"))
			return notify_fail("这么可爱的小家伙不要伤害它吧");
		else if(random(3)>1)
		{
                        message_vision( "\n$N将小鱼捉了起来。\n",this_player());
                        fish=new(__DIR__"obj/fish.c");
                        fish->move(me); 
                        return 1;
                }
		else
		        message_vision( "\n$N捉来捉去,可是捉不着。\n",this_player());
		
	}
        return 1;
}  