//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";
  long_describe = "你顺着山路往上,路旁峭壁丛生,光线越来越暗,前面是一个极长的峡谷,极易
设伏,你心里不禁犯了嘀咕";
 	doorstr = 20; 
 	nextdirect = "northup";
 	npc_type="dalunsi";
 	level=2;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"sshanlu1", 
  "northup" : __DIR__"laotuxia",
      ]));
}