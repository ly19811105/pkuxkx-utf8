inherit ROOM;
void create()
{
    set("short","西厢");
    set("long",@LONG
西厢。
LONG);

    set("exits", ([
        "east" : __DIR__"dating.c",
    ]));

    setup();
    replace_program(ROOM);
}
