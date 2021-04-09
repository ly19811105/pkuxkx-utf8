// tufeiwo1.c 林中小路
// by Cleansword 1996/2/2

inherit ROOM;

void create()
{
	set("short", "林中小路");
	set("long", @LONG
	你走在一条僻静的林中小路上，两旁是阴森森的树林。只见左右前后，到处
都是铺天盖地的松树林。几十丈高的大松树簇在一块，密实的枝叶象一蓬蓬巨伞
般伸向天空，把阳光遮得丝毫也无。据说这里经常有土匪出没，不可久留。边上
有个小山洞(dong)。
LONG
	);
        set("outdoors", "wudang");

	set("no_sleep_room",1);

	set("exits", ([
		"south" : __DIR__"tufeiwo2",
		"northdown" : __DIR__"wdroad7",
	]));

        set("objects", ([
                __DIR__"npc/tufei2" : 2,
                __DIR__"npc/xiao_louluo" : 2,
                __DIR__"npc/xiao_tufei" : 2,
		 ]));

	setup();
}

void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
    int i;
    object *ob;
    object me;
    mapping fam;
    me = this_player();
    if( !arg || arg=="" ) return 0;
    if( arg=="dong" )
    {
        if( (fam = me->query("family")) && fam["family_name"] == "丐帮" ) 
        {
            message("vision",
            me->name() + "运起丐帮缩骨功，一弯腰往洞里钻了进去。\n",
            environment(me), ({me}) );
            me->move("/d/gaibang/underwd");
            message("vision", me->name() + "从洞里走了进来。\n", environment(me), ({me}) );
            return 1;
        }
    }
    return notify_fail("这么小的洞，你钻得进去吗？\n");
}