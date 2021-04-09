// Room: /d/jiaofei/zshanlu4.c
// Date: by jason(残叶) Wed Dec 31 15:32:18 2008
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{

	short_name = "石阶";
    long_describe = "峰回路转，此处两侧林立着许多辘轳与绞索，不知有什么古怪用途。曲折
的石阶蜿蜒而上，回望旁侧诸峰隐隐约约，如不是血雨腥风的江湖，此处倒是
一个一览众山的好所在";

 	doorstr = 50; 
 	nextdirect = "northup";
	level = 5;
	npc_type = "riyuejiao";	
}

void create()
{
	::create();
	set("exits", ([ /* sizeof() == 2 */
		  "southdown" : __DIR__"zshanlu3",
		  "northup" : __DIR__"zshanlu5",
		]));
	set("outdoors", "tiezhang");
}
