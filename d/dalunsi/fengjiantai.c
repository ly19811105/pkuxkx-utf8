// 大轮寺
//by kiden

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "风见台");
        set("long", @LONG
走到这里，眼前豁然开朗，只见一个方圆几十丈旷坪，四周光秃秃的只有
些杂草，坑洼处露出一片片残雪。四下一片寂静，只有凛冽的山风呼啸而过，
发出狼嚎般的怪响。
LONG 
        );

        set("exits", ([

                "eastdown" : __DIR__"ruyoukou",
                "west" : __DIR__"luofenggang",
                "northup" : __DIR__"xuelingquan",


        ]));
        set("objects", ([
//                __DIR__"npc/baoxiang" : 1,

        ]));
        set("outdoors", "dalunsi");
        set("no_clean_up", 0);
        setup();
}

void init()
  {
        object ob = this_player();
        if (3000/((int)ob->query_skill("dodge",1)+10) > random(300)) {
        message_vision(HIW"
突然一阵狂风夹着雪花扑面而来，$N惊愕之下，心胆俱寒，\n
禁不住脚下不稳，顺着山路摔了下去！\n"NOR,ob);
        switch (random(4)){
        case 0:  
        ob->move(__DIR__"ruyoukou"); 
        break;
        case 1: 
        ob->move(__DIR__"qianbuling1");
        break;
        case 2:
        ob->move(__DIR__"qianbuling2"); 
        break;
        case 3:
                    ob->move(__DIR__"shanchandu");
  break;
        } 
        tell_object(ob,HIW"你反应迅速，急忙双手抱头，身体蜷曲。眼前昏天黑地，顺着山路直滚了下去。\n"NOR);
        tell_room(environment(ob),HIW"只听“扑通”一声，"+ob->query("name")+"不知从哪里掉了下来，重重摔在地上。\n"NOR, ({ ob }));
ob->start_busy(random(5));
       }
  }
