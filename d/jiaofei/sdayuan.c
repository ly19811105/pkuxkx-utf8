//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = HIC"青龙堂大院"NOR;
  long_describe = "这里便是青龙堂的大院，院里整齐的排着一些木人桩和沙包供帮众练武之
用，东西两边分别是几间厢房";
 	doorstr = 50; 
 	nextdirect = "north";
 	npc_type="shenlongdao";
 	level=4;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "south" : __DIR__"sguangchang", 
  "north" : __DIR__"sqinglongtang",
  "west" : __DIR__"sxixiangfang",
  "east" : __DIR__"sdongxiangfang",		
      ]));
}