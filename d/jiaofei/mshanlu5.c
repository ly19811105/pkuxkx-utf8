//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "石阶";
  long_describe = "你顺着石阶而行，偶尔听见几声钟鸣，你心中啧啧称奇，连忙加紧速度，想要一探究竟";
 	doorstr = 20; 
 	nextdirect = "northup";
 	npc_type="shenlongdao";
 	level=1;
}

void create()
{
	::create();
	set("exits", ([ 
         "northup" : __DIR__"mshanlu6",
         "southdown" : __DIR__"mshanlu4",	
      ]));
}