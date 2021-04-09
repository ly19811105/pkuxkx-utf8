// Room: /u/kiss/quanzhen/youxiang.c
// Made by: kiss

#include <ansi.h>
inherit ROOM;

string look_men();

void init();

void create()
{
	set("short", CYN"游仙阁"NOR);
	set("long", @LONG
游仙阁内别有一番洞天，四周摆放着各色各样的名花奇草，香气四溢，一张
八仙桌搁在中央，西边是乘云阁，南边是逍遥楼，东边是九仙楼，北边有一道门。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "west" : __DIR__"chengyg.c",
  "north" : __DIR__"qizhend.c",
  "south" : __DIR__"xiaoyaol.c",
  "east" : __DIR__"jiuxianl.c",
]));
    set("item_desc",([
        "men"        :    (: look_men :),
    ]));
	set("no_clean_up", 0);

	setup();

}

void init()
{
    add_action("do_knock", "knock");
    add_action("do_push", "push");
}

int close_men()
{
    object room;

    if(!( room = find_object(__DIR__"qizhend")) )
        room = load_object(__DIR__"qizhend");
    if(objectp(room))
    {
        delete("exits/north");
        message("vision", "门吱吱呀呀地自己合上了。\n", this_object());
        room->delete("exits/south");
        message("vision", "门吱吱呀呀地自己合上了。\n", room);
    }
    else message("vision", "ERROR: men not found(close).\n", room);
}

int do_knock(string arg)
{
    object room;

    if (query("exits/north"))
        return notify_fail("大门已经是开着了。\n");

    if (!arg || (arg != "door" && arg != "men"))
        return notify_fail("你要敲什么？\n");

    if(!( room = find_object(__DIR__"qizhend")) )
        room = load_object(__DIR__"qizhend");
        
    if(objectp(room))
    {
    if ((int)room->query_temp("sleeping_person") > 0)
    {
        message_vision(
        "$N刚轻轻地敲了一下门，就听见里面传出一阵雷鸣般的鼾声，\n"
	"显然里面的人睡得跟死猪似的，怎么敲都没用了\n",
        this_player());
    } else if ((int)room->query_temp("person_inside") > 0)
    {
    	switch( random(2) )
    	{
    	case 0:
        	message_vision(
        	"$N轻轻地敲了敲门，只听见里面有人很不耐烦地吼到：\n"
		"刚躺下就来敲门！我睡着了，听不见！！！\n",
        	this_player());
        	
        	break;
       	case 1: 
        	message_vision(
        	"$N轻轻地敲了敲门，只听见里面有些响动，\n"
		"好象有人在踱来踱去，拿不定主意是否开门。\n",
        	this_player());
        	
        	break;
	}       	
	        	
    } else
    {
	room->delete_temp("sleeping_person");
        message_vision("$N轻轻地敲了敲门：咚、咚、咚．．．咚、咚、咚．．．\n",
            this_player());
    }
    }

    if(objectp(room))
    	message("vision",
    	"外面传来一阵敲门声，你从门缝往外一瞧，是"+this_player()->query("name")+"一脸焦急地站在门外，\n"
    	"看样子也想进来休息。\n", room);
        
    return 1;
}

int do_push(string arg)
{
    object room;

    if (query("exits/north"))
        return notify_fail("门已经是开着了。\n");

    if (!arg || (arg != "door" && arg != "men"))
        return notify_fail("你要推什么？\n");

    if(!(room = find_object(__DIR__"qizhend")))
        room = load_object(__DIR__"qizhend");
        
    if(objectp(room))
    {
    if((int)room->query_temp("person_inside")<=0)
    {
	 	room->delete_temp("person_inside");
        set("exits/north", __DIR__"xiuxishi");
        message_vision("$N轻轻地把门推开。\n", this_player());
        room->set("exits/south", __FILE__);
//      message("vision", "有人从外面把门推开了。\n", room);
        remove_call_out("close_men");
        call_out("close_men", 10);
    } else 
    {
        message_vision("$N想把门推开，却发觉门被人从里面闩上了。\n",
	 	this_player());
    }
    }

    return 1;
}


string look_men()
{
    object room;

    if (query("exits/north"))
	return ("门上挂了个牌子：南柯梦处\n");

    if(!( room = find_object(__DIR__"qizhend")) )
        room = load_object(__DIR__"qizhend");

    if( objectp(room) )
    if( (int)room->query_temp("person_inside") > 0 )
    {
	return ("门上挂了个牌子：请毋打扰\n");
    } 
    
    return ("门上挂了个牌子：休息室\n");
}

int valid_leave(object me, string dir)
{

    	object room;
    	
	if(!( room = find_object(__DIR__"qizhend")) )
        	room = load_object(__DIR__"qizhend");

	if(objectp(room) && dir == "north")
	{
		room->add_temp("person_inside", 1);
		// will open the door if ppl inside stay too long 
		remove_call_out("force_open");
		call_out("force_open", 599, room);
	}		

	return ::valid_leave(me, dir);
}

