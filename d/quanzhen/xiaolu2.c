// Room: /d/quanzhen/xiaolu2.c

inherit ROOM;

void create()
{
	set("short", "小树林");
	set("long", @LONG
这是一片茂密的小树林，郁郁葱葱的长着许多树木(shu) ，北边好象有一片
空地。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"south" : __DIR__"xiaolu1.c",

]));
        set("objects",([
        __DIR__"npc/bee.c": 2,
     ]));
	setup();
	
}

void init()
{
 add_action("do_bo","bo");
}
 
int do_bo(string arg)
{
  if(!arg||arg!="shu") 
  return 0;
  message_vision("$N用手拨开了树从，竟然发现有一条通道.\n",this_player());
  set("exits/north",__DIR__"fengchang.c");
  
  remove_call_out("close");
  call_out("close",5,this_object());
 return 1;
 }

void close(object room)
{
        message("vision","只见一阵风吹过，这条道又没有了。\n", room);
  room->delete("exits/north");
}
