//ybingqi.c
//by hehe
//2003.3.5

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "兵器房");
    set("long", @LONG
这是燕子坞的兵器房，这里的兵器简直应有尽有，慕容家武学
闻名天下，其实兵器方面也毫不逊色。慕容家的弟子还可以在
这里领到趁手的兵器(sword,blade)。
LONG
    );

    set("exits", ([
		"west" : __DIR__"ylianwu1",
    ]));
    
    set("outdoors", "murong");
	set("blade_count",3);
	set("sword_count",3);
    setup();
}
void init()
{
	add_action("do_qu","qu");
}
int do_qu(string arg)
{
	object ob,me;
	me = this_player();
	if(me->query("family/family_name")!="姑苏慕容")
	{
		message_vision("$N不是这里的人也想浑水摸鱼？\n",me);
		return 1;
	}
	if(!arg)
	{
		write("你想取什么兵器?\n");
		return 1;
	}
	if(arg=="sword")
	{
		if(query("sword_count")<=0)
		{
			message_vision("$N来晚了，你要的兵器都被你的师兄们拿走了！\n",me);
			return 1;
		}
		ob=new("/clone/weapon/jian.c");
		ob->move(me);
		message_vision("$N从房里取了一柄长剑！\n",me);
		add("sword_count",-1);
		return 1;
	}
	else if(arg=="blade")
	{
		if(query("blade_count")<=0)
		{
			message_vision("$N来晚了，你要的兵器都被你的师兄们拿走了！\n",me);
			return 1;
		}
		ob=new("/clone/weapon/gangdao.c");
		ob->move(me);
		message_vision("$N从房里取了一柄钢刀！\n",me);
		add("blade_count",-1);
		return 1;
	}
	else
	{
		message_vision("$N要取什么东西？\n",me);
		return 1;
	}
}
