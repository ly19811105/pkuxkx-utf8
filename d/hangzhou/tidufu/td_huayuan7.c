// Room: /hangzhou/td_huayuan7.c
// hubo 2008/4/19

inherit "/d/hangzhou/song_room";
#include <ansi.h>
#include "/d/hangzhou/huayuan.h"
void create()
{
        set("short", "花园");
        set("long", @LONG
杭州提督府的花园，种着五颜六色的鲜花，香味扑鼻，另人陶醉。你一走进来，
感觉失去了方向。心里有种不祥的预感。这里的花丛（huacong）比别的地方都
茂盛。
LONG);
        set("outdoors", "hangzhou");
        set("exits", ([     
                "east" : __DIR__"td_huayuan8",
                "west" : __DIR__"td_huayuan"+(random(8)+2),
                "south" : __DIR__"td_huayuan"+(random(8)+2),
                "north" : __DIR__"td_huayuan"+(random(8)+2),     
]));
     	set("no_newbie_task",1);
   set("item_desc", ([ 
   "huacong" : "这里的花丛远比别的地方茂密，不知道是否可以拨(bo)开看看。\n",  
   ]));      	
   setup();
}
void init()  
{
        add_action("do_bo", "bo");
}

int do_bo(string arg)
{
  if(!arg||arg!="huacong") 
  return 0;
  message_vision("$N用手拨开了花从，竟然发现有一条很小的路。\n",this_player());
  set("exits/enter",__DIR__"td_xiaodao1.c");
  
  remove_call_out("close");
  call_out("close",5,this_object());
 return 1;
 }

void close(object room)
{
        message("vision","只见一阵风吹过，这条道又没有了。\n", room);
  room->delete("exits/enter");
}