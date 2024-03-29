inherit ROOM;

void create()
{
	set("short", "独尊厅大门");
        set("long",@LONG
这就是通向『灵鹫宫』独尊厅的大门。大门左右各有一头石雕的猛鹫，
高达三丈有余，尖喙巨爪，神骏非凡，栩栩如生，似乎随时要腾空而去。
堡门半掩，门口站着两个俊俏的姑娘。
LONG );
        set("outdoors", "lingjiu");
        set("exits", ([
		"north" : __DIR__"zhengting",
		"south" : __DIR__"dadao2",
        ]));
	set("objects",([
        __DIR__"npc/lanjian" : 1,
        __DIR__"npc/meijian" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
    if (me->query("special_skill/sociability")) 
        return ::valid_leave(me, dir);  
    if (!userp(me))
        return ::valid_leave(me, dir);  
	if ((dir == "north") && ((string)me->query("family/family_name") != "灵鹫宫")
        && (!me->query_temp("lingjiu/ask_apprentice")))
	{
	    if (objectp(present("mei jian", environment(me)))
	        && living(present("mei jian", environment(me))))
	        return notify_fail	("梅剑伸手拦住你，说道：“非灵鹫宫弟子请回！”\n");
	    else if (objectp(present("lan jian", environment(me)))
	        && living(present("lan jian", environment(me))))
	        return notify_fail	("兰剑伸手拦住你，说道：“非灵鹫宫弟子请回！”\n");
	}
	return ::valid_leave(me, dir);
}
