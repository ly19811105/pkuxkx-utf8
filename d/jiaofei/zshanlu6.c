// Room: /d/jiaofei/zshanlu5.c
// Date: by jason(残叶) Wed Dec 31 15:34:04 2008
inherit __DIR__"jiaofeiroom.c";

void jiaofei_init()
{
	short_name = "石阶";
    long_describe = "石阶堪堪即尽，望上去似乎是一个大大的广场。铁掌峰无一处不是地势险
要，偏偏此地更显扼喉之姿，转身望去，来路细微几不可辨，居高临下令人胸
中激荡，真是一夫当关之所";
 	doorstr = 50; 
 	nextdirect = "north";
	level = 6;
	npc_type = "riyuejiao";	
}


void create()
{
	::create();
	set("exits", ([ /* sizeof() == 3 */
		  "southdown" : __DIR__"zshanlu5",
		  "north" : __DIR__"zguangchang",
		]));
	set("outdoors", "tiezhang");
}
