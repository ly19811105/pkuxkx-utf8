//Create by whuan@pkuxkx
//铁掌帮
#include <ansi.h>
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";
  long_describe = "你终于走出了峡谷，眼前一亮，心中也豁然开朗。前面不远处便是一个广
场，一杆大旗随风飘扬，你仔细辨认，似乎写着“"+HIC"青龙堂"NOR"”";
 	doorstr = 50; 
 	nextdirect = "north";
 	npc_type="dalunsi";
 	level=4;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"laotuxia2", 
  "north" : __DIR__"sguangchang",
      ]));
}