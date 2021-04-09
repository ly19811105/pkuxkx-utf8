//春明门 /d/jinyang/chunmingmen
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "东市");
        set("long", @LONG
这是喧嚣的长安东市，两边的商店鳞次栉比，市场街道
上挤满了来自长安各地的居民，来自异国他乡的商人，好一
个热闹景象。街道两边是长安有名的客栈和榷场。
LONG);

        set("exits", ([
                "west" : __DIR__"kedian",
                "north" : __DIR__"eastmarket-1",
                "south" : __DIR__"eastmarket-3",
                "east" : __DIR__"offline_shop1",                
        ]));

        set("outdoors", "changan");
        set("changan", 1); // 0-郊外 1-外城 2-皇城 3-禁宫 4-城墙
        setup();
   
}