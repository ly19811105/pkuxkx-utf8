inherit __DIR__"lanzhou.c";

void create()
{
	set("short", "大通铺");
	set("long", @LONG
这里是客栈二楼大房间，很多床并在一起，不少客人已经睡着了。
LONG);

	set("sleep_room", "1");
	set("no_fight", "1");

	set("exits", ([
		"out" : __DIR__"kedian2",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if ( dir == "out" ) me->delete_temp("rent_paid");

	return ::valid_leave(me, dir);
}
void init()
{
	add_action("do_none", "dz");  
	add_action("do_none", "dazuo");    
	add_action("do_none", "study");    
	add_action("do_none", "du");  
	add_action("do_none", "lian");
	add_action("do_none", "practice"); 
	add_action("do_none", "exercise"); 
	add_action("do_none", "tuna");
	add_action("do_none", "respirate");
	add_action("do_none", "xiulian");  	
	add_action("do_none", "vein");  	
}
int do_none()
{  
	write("这样会影响别的客人的。\n");
	return 1; 
}  