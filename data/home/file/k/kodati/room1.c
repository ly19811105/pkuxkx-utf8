//By Pal
//新房间模板
//所有的动作都要加上判断，看玩家是否有能力创建这个房间
#pragma save_binary

#include <ansi.h>
inherit ROOM;
#include "/data/home/std_file/stdroom.c"
void create()
{
	set("short", "亦狂山庄");//房间短描述，模板为ROOM_NAME
	set("long", @LONG
这是一个新的房间，你可以对它进行装修。
LONG
	);
	set("valid_startroom",0);
	set("host","kodati");//所有者，模板里固定为pkuxkx
	set("roomvalue",50);//房间价值，初始为50，降到0就倒了
	set("room_ok",1);//是否好的房间
	set("selfcreate",1);
	set("exits", ([
//房间出口
		]));
	set("objects", ([
//房间有的物品
		]));
	restore();
	setup();
}
