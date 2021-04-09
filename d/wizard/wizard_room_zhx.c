#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", CYN"旭心的工作室"NOR);
        set("long", @LONG
这是一个抽风的少年。每天旭心就在这里工作、发呆。听说他最近出家了，
还取了个名字叫“虚旭”，整天跟着一个叫“清普”的大米练功，令人捉摸不透。
有什么事就在这里给他留言(post)吧，只是不知道他能不能看到，呵呵。
LONG NOR);

        set("exits", ([
                "down" : "/d/city/guangchang",
                "northwest" : "/d/wizard/dream_room",
        ]));

        set("valid_startroom", 1);

        setup();
        "/clone/board/zhx_b"->foo();
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
