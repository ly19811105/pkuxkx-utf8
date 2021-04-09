//Create by whuan@pkuxkx
//铁掌帮
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "寺门";
  long_describe = 
"这是一座古刹，大门两边却摆放着黑白无常的石像，阴森恐怖，寺中偶尔有
钟声传出，却并无诵经之声。你不禁感觉这里处处透着邪门，抬头一看，寺门上
的匾额写着三个大字：兰若寺。";
 	doorstr = 20; 
 	nextdirect = "north";
 	npc_type="riyuejiao";
 	level=1;
}

void create()
{
	::create();
	set("exits", ([ 
         "north" : __DIR__"mguangchang",
         "southdown" : __DIR__"mshanlu6",	
      ]));
}