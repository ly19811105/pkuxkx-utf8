//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "老秃峡";
  long_describe = "这是一条峡谷,两边的峭壁如刀切一般,虽有突出的崖石(stone)可以落脚,但
如果轻功修为稍低,根本无法攀援。这里十分狭窄，只能一人通过";
 	doorstr = 20; 
 	nextdirect = "northup";
 	npc_type="dalunsi";
 	level=2;
 	
}

void create()
{
	::create();
	set("exits", ([ 
  "southdown" : __DIR__"laotuxia", 
  "northup" : __DIR__"laotuxia2",
      ]));
  set("max_user",1);    
}