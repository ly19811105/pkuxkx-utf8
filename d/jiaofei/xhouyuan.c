//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "后院";
  long_describe = "这里是朱雀观的后院，经常有很多人在这里习武。后院的中间是一大块空
地，北边有一道门";
 	doorstr = 30; 
 	nextdirect = "westup";
 	npc_type="baituo";
 	level=2;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"xzhengdian", 
  "westup" : __DIR__"xfengding",
      ]));
  set("outdoors", "tiezhang");    
}