//By Pal
//新房间模板
//所有的动作都要加上判断，看玩家是否有能力创建这个房间
//created by Pal
//cometh@tom.com
//2003.10.8
//这里就是yom得palzt了。
#pragma save_binary

#include <ansi.h>
inherit ROOM;
#include "/data/home/std_file/stdgate.c"
void create()
{
	set("short", "palzt入口");//房间短描述，模板为ROOM_NAME
	set("long", @LONG
这里就是yom得palzt了。
漆黑得大门紧闭着，你需要尝试去敲敲门试试。
LONG
	);
	set("valid_startroom",0);
	set("host","yom");//所有者，模板里固定为pkuxkx
	set("roomvalue",50);//房间价值，初始为50，降到0就倒了
	set("room_ok",1);//是否好的房间
	set("selfcreate",1);
	set("exits", ([
//房间出口
		"south":"/d/city/guangchang",
//		"north":"/data/home/file/y/yom/room1.c",//固定这两个房间不让删除
		]));
	set("objects", ([
//房间有的物品
		]));
	setup();
}