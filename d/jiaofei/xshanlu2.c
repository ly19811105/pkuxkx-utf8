//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";
  long_describe = "顺着山路过去便是小指峰，此处小路天成，似是罕有人迹，小路两侧密林将
阳光完全挡住，你不由暗暗心惊，赶忙加紧脚步";
 	doorstr = 30; 
 	nextdirect = "northwest";
 	npc_type="baituo";
 	level=2;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"xshanlu1", 
  "northwest" : __DIR__"xshanlu3",
      ]));
  set("outdoors", "tiezhang");    
}