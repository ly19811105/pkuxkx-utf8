inherit ROOM;
void create()
{
    set("short","东厢");
    set("long",@LONG
东厢。
LONG);

    set("exits", ([
        "west" : __DIR__"dating.c",
    ]));

    setup();
}

void init()
{
    object ob;
    ob=this_player();

    ob->unconscious();

    write("你发现阿紫的脸有点红.\n");

    return;
}

