//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "石阶";
  long_describe = "这是用雕花大理石做成的石阶，蜿蜒而上，你抬头望去，前面似乎有一个广
场，恍惚能听到少女的娇叱之声。";
 	doorstr = 30; 
 	nextdirect = "northup";
 	npc_type="riyuejiao";
 	level=3;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"wxiaolu5", 
  "northup" : __DIR__"wshijie2",
      ]));
}