// Room: /d/jiaofei/zshanlu5.c
// Date: by jason(残叶) Wed Dec 31 15:34:04 2008
inherit __DIR__"jiaofeiroom.c";

void jiaofei_init()
{
	short_name = "石阶";
    long_describe = "石阶狭窄光滑，想来中指峰为铁掌五岳之首，帮中机密要地尽集于此，铁
掌帮众自然日常巡逻慎密。狭窄石阶两侧便是深远万仞，一望下去，不由令人
头晕目眩";
 	doorstr = 80; 
 	nextdirect = "up";
	level = 4;
	npc_type = "riyuejiao";	
}


void create()
{
	::create();
	set("exits", ([ /* sizeof() == 3 */
		  "southdown" : __DIR__"zshanlu4",
		  "northup" : __DIR__"zshanlu6",
		]));
	set("outdoors", "tiezhang");
}
