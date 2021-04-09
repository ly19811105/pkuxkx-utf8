inherit __DIR__"karma_room.c";
#include <ansi.h>

void create()
{
	set("short", "地下河边"NOR);
	set("long", @LONG
这是一条地下河，完全阻挡了向东的道路。
LONG
	);
       // set("outdoors", "dongtianmu");
	set("level", 4);
	set("river",1);
	set("exits", ([
		//"up" : (:get_path:),
		//"east" : __DIR__"level4river",
		"west" : __DIR__"level4path2",
		//"north" : __DIR__"level4treed",
		//"south" : __DIR__"level4treef",
	]));

	set("objects", ([
		//__DIR__"npc/heshang" : 1,
		//__DIR__"npc/songbing_y" : 2,
        ]));
	setup();
}
void init()
{
	add_action("do_boat","zaochuan");
	::init();
}
int boat(object me)
{
	object product=new(__DIR__"obj/boat");
	if (!me||environment(me)!=this_object())
	return 1;
	me->delete_temp("karma/level4/start_make_boat");
	product->move(environment(me));
	message_vision("一艘崭新的小船出现在大家眼前。\n",me);
	return 1;
}
int do_boat()
{
	int allow,count=0;
	object obj,*inv,product, me=this_player();
	if (me->is_busy())
	{
		write("你正忙着呢。\n");
		return 1;
	}
	if (me->query_temp("weapon")&&objectp(obj=me->query_temp("weapon"))&&obj->is_KARMA_AXE()) allow=1;
	else if (me->query_temp("secondary_weapon")&&objectp(obj=me->query_temp("secondary_weapon"))&&obj->is_KARMA_AXE()) allow=1;
	if (!allow)
	{
		tell_object(me,RED"你要开始造船，需要拿一把斧头。\n"NOR);
		return 1;
	}
	if (me->query_temp("karma/level4/start_make_boat"))
	{
		tell_object(me,RED"你已经开始造船了。\n"NOR);
		return 1;
	}
	if (me->query_temp("karma/level4/skill")!="carpenter")
	{
		tell_object(me,"你不擅长造船，找个擅长的人来做吧。\n");
		return 1;
	}
	inv=all_inventory(this_object());
	for (int i=0;i<sizeof(inv);i++)
	{
		if (inv[i]->is_KARMA_MATERIAL())
		count+=1;
	}
	if (count<me->query_temp("karma/level4/skill_carpen"))
	{
		write("这里的木材数量并不足以制造一艘可以渡河的小船。\n");
		return 1;
	}
	for (int i=0;i<sizeof(inv);i++)
	if (inv[i]->is_KARMA_MATERIAL())
	destruct(inv[i]);
	me->set_temp("karma/level4/start_make_boat",1);
	me->add_busy(2+random(2));
	message_vision("$N开始用地上的木材来制造一艘小船。\n",me);
	remove_call_out("boat");
	call_out("boat",8+random(4),me);
	return 1;
}