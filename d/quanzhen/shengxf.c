// Room: /u/kiss/quanzhen/shengxf.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "升仙坊");
	set("long", @LONG
“升仙坊内，气象万千”这句话一点也不错，只看那亭顶，只见北天的星图
以奇石连缀其上，正是人间少有的瑰宝。不知是哪一位能工巧匠所制，特别独具
匠心的是，亭顶的“天空”全以世间罕有的蓝晶石制成，深邃得令人神往！
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"sanqingdian.c",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
