//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = HIW"白虎堂广场"NOR;
  long_describe = "这里是一个青花大理石铺成的广场，四周种着一些不知名的花，中央竖着一
根三米多高的旗杆，一面大旗随风飘扬，“"HIW"白虎堂"NOR"”三个大字写得气势磅礴，不禁让人叫好。";
 	doorstr = 30; 
 	nextdirect = "north";
 	npc_type="riyuejiao";
 	level=3;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"wshijie2", 
  "north" : __DIR__"wdating",
      ]));
}