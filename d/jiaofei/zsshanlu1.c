// Room: /d/jiaofei/zmshanlu1.c
// Date: by jason(残叶) Wed Dec 31 15:59:31 2008
inherit __DIR__"jiaofeiroom.c";

void jiaofei_init()
{
	short_name = "山路";
  long_describe = "这是中指峰一条上山的山路。\n和拇指峰截然不同的是，这里似乎刻意进行了修筑，\n道路格外艰险。绝对的一夫当关万夫莫开之地";
  //门的强度,100的话需要1w点内力才能break。建议按等级递增。
 	doorstr = 40; 
 	//下一个房间的方向，走这个方向的玩家会受到基类的检查。比如必须没有了土匪，门也必须是开着的。
 	//其他方向就不检查了
 	nextdirect = "eastup";
 	//房间的等级，1最低，理论上没有最高。不过高了很恐怖。可以试验一下。
	level = 6;
	npc_type = "riyuejiao";
}


void create()
{
	::create();
	set("exits", ([ /* sizeof() == 2 */
		  "eastup" : __DIR__"zsshanlu2",
		  "westdown" : __DIR__"sdshanlu3",
		]));
}
