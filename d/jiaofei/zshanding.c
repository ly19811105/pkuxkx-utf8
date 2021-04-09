// Room: /d/jiaofei/zshanding.c
// Date: by jason(残叶) Wed Dec 31 15:37:03 2008
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "中指峰山顶";
    long_describe = "这里是中指峰的山顶。从这里可以俯瞰到其余四座山峰。山脚下炊烟缭缭，\n隐约可以听到山歌在山间飘荡。好一派人间仙境。说是山顶，面前却还有一个\n小峰，又高出数丈去";
 	doorstr = 100; 
 	nextdirect = "north";
	level = 9;
	npc_type = "xingxiu";	
	islastroom = 1;
}

void create()
{
	::create();
	set("exits", ([ /* sizeof() == 2 */
		  "southdown" : __DIR__"zxuanya",
		  "north" : __DIR__"baoku",
		]));
	set("outdoors", "tiezhang");
}
