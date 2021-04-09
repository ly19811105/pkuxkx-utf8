// Room: /d/mingjiao/damen.c

inherit ROOM;

void create()
{
	set("short", "山门");
	set("long", @LONG
     这是明教总舵的第二道关卡，地势更为险要，三面环山，中间
   有条小路，通向光明顶。
LONG
	);
	set("objects", ([ /* sizeof() == 2 */
 __DIR__"npc/ht_zhong" :2,
  "/kungfu/class/mingjiao/yanyuan.c" : 1,
]));
	set("outdoors", "mingjiao");
	set("exits", ([ /* sizeof() == 6 */
  "west" : __DIR__"jm-tan",
  "north" : __DIR__"hs-tan",
  "south" : __DIR__"rj-tan",
  "east" : __DIR__"lh-tan",
  "southdown" : __DIR__"shanlu2",
  "northup" : __DIR__"guangchang",
]));
	set("no_clean_up", 0);
     setup();
}
int valid_leave(object me, string dir)
{
    if (me->query("special_skill/sociability")) 
        return ::valid_leave(me, dir);  
    if (me->query("family/family_name")!="明教" && dir == "northup"
    && objectp(present("yan yuan", environment(me)))
    && living(present("yan yuan", environment(me))))
        return notify_fail("颜垣说道：“你非我教弟子，不能上山。”\n");
    return ::valid_leave(me, dir);
}

