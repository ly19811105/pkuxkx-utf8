// Room: /d/shaolin/dmyuan.c
// Date: YZC 96/01/19

inherit ROOM;
#include <ansi.h>




void create()
{
	set("short", "达摩院");
	set("long", @LONG
这是一座古朴的殿堂。西首的墙上挂满了各类武功图谱，不
少白须白眉的老僧们正端坐在图谱画轴之前，似乎在苦苦思索。
南北山墙是高及屋顶的大书架，走近细看，它们是各门各派的武
功秘笈，屋正中摆着几张矮几诃和几个团，几位老僧正在入定中。
西首有个楼梯上楼。
LONG
	);

	set("exits", ([
		"southdown" : __DIR__"wuchang3",
		"northdown" : __DIR__"guangchang5",
		"up" : __DIR__"dmyuan2",
	]));

	setup();
}


int valid_leave(object me, string dir)
{
	int skill;

	if (!me->query("luohan_winner"))
	{
		if (dir == "up")
		{
                        return notify_fail("你还没破罗汉阵，不能进入达摩院。\n");
		}
	}
	return ::valid_leave(me, dir);
}

