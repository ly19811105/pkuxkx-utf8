//xiaoyuan by binlang
inherit ROOM;
void create()
{
        set("short", "小院");
        set("long", @LONG
这是一个小院，小院里花草树木也种了不少，透出一种清雅之气
  院里有两个老者，神采奕奕，仙风飘飘。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
//  "southdown" : __DIR__"hsxl2",
  "northup" : __DIR__"hsxl2",
]));
        set("objects", ([
       "/kungfu/class/huashan/gao.c" :1,
       "/kungfu/class/huashan/ai.c"  :1,
        ]));
        set("room","room6");
        set("outdoors", "xx" );
        setup();
        replace_program(ROOM);
}
