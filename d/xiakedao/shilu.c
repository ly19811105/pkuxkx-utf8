
inherit ROOM;

void create()
{
        set("short", "石路");
        set("long", @LONG

    石路上不见人踪，平滑乾净的石板，看来仿佛终年都有人走动，玉一般暴
露在苍穹之下。往东是一片阴郁的松林，林中似有飞檐楼阁。西边也是一片松
林，隐约有流水之声传来。
LONG
        );
        set("exits", ([ 
		"west" : __DIR__"garden",
		"east" : __DIR__"loulang",
]));
        set("outdoors", "palace");

        setup();
        replace_program(ROOM);
}

