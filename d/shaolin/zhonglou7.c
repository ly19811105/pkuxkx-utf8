// Room: /d/shaolin/zhonglou7.c
// Date: YZC 96/01/19
// seagate@pkuxkx增加敲钟任务 2010/10/09

#include <ansi.h>
inherit ROOM;
#include "/newbiequest/shaolin/quest_qiaozhong.h"

string look_bell();
string look_out();

void create()
{
        set("short", "钟楼七层");
        set("long", @LONG
这里就是钟楼之顶。直入眼帘的便是那口大钟和一根悬挂空
中的巨杵。细看大钟，整整有两丈来高，直径也有丈许。钟身似
由青铜浇铸，上面满是密密麻麻的印文古篆，估计重逾数千斤。
巨杵粗可合抱，丈把来长，一头裹以厚皮，正对着钟腰。尽管山
风吹人欲倒，谁都禁不住想撞一下钟(bell)试试。往外看，有个很
大的汉白玉窗台(out)，上面足可站一个人。
LONG
        );

        set("exits", ([
                "down" : __DIR__"zhonglou6",
        ]));

        set("item_desc",([
                "bell"          :       (: look_bell :),
                "out"           :       (: look_out :),
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/qing-xiao" : 1,
        ]));
        setup();
}


void init()
{
        add_action("do_knock", "knock");
        add_action("do_out", "out");
        add_action("do_xuqi","xuqi");
}

int do_knock(string arg)
{
        object me;
        int ret;

        me = this_player();
        if ( !arg || ( arg != "bell" ) ) return notify_fail("你要敲什麽？\n");

        ret=do_qiaozhong();
        if(ret>=0)
        	return 1;

        me->add("qi", -20);
        if ( random((int)me->query("kar")) < 5 )
        {
                message_vision("$N一不小心敲到自己头上了。\n", me);
                //me->add("qi", -10 - me->query("qi"));
                me->unconcious();
        }

        else
        {
                mapping mine;

                mine = me->query_entire_dbase();
                message_vision("$N敲了一下大钟，『咣……』声音传遍整个寺庙。\n", me);
                write("钟声如迅雷般在你耳边炸响，你头脑中一片糊涂，\n"
                        "全身摇摇欲坠，勉力支撑着不倒在地上。心中一个\n"
                        "声音告诉你，得赶快离开这里，不然就没命了。\n");

        }
        return 1;
}

int do_out(string arg)
{
        object me;
        int i, ging_cost, qi_cost;

        me = this_player();
        i = (int)me->query_skill("dodge", 0) + random(200);
        ging_cost = 600 / (int)me->query("int");
        qi_cost = 500 / (int)me->query("int");
        if(((int)me->query("jing") < ging_cost) || ((int)me->query("qi") < qi_cost))
                i = 0;

        message_vision("$N爬上窗台，一个纵身，跳了下去。\n", me);
        me->move(__DIR__"zhonglou");
        message_vision("只听『砰』地一声$N从塔顶跳了下来。\n", me);
        // me->set_temp("last_damage_from", "从钟楼七层跳出去摔");
        if ( i < 50)
        {
            me->receive_damage("qi", 0, "从钟楼七层跳出去摔");
            me->die();
        }
        else if( i < 125)
            me->unconcious();
        else
        {
            message_vision("$N已稳稳地站在地上。\n", me);
            if( i > 175) me->improve_skill("dodge", 4*(int)me->query_skill("dodge", 1));
            me->receive_damage("jing", ging_cost, "从钟楼七层跳出去摔" );
            me->receive_damage("qi", qi_cost, "从钟楼七层跳出去摔" );
        }
        me->start_busy(2);

        return 1;
}

string look_bell()
{
        return
        "※※※※※※※※※※※※※※※※※※※※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※　　　　　佛语有曰：　　　　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※　『做一天和尚，撞一天钟』　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※　（ｋｎｏｃｋ　ｂｅｌｌ）　　※※※※\n"
        "※※※※　　　　　　　　　　　　　　　※※※※\n"
        "※※※※※※※※※※※※※※※※※※※※※※※\n";
}

string look_out()
{
        return  "这里是钟楼顶层的窗台，从这里可以遥望整个少室山脉，\n"
"以及高耸入云的嵩山。浮世烟尘，尽在眼底。据说在此地\n"
"可以与天界诸佛直接交流，对禅修大有益处。\n";
}
