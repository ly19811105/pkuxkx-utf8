//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = HIC"青龙堂"NOR;
  long_describe = "这里是青龙堂的大厅，正面墙壁上镶着一条青龙，云飞龙腾，惟妙惟肖。
迎面的太师椅上坐着一位老者，赫然便是堂主";
 	doorstr = 100; 
 	nextdirect = "north";
 	npc_type="dalunsi";
 	level=6;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "south" : __DIR__"sdayuan", 
  "north" : __DIR__"shouyuan",	
      ]));
}