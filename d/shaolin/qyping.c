// Room: /d/shaolin/qyping.c
// Date: YZC 96/01/19
#include <ansi.h>
inherit ROOM;
int do_guard();



void create()
{
        set("short", "青云坪");
        set("long", @LONG
这里便是少室绝顶。极目望去，只见白云缕缕，如苍龙绕岭；
嵩山拔翠，似金刚擎天。山腰五道瀑布飞泻而下，石级蜿延曲折，
宛若一条长虫，游人纷纷其上，已如蚁蛭。面前的平地上寸草不
生，正中三棵巨松围成一圈，圈中央似乎有什么东西在闪闪发光。
LONG
        );

        set("exits", ([
                "southdown" : __DIR__"shulin14",
                "enter" : __DIR__"fumoquan",
        ]));

        set("outdoors", "shaolin");
        setup();
}

void init()
{
    object me=this_player();
    add_action("do_leave","leave");
    if (me->query("family/family_name")=="少林派"&&!me->query_temp("青云坪提示")&&
        (me->query("family/master_id")=="du e"||me->query("family/master_id")=="du jie"||me->query("family/master_id")=="du nan"))
    {
        me->set_temp("青云坪提示",1);
        tell_object(me,BLINK+HIG+"少林三渡弟子可以用leave命令，离开青云坪。\n"NOR);
    }
}

int do_leave()
{
    object me=this_player();
    if (me->query("family/family_name")=="少林派"&&
        (me->query("family/master_id")=="du e"||me->query("family/master_id")=="du jie"||me->query("family/master_id")=="du nan"))
    {
        if (me->is_busy())
        {
            tell_object(me,"你正忙着呢。\n");
            return 1;
        }
        if (me->is_fighting())
        {
            tell_object(me,"你想用bug脱离战斗嘛？没门！\n");
            return 1;
        }
        if (random(1000)>499)
        {
            me->move("/d/shaolin/guangchang1e");
            tell_room(this_object(),me->query("name")+"一闪身，就在松树林失去了踪影。\n");
            tell_object(me,"你对松树林的路径烂熟于胸，迅速回到了广场。\n");
            return 1;
        }
        else
        {
            me->move("/d/shaolin/guangchang1w");
            tell_room(this_object(),me->query("name")+"一闪身，就在松树林失去了踪影。\n");
            tell_object(me,"你对松树林的路径烂熟于胸，迅速回到了广场。\n");
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int do_guard()
{
        object me,dunan,due,dujie;

        me = this_player();
        if(!( dunan = find_living("du nan")) )
                dunan = load_object("/kungfu/class/shaolin/du-nan");
        if(!( due= find_living("du e")))
                due = load_object("/kungfu/class/shaolin/du-e");
        if(!( dujie = find_living("du jie")))
                dujie = load_object("/kungfu/class/shaolin/du-jie");
        dunan->move(this_object());
        due->move(this_object());
        dujie->move(this_object());
        dunan->remove_call_out("halt");
        due->remove_call_out("halt");
        dujie->remove_call_out("halt");
        message_vision("只听有人喝道：「 什么人！竟敢在金刚伏魔圈旁边动武？」",me);
        dunan->kill_ob(me);
        dujie->kill_ob(me);
        due->kill_ob(me);
        return 1;
}
        

int valid_leave(object me, string dir)
{
        if ( dir == "enter" )
        if ( present("fumo dao", me) || present("jingang zhao", me) 
          || present("fumo dao", environment(me)) || present("jingang zhao", environment(me)) )
                return notify_fail("只听里面有人说道: 大侠上回已来过此处，此刻身携重宝，不便进入，\n恕老衲等失礼了。\n");

        return ::valid_leave(me, dir);
}

