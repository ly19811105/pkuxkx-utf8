//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "后院";
  long_describe = "这里是青龙堂后院，是堂主的练功之所，中间是一块练武场，旁边整齐的
摆放着武器架，十八般武器样样俱全。院的另一边有一道门，应该是通向山顶。";
 	doorstr = 100; 
 	nextdirect = "northup";
 	npc_type="xingxiu";
 	level=8;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "south" : __DIR__"sqinglongtang", 
  "northup" : __DIR__"sshijie1",	
      ]));
}