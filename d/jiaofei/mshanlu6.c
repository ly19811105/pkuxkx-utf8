//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "石阶";
  long_describe = "顺着钟声往上看去，似乎有一座庙宇在拇指峰的第一节与第二节之间。
你心中一喜，但钟声里杀伐之气甚重，你不由感觉庙中人并非善类";
 	doorstr = 20; 
 	nextdirect = "northup";
 	npc_type="shenlongdao";
 	level=1;
}

void create()
{
	::create();
	set("exits", ([ 
         "northup" : __DIR__"msimen",
         "southdown" : __DIR__"mshanlu5",	
      ]));
}