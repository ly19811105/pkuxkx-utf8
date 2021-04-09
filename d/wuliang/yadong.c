// /d/dalicheng/yadong.c
// notme 2004/04/11
// 降低了剑的重量，但是要求20先天膂力才能拿到
inherit ROOM;
int do_pick(string arg);
void create()
{
    set("short", "崖洞");
    set("long", @LONG
你眼前出现了一把耀眼的宝剑（sword），剑上镶嵌了诸色宝石。
剑身凿空，镶上宝石，月光透过宝石，映出一丝彩色的影子.
LONG
       );
    set("item_desc", ([
                "sword": "看起来这把宝剑不是那么容易拔（pick）出来的。\n",
                ]));

    set("exits", ([
                "down" : __DIR__"yubi3",
                ]));

    set("outdoors", "dali");
    setup();
}
void init()
{
    add_action("do_pick","pick");
}
int do_pick(string arg)
{
    object me,sword;
    me=this_player();

    if(!arg||arg!="sword") return notify_fail("你想拔什么?\n");
    if(query_temp("mark/been_get")) return notify_fail("宝剑已经被人拿走了。\n");
    if( me->query("str")>20 && me->query("neili") > 1000)
    {
        message_vision( "$N运起内力将游侠宝剑拔了起来。\n", me );
        sword=new(__DIR__"obj/yxbj.c");
        sword->set("weapon_prop/damage",100 + random(101));
        sword->move(me);
        set_temp("mark/been_get",1);
        return 1;
    }
    message_vision( "$N使出吃奶的力气想要拔出宝剑，可哪里拔得出来。\n",me );
    return 1;
}

void reset()
{
    ::reset();
    delete_temp("mark/been_get");
}
