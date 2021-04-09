// Room: /d/gumu/mudao12.c
 
inherit ROOM; 
 
void create() 
{ 
        set("short", "墓道");
        set("long", @LONG
    你走在墓道里，四周回响着“咚咚”的脚步声。
尽管明知头上的怪石不会碰着你，你仍不由自主的弓着
腰身，加快了步伐。
LONG
        );
        set("no_sleep_room", 1);
        set("exits", ([ /* sizeof() == 3 */
  "west" : __DIR__"hean",
  "north" : __DIR__"mudao13",
 
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
 
