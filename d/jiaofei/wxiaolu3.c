//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "小路";
  long_describe = "这是一条通往山顶的小路，路两旁奇花异草，馥郁芬芳，显是有人打理";
 	doorstr = 30; 
 	nextdirect = "northup";
 	npc_type="baituo";
 	level=3;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"wxiaolu2", 
  "northup" : __DIR__"wxiaolu4",
      ]));
}