//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "寺后广场";
  long_describe = 
"这里是寺后广场，四周树木(tree)林林总总，中间是一块空地，偶尔有一些和尚在这里习武";
 	doorstr = 90; 
 	nextdirect = "north";
 	npc_type="dalunsi";
 	level=5;
}

void create()
{
	::create();
	set("exits", ([ 
         "south" : __DIR__"mdadian",
         "north" : __DIR__"mhoushan",			
      ]));
}