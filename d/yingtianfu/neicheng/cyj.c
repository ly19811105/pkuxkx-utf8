//城门
// By Zine 23 Nov 2010

inherit __DIR__"yingshan_room.c";
#include <ansi.h>

void create()
{
        set("short", "存义街");
        set("long", 
"这里是存义街，西面通往中城。\n"

        );
        set("exits", ([
                
              
                
                "west" : __DIR__"zhongcheng",
                "east" : __DIR__"lrj",
                "south" : __DIR__"foodshop",
                "north" : __DIR__"zahuopu",
                
        ]));
         set("objects", ([
		__DIR__"npc/noname" : 1,
	    ]));
        set("outdoors", "yingtianfu");
        setup();
   
}

