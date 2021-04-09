// Room: /d/jiaofei/mdshanlu1.c
// Date: by jason(残叶) Wed Dec 31 15:56:25 2008
inherit __DIR__"jiaofeiroom.c";


void jiaofei_init()
{
	short_name = "山路";
  long_describe = "这是一条下山的山路，可以通往中指峰。路的两旁长满了人高的杂草，\n看来平日人迹罕至。偶尔你可以听到狼的叫声";
  //门的强度,100的话需要1w点内力才能break。建议按等级递增。
 	doorstr = 30; 
 	//下一个房间的方向，走这个方向的玩家会受到基类的检查。比如必须没有了土匪，门也必须是开着的。
 	//其他方向就不检查了
 	nextdirect = "westdown";
 	//房间的等级，1最低，理论上没有最高。不过高了很恐怖。可以试验一下。
	level = 6;
	npc_type = "xingxiu";
}

void create()
{
	::create();
	set("exits", ([ /* sizeof() == 1 */
		  "westdown" : __DIR__"wdshanlu3",
		  "eastup" : __DIR__"wdshanlu1",
		]));
	set("outdoors", "tiezhang");
}
