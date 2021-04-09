// Room: /d/xingxiu/xxroad4.c

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
山势在这里渐渐变得平缓，你已经可以听见西边山涧底的水声。东面有一
个山洞。
LONG
        );
        set("exits", ([
  "south" : __DIR__"xxroad4",
  "enter" : __DIR__"cangku",
  "north" : __DIR__"xxroad6",
]));

        set("objects", ([
                "/kungfu/class/xingxiu/chuchen" : 1,
        ]) );


        set("no_clean_up", 0);
        set("outdoors", "xingxiuhai");

        setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
    mapping myfam;
    myfam = (mapping)me->query("family");
    if(me->query_temp("apprentice/step"))
        return ::valid_leave(me, dir); 
    if (me->query("special_skill/sociability")) 
        return ::valid_leave(me, dir);  
    if ((!myfam || myfam["family_name"] != "星宿派") && dir != "south"
	&& (present("chuchen zi", environment(me)))
	&& living(present("chuchen zi", environment(me))))
	    return notify_fail("出尘子一言不发，闪身拦在你面前。\n");
    return ::valid_leave(me, dir);
}

