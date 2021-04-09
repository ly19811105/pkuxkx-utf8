// Room: /d/shaolin/smdian.c
// Date: YZC 96/01/19
// Modified by iszt@pkuxkx, 2007-03-30

inherit ROOM;

void create()
{
	set("short", "密室");
	set("long", @LONG
这是一间阴森森的密室，光线阴暗，地上厚厚的灰尘上隐隐约约有
几个女子的脚印，象是有人刚刚来过，靠墙的角上有一个小门(door)。
LONG);
//	set("exits", ([
//		"north" : __DIR__"taijie",
//	]));
	set("item_desc",([
		"door" : "一扇非常结实的铁门",
	]));
	set("objects",([
		__DIR__"obj/bingpozhang.c" : 1,
	]));
        set("no_task",1);
	setup();
}
void init()
{
	add_action("do_open", "open");
	add_action("do_close", "close");
}
void close_gate()
{
	object room;
	if(!( room = find_object(__DIR__"andao")) )
		room = load_object(__DIR__"andao");
	if(objectp(room))
	{
		delete("exits/south");
		message("vision", "一阵风吹来，小门吱吱响着合了起来。\n", this_object());
		room->delete("exits/north");
		message("vision", "小门慢慢地关上了。\n", room);
	}
}
int do_close(string arg)
{
	if (!query("exits/south"))
		return notify_fail("小门已经是关着的了。\n");
	if (!arg || (arg != "door" && arg != "south"))
		return notify_fail("你要关什么？\n");
	message_vision("$N走上前去，想关上门。\n", this_player());
	remove_call_out("close_gate");
	call_out("close_gate", 2);
	return 1;
}
int do_open(string arg)
{
	object room;
	if (query("exits/south"))
		return notify_fail("小门已经是开着的了。\n");
	if (!arg || (arg != "door" && arg != "south"))
		return notify_fail("你要开什么？\n");
	if(!( room = find_object(__DIR__"andao")) )
		room = load_object(__DIR__"andao");
	if(objectp(room))
	{
		set("exits/south", __DIR__"andao");
		message_vision("$N使劲把小门打了开来。\n", this_player());
		room->set("exits/north", __FILE__);
		message("vision", "吱地一声，铁门开了。\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}
	return 1;
}
