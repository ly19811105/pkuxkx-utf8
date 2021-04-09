inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "天市堂");
        set("long", @LONG
你一进入明教的天市堂，顿时感到一鼓肃杀之气。教众出入都十分
小心，惟恐惊动了坐在油木桌后的堂主李天垣。见你进来李天垣抬眼看
了看你，一张很柔和的脸却立马让你心惊肉跳。
LONG );
        set("exits", ([
                "west"      : __DIR__"ywgong",

        ]));
        set("objects",([
             __DIR__"npc/litianyuan":1,
        ]));
        setup();
}

