//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";
  long_describe = "顺着山路过去便是拇指峰，此处小路天成，似是罕有人迹，你不由暗暗心惊，赶忙加紧脚步";
 	doorstr = 20; 
 	nextdirect = "north";
 	npc_type="dalunsi";
 	level=1;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southeast" : __DIR__"xiaoting", 
  "north" : __DIR__"mshanlu2",
      ]));
}