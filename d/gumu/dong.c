#include <ansi.h>
inherit ROOM;
int do_get(string arg);


void create()
{
        set("short", "山洞");
        set("long", @LONG
这是一个水底的小洞，光线阴暗，偶尔有一两个漩涡。靠里边有
数个骷髅，象是为抢什么东西互相残杀而死的。隐隐，你觉得脚下踩
着什么一本书。
LONG
        );
        set("exits", ([ 
  
  "out" : __DIR__"dixiahe6",
  
]));
       set("objects",([
                __DIR__"obj/jiuyin-zhenjing1.c" : 1,
		
        ]));
        setup();
}

void init()
{
        add_action("do_get","get");
}

int do_get(string arg)
{
        object zhenjing;
        
         if (objectp( zhenjing = present("jiuyin zhenjing",environment(this_player())) ))
        {
                zhenjing->move(this_player());
                message_vision("$N拣起一本" + MAG + "九阴真经" + NOR + "。\n",this_player());
                return 1;
        }
        return 0;
}
