//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";
  long_describe = "顺着山路过去便是小指峰，此处小路天成，似是罕有人迹。声声虫鸣更显得这里冷幽可怖";
 	doorstr = 30; 
 	nextdirect = "northup";
 	npc_type="baituo";
 	level=2;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"xzhengdian", 
  "northup" : __DIR__"xfengding",
      ]));
  set("outdoors", "tiezhang");    
}