inherit ROOM;
int do_climb(string);
void create()
{
  set ("short", "松林");
  set ("long", @LONG
山路依旧蜿延而上，两边的松林被山风一吹，哗哗地做响。抬头上望，
山高林密，不知还要走多远．向前望去，林中太暗，什么也看不清楚。前
方一棵大松树(pine)上好象写了些什么。
LONG);
  set("item_desc", ([ /* sizeof() == 1 */
  "pine" : "灵鹫宫练功圣地!\n",
]));

set("exits", ([ /* sizeof() == 4 */
"northup" : __DIR__"dadao1",
 "southdown": __DIR__"shanlu2"]));

        set("no_clean_up", 0);
	set("outdoors", 1);
        setup();
}
void init()
{
        add_action("do_climb", "climb");
}

int do_climb(string arg)
{       
          object me,room;
        me=this_player();

        if ( !arg || ((arg != "pine") ))
                return notify_fail("你要爬什么？\n");
 if(!( room = find_object(__DIR__"uptree")) )
  room = load_object(__DIR__"uptree");
                message_vision("$N抓住伸出的树枝，小心翼翼的爬了上去。\n",me);
           me->move(room);
//         me->receive_damage("qi", 20); (for i dont clear this in xkx)
		tell_room( environment(me), "树枝晃了几晃，有个人爬了上来！\n", ({me}));

                return 1;
}
