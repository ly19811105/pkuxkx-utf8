// Room: /d/jiaofei/mdshanlu1.c
// Date: by jason(残叶) Wed Dec 31 15:56:25 2008
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山顶";
  long_describe = "这里是中指峰的山顶，奇怪的是面前还有一个大土包";
  //门的强度,100的话需要1w点内力才能break。建议按等级递增。
 	doorstr = 100; 
 	//下一个房间的方向，走这个方向的玩家会受到基类的检查。比如必须没有了土匪，门也必须是开着的。
 	//其他方向就不检查了
 	nextdirect = "east";
 	//房间的等级，1最低，理论上没有最高。不过高了很恐怖。可以试验一下。
	level = 8;
	npc_type = "xingxiu";
	islastroom = 1;
}

void create()
{
	::create();
	set("exits", ([ /* sizeof() == 1 */
		  "east" : __DIR__"baoku",
		  "westdown" : __DIR__"zsshanlu2",
		]));
	set("outdoors", "tiezhang");
}
