//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "广场";
  long_describe = "这里是一个青石铺成的广场，广场中央竖着一根三米多高的旗杆，一面大旗
随风飘扬，“"HIC"青龙堂"NOR"”三个大字写得气势磅礴，不禁让人叫好。往里走便是青龙堂了";
 	doorstr = 50; 
 	nextdirect = "north";
 	npc_type="dalunsi";
 	level=4;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "south" : __DIR__"sshanlu3", 
  "north" : __DIR__"sdayuan",
      ]));
}