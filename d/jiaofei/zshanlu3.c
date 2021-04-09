// Room: /d/jiaofei/zshanlu3.c
// Date: by jason(残叶) Wed Dec 31 15:30:45 2008
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{

	short_name = "山路";
    long_describe = "山路似乎已经到了尽头，你耳边隐隐传来阵阵轰鸣，便如甚么巨大物事在
头顶滚动。脚下山路随渐浓的杀气震颤，云雾的彼端仿佛潜着一群食人的恶魔";

 	doorstr = 20; 
 	nextdirect = "northup";
	level = 6;
	npc_type = "riyuejiao";	
}

void create()
{
	::create();
	set("exits", ([ /* sizeof() == 2 */
		  "southdown" : __DIR__"zshanlu2",
		  "northup" : __DIR__"zshanlu4",
		]));
	set("outdoors", "tiezhang");
}
