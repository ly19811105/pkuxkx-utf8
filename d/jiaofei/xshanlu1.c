//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";
  long_describe = "顺着山路过去便是小指峰，此处小路天成，似是罕有人迹，小路两侧密林将
阳光完全挡住，你不由暗暗心惊，赶忙加紧脚步。";
 	doorstr = 20; 
 	nextdirect = "northup";
 	npc_type="baituo";
 	level=1;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "west" : __DIR__"jiulongtang", 
  "northup" : __DIR__"xshanlu2",
      ]));
  set("outdoors", "tiezhang");    
}