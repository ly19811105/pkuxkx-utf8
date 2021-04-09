//Created By Pal
//cometh@tom.com
//2003.10.5
#pragma save_binary

#include <ansi.h>
inherit ROOM;

mapping *itemlist = ({
([	"name":"沙发",
	"id":"sofa",//买的时候的名称
	"realid":"big sofa",//买出来以后物品名称
	"value":2000,
	"unit":"张",
	"file":"/data/home/std_file/obj/stool",//属于凳子一类的
	"dailycost":20,//每天损耗
	"maxlife":500//寿命
]),
([	"name":"席梦思",
	"id":"bed",
	"realid":"soft bed",
	"value":3000,
	"unit":"张",
	"file":"/data/home/std_file/obj/bed",//属于床一类的
	"dailycost":20,//每天损耗
	"maxlife":1000//寿命
]),
});
void create()
{
	set("short", "北大侠客行家具店");
	set("long", @LONG
这里是北大侠客行的家具店总店，主要出售较大件的家具，
你可以看到各种各样的橱柜等等。
LONG
	);
	set("exits", ([
		"south":__DIR__"center",
		]));
	set("objects", ([
//房间有的物品
		]));
	setup();
}

void init()
{
	object me;
	string str,filename;

	me = this_player();
	str=me->query("id");

	filename="/data/home/file/"+str[0..0]+"/"+str+"/"+"gate.c";
	if(file_size(filename)>0)
	{
		add_action("do_buy","buy");
		add_action("do_buy","xuangou");
	}
	add_action("do_list","list");
	add_action("do_list","chakan");
}

string value_string(int value)
{
    if( value < 1 ) value = 1;
    else if( value < 100 )
	return chinese_number(value) + "文钱";
    else if( value < 10000)
	return chinese_number(value/100) + "两白银"
	+ (value%100? "又" + chinese_number(value%100) + "文钱": "");
    else
	return chinese_number(value/10000) + "两黄金" + (value%10000?chinese_number((value%10000)/100) + "两白银":"")
	+ (value%100? "又" + chinese_number(value%100) + "文钱": "");
}

int do_buy(string arg)
{
	mapping goods,*item,buyitem;
	string str,name;
	object me;
	int value,afford,i,goodsfind;

	if( !arg )
		return notify_fail("你要买什么？\n");

	me=this_player();
	goodsfind=0;
	for(i=0;i<sizeof(itemlist);i++)
	{
		goods=itemlist[i];
		if(arg==goods["id"])
		{
			goodsfind=1;
			break;
		}
	}
	if( !goodsfind )
		return notify_fail("这里没有你想要买的东西。\n");
	value=goods["value"]*100;//把silver为单位的转化为coin单位
	if( !(afford=me->can_afford(value)) )
	{
		write("你没有足够的钱。\n");
		return 1; 
	}
	else if( afford == 2 )
	{
		write("你没有足够的零钱，而银票又没人找得开。\n");
		return 1;
	}

	item=me->query_temp("selfitem");
	if(!item) item = ({});
	me->delete_temp("selfitem");
	buyitem=([ ]);
	buyitem=goods;
    item += ({buyitem});
	me->set_temp("selfitem",item);
	me->pay_money(value);
	tell_object(me,sprintf("你从家具店买下一%s%s\n",goods["unit"],goods["name"]));

	return 1;
}

int do_list()
{
	mapping goods;
	string str,name;
	int i;
	str="";
	for(i=0;i<sizeof(itemlist);i++)
	{
		goods=itemlist[i];
		name=sprintf("%s(%s)",goods["name"],goods["id"]);
		str += sprintf("%-30s：%-20s\n",name,value_string(goods["value"]*100));
	}
	tell_object(this_player(),str);
	return 1;
}