//修正两个bug   boost 2008-08-28
// 1 不能list，原因在于box内物品出现断层，原因未知，现在修改list解决问题
// 2 sell的时候因不能超过500件物品而回头覆盖原有物品时，原物品并未dest，可能会造成物品过多
// 现在改为sell到上限(MAX_SELL)的时候，砍掉最老的一半，剩下的一半顶替老的一半
// modified by Vast @ 2009.3.22  修改了List的显示方式，给list增加了参数，可以分类显示
#include <ansi.h>
inherit ROOM;
inherit "/inherit/room/rbz.c";

void create()
{
    set("short", HIY"荣宝斋"NOR);

	set("long", CYN @LONG
这里是京城里最有名的珠宝店在扬州的分店。店主人见多识广，收藏的宝物
也颇不少，除了当世的名家珍品，还时常有些宝石兵器之类的。墙上挂着一块牌
子(sign)，牌子旁边贴着一张【最新公告】（paizi）。
LONG NOR);

	set("exits", ([
		"north" : __DIR__"dangpu",
	]));
	set("objects", ([
		"/d/beijing/npc/liulaoban":1,
	]));

	set("item_desc", ([
		"sign" : "公平交易，童叟无欺\n

			注意：本店只经营珠宝，并提供珠宝保管服务，按珠宝价值收取20%手续费。\n
			sell        卖
			buy         买
			pawn        当
			redeem      赎
			value       估价
			list        列表\n",
			
		"paizi":"         list 命令可以加以下参数，来显示具体的某类物品，并能看到较为详细的属性\n
			weapons  :   显示所有武器类物品列表，并可以看到武器的伤害数值
			armors   ：  显示所有防具类物品列表，并可以看到防具的防御数值
			gem      ：  显示所有宝石列表
      			sword/blade/staff/whip/axe/spear/hammer/halberd/throwing/dagger
               			:    显示具体某类武器类物品列表
			armor/boots/cloth/hands/head/shield/surcoat/waist/wrists/finger/neck
			         ：  显示具体某类防具类物品列表\n",
	]));
	set("no_beg",1);
	set("no_steal", 1);
	set("least_msg", 1);
//	set("no_fight", 1);
//	set("no_perform", 1);
    setup();
}

// no clean up at hockshop to prevent items lose.
int clean_up()
{
	return 0;
}
