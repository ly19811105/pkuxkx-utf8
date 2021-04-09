// Room: /d/jiaofei/zshanlu2.c
// Date: by jason(残叶) Wed Dec 31 15:29:00 2008
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";

    long_describe = "这是通往主峰的山路，通道更加狭窄，几乎仅容一人一骑。向上望去甬路
笔直陡峭，如玉带隐在雾中，你不仅纳闷山路为什么修成这般狭窄平滑";

 	doorstr = 70; 
 	nextdirect = "northup";
	level = 3;
	npc_type = "shenlongjiao";	
}


void create()
{
	::create();
	set("exits", ([ /* sizeof() == 2 */
		  "southdown" : __DIR__"zshanlu1",
		  "northup" : __DIR__"zshanlu3",
		]));
	set("outdoors", "tiezhang");
}
