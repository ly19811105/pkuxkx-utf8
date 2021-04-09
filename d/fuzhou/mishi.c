// room: mishi.c
//Jay 4/7/96
//modified by Zine 2010

inherit ROOM;

int valid_leave();

void create()
{ 
       set("short","密室");
       set("long", @LONG
这是一间黑黢黢的小房间，墙上的砖头(zhuan)已经掉渣子了，房梁
(liang)也已经朽烂不堪。墙脚处有一个铁箱子，上面积满了尘土。
LONG
     );
        set("exits", ([
                "out" : __DIR__"midao",
        ]));       
        set("item_desc", ([
                "zhuan" :      
        "砖头烂得一塌糊涂。\n",
                "liang" :
        "房梁是上好的楠木做的，可惜年代太久，已经腐烂得不成样子了。\n",
        ]) );
        set("objects", ([
                __DIR__"obj/tiexiang" : 1,
        ]));       

        set("no_clean_up", 0);
        setup();

}

void init()
{
        add_action("do_jump", "jump");
}


int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) 
                return 0;
        if( arg=="liang")
        {
            if (me->query_temp("marks/跳1") )
                {
                if (me->query_dex()<20) 
                    write("你试图跳上房梁，无奈身法不够敏捷，只好做罢。\n");
                else 
                    {
                        write("你纵身跃上了房梁。\n");
                        tell_room(environment(me),me->name() +"一纵身跃上了房梁。\n");
                        me->move(__DIR__"liang");
                        tell_room(environment(me),me->name() + "从下面跃了上来。\n" );
                    }
                
                }
        }
        return 1;
}

int valid_leave(object me, string dir)
{
        me->delete_temp("marks/跳1");
        return ::valid_leave(me, dir);
}
 
