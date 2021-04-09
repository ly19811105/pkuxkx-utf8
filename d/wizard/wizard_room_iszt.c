#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", HIG + BOLD"香蕉树"NOR);
        set("long", HIY @LONG
这里是一棵香蕉树，树上挂着一件香蕉皮、一把芭蕉扇、一台美的风扇、
一面铁扇公主，却唯独没有香蕉。倒是一个似曾相识的陌生人坐在树枝上面，
时而发呆，时而在树干上奋笔疾书。树洞里似乎散落着很多丹药。
LONG NOR);

        set("exits", ([
                "down" : "/d/city/guangchang",
                "north" : "/d/wizard/dream_room",
                "southwest" : "/d/lingxiao/xuedi1",
                "northdown" : "/d/beijing/tianqiao",
                "northup" : "/u/iszt/jinzhang",
                "east" : "/u/iszt/workroom",
        ]));

        set("valid_startroom", 1);

        set("objects", ([ "d/wudang/npc/xiaocui" : 1, ]));
        setup();
	"/clone/board/iszt_b"->foo();
}

void init()
{
        object me = this_player();
        add_action("do_search","search");
        if(me->query("id") == "ztadvent" && userp(me))
        {
                me->move("/d/city/guangchang");
                me->delete("env/immortal");
                me->delete("invisibility");
                me->die();
                message("channel:rumor",HIM"【谣言】听说"+me->query("name")+HIM"从"HIY"香蕉树"HIM"上掉到中央广场摔死了！\n"NOR,users());
        }
        return;
}

int do_search()
{
        object me = this_player();
        object obj = random(20)<14 ? new("/clone/story/obj/lingzhi.c") : new("/d/xiangyang/npc/obj/shanlw.c");
        message_vision("$N在树洞里四下搜寻着，找到一颗"+obj->query("name")+"！\n", me);
        message_vision("只可惜一股强大的内力袭来，$N不得不将它丢掉。\n", me);
        destruct(obj);

        return 1;
}
