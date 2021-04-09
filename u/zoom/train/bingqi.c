//bingqi.c
//by zoom
//2004.3.29

inherit ROOM;

void create()
{
    set("short", "兵器房");
    set("long", @LONG
这是新手学堂的兵器房，里面放着一些竹剑和木刀，看来是给新手
练习用的。挑件趁手的兵器(sword、blade)吧。
LONG
    );

    set("exits", ([
		"west" : __DIR__"lianwu1",
    ]));
    
    set("objects", ([
	__DIR__"npc/jiading" : 1,
    ]));

    set("blade_count",3);
    set("sword_count",3);

    setup();
}

void init()
{
	add_action("do_qu","qu");
        add_action("do_qu","na");
}

int do_qu(string arg)
{
	object ob,me;
	me = this_player();
	if(me->query("age")>14||me->query("combat_exp")>5000)
	{
		message_vision("$N都老大不小的人了，怎么也来捡这个便宜？\n",me);
		return 1;
	}
	if(!arg)
	{
		write("你想取什么兵器?\n");
		return 1;
	}
	if(arg=="sword")
	{
		if(query("sword_count")<=0)
		{
			message_vision("$N来晚了，你要的兵器没有了！\n",me);
			return 1;
		}
		ob=new("/clone/weapon/jian.c");
		ob->move(me);
		message_vision("$N从房里取了一柄长剑！\n",me);
		add("sword_count",-1);
		return 1;
	}
	else if(arg=="blade")
	{
		if(query("blade_count")<=0)
		{
			message_vision("$N来晚了，你要的兵器没有了！\n",me);
			return 1;
		}
		ob=new("/clone/weapon/gangdao.c");
		ob->move(me);
		message_vision("$N从房里取了一柄钢刀！\n",me);
		add("blade_count",-1);
		return 1;
	}
	else
	{
		message_vision("$N要取什么东西？\n",me);
		return 1;
	}
}
