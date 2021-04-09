// Room: /d/jiaofei/zshanlu1.c
// Date: by jason(残叶) Wed Dec 31 15:23:44 2008
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";

    long_describe = "这是通往主峰的山路，路势狭窄阴森，两侧陡立石壁隐然有斑斑血迹。奇
怪的是路面笔直向上，居然颇为平滑，居中两道浅浅的痕迹，不知因何而留";

 	doorstr = 50; 
 	nextdirect = "northup";
	level = 5;
	npc_type = "baituo";	
}

void create()
{
	::create();
	set("exits", ([ /* sizeof() == 2 */
		  "northup" : __DIR__"zshanlu2",
		  "south" : __DIR__"jiulongtang",
		]));
	set("outdoors", "tiezhang");
}
