//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "石阶";
  long_describe = "你顺着石阶而行，隐隐约约见到前方似乎有一处道观，于是加快速度，想上
前一探究竟。";
 	doorstr = 40; 
 	nextdirect = "northup";
 	npc_type="baituo";
 	level=2;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"xshijie1", 
  "northup" : __DIR__"xzhuqueguan",
      ]));
  set("outdoors", "tiezhang");    
}