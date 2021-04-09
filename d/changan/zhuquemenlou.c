//春明门 /d/jinyang/chunmingmen
// By Zine 23 Nov 2010

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIR"朱雀门城楼"NOR);
        set("long", @LONG
这是朱雀门城门上的望楼，一队队壮健的金吾卫盔甲
鲜明，手持陌刀长戟，强弓利箭，警惕的注视着城下过望
行人；城门北面是皇城，南面是朱雀大街。
LONG        );

        set("exits", ([
                "west" : __DIR__"innerwall10",
                "east" : __DIR__"innerwall9"
        ]));
        
        set("locate_level",4);

        set("outdoors", "changan");
        set("changan", 4); // 0-郊外 1-外城 2-皇城 3-禁宫 4-城墙
        setup();
}