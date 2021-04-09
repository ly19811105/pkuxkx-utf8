
inherit ROOM;
void create()
{
	set("short", "帅府大门");
	set("long", @LONG
	这里是襄阳驻军的帅府的大门,郭靖统领襄阳守军,指挥所就在这里.
     这里戒备森严,不可靠的人是绝对不能放进去的.
LONG
	);

	set("exits", ([
		"south" : __DIR__"sfdating",
		"north" : __DIR__"xywest2"          
	]));

	set("objects", ([
		__DIR__"npc/shoujun" : 4,
        ]));

	setup();
}
int valid_leave(object me, string dir)
{        
    int i;
    object *ob, xytaskd;
    if (me->query("special_skill/sociability")) 
        return ::valid_leave(me, dir);        
    if( dir != "south" || me->query_temp("citan") || me->query_temp("女佣") )
        return ::valid_leave(me, dir);
    xytaskd=load_object("/adm/daemons/xytaskd.c");
    if( xytaskd->query("begin") || me->query_temp("xytaskd/number") || me->query_temp("xytaskd/qianhuzhang"))
        return ::valid_leave(me, dir);
    ob = all_inventory( environment( me ));
    for(i=0; i<sizeof(ob); i++) 
    {
        if( living(ob[i]) && ob[i]->query("id") == "shou jun" )
            return notify_fail("守军伸手拦住你说:此乃军机重地,岂能擅闯？\n");
    }
    return ::valid_leave(me, dir);
}


