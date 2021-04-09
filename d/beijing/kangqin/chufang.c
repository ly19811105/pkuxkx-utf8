// Room: /d/beijing/kangqin/chufang.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"厨房"NOR);
	set("long",
MAG"这里是康亲王府的厨房，进门右手处一排并列了八、九
口大锅。左边则是排放了各种准备好了的半成品，只等着下
锅了。你一定是饿了吧,那就赶紧坐下(zuo)吃饭吧.\n"NOR
	);
	set("exits", ([ /* sizeof() == 1 */
  	"east" : __DIR__"garden.c",
]));

	setup();

}
void init()
{
    add_action("do_zuo","zuo");

}

 int do_zuo()
{

   	object me=this_player();
	int food = me->max_food_capacity();
	int water = me->max_water_capacity();
   	if((string)me->query("class") != "officer")
  	return notify_fail("怎么，你想白吃啊！\n");

	if(me->query("food") < food )
   	me->add("food", food / 4);
   	if(me->query("water") < water )
   	me->add("water", water / 4);
   	if(me->query("food") > food && me->query("water") > water)
   	return notify_fail("你已经胀得什么都吃不下了！\n");

   	message_vision("$N吃饱喝足，站了起来.\n",me);
   	me->start_busy(random(4));
  	return 1;
}
