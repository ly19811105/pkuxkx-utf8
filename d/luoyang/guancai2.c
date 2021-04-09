#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"棺材店内室"NOR);
	set("long",
	     HIC"一进门，一股腐臭让你几乎要窒息了。屋里满是棺材(guancai)。\n"NOR
	);
	set("exits", ([
                "west" : __DIR__"guancaidian",
	]));
	set("item_desc", ([
		"guancai" : "\n棺材板很结实，上面积了些灰尘。\n" ,
	]));

	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_move", "move");
        add_action("do_move", "open");
        add_action("do_knock", "knock");
}


int do_move(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg!="guancai") return notify_fail("你要移开什么？\n");
	message_vision(
		"\n$N掀开棺材板，只听“唰”的一声, 地道里突然白光一闪，\n"+
		"一柄长剑倏的伸出,“噗”的一声刺入了$N的小腹,又“噗”的一声拔了出来。\n"+
                "一个道人从洞里探出头来，满脸不屑地看了$N一眼，又伸手把地板关上了。\n", this_player());
        if((int)this_player()->query("qi") < 250) 
        {
            this_player()->receive_damage("qi", 0, "在掀棺材板时被人杀");
            this_player()->die();
        }
        else this_player()->unconcious();
	return 1;
}

int do_knock(string arg)
{
        object me,hole;
	string dir;
        me = this_player();
        if (!arg||arg=="") return 0;
	if( arg=="guancai" ) {
		message_vision("\n$N试著敲了敲棺材板，咚咚，里面似乎是空的。\n", this_player());
	}
	if( sscanf(arg, "guancai %s", dir)==1 )
	{
		if( dir=="3" || dir=="three") {

		message_vision("\n$N在棺材板上咚咚咚敲了三下，只听吱呀一声，\n"+"里边伸出一双手把棺材板掀开了。\n", this_player());
                set("exits/eastdown", __DIR__"andao1");
                remove_call_out("close");
                call_out("close", 5, this_object());

	        }
		else return notify_fail("\n你胡乱敲了棺材板几下，结果什么也没发生。\n");
	}
return 1;
}

int do_enter(string arg)
{
 if( !arg || arg!="guancai" ) return 0;
 return notify_fail(" 想穿棺材板啊？你不会奇门遁甲。\n");
 return 1;
}
void close(object room)
{
        message("vision","只见棺材板乒地又关上了。\n", room);
        room->delete("exits/eastdown");
}

