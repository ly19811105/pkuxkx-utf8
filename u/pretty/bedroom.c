// bedroom.c --> for pretty's bedroom

inherit ROOM;

int halt_shooting(object me);

void create()
{
        set("short", "试炼场");
        set("long", @LONG
甫一进入这间卧室，你几乎不能适应与外面的巨大反差，
只见墙上挂满了各种冲锋枪、手榴弹以及火箭筒，墙角里还摆
着一门小钢炮。除去这些之外，最显眼的莫过于放在四个墙角
里的巨大音箱了，本应放书的书架上却摆了几层的ＣＤ。据说
主人经常放上一张摇滚的ＣＤ，将音量开到最大，然后手持冲
锋枪一边狂叫一边四处扫射，可要小心了。
LONG
        );

        set("exits", ([
                "east"   : __DIR__"workroom.c",
        ]));

        setup();
}

void init()
{
        add_action("do_turn", "turn");
}

int do_turn(string arg)
{
        object me;
        
        me = this_player(1);
        if ( !arg || ((arg != "on") && (arg != "off")) )
                if ( me->query("gender") == "男性" )
                        return notify_fail("你扭来扭去，仿佛在展示自己强健的肌肉。\n");
                else
                        return notify_fail("你扭来扭去，仿佛在展示自己柔美的线条。\n");
        if ( arg == "on" )
        {
                message_vision("$N把音箱的开关打开，顿时，一阵震耳欲聋的强劲音乐响了起来。\n", me);
                me->start_busy(6, (: halt_shooting :) );
                me->set_temp("being_shooting", 1);
                call_out("music", 2, me);
                return 1;
        }
        else if ( me->query_temp("being_shooting") )
        {
                me->delete_temp("being_shooting");
                remove_call_out("music");
                remove_call_out("appear");
                remove_call_out("aim");
                remove_call_out("shoot");
                me->interrupt_me();
                message_vision("$N眼疾手快，一把关掉了电源，屋内瞬间又恢复了原样。\n", me);
                return 1;
        }
        else
        {
                message_vision("电源已经是关着的了。\n", me);
                return 1;
        }
}

int halt_shooting(object me)
{
        return 1;
}

void music(object me)
{
        message_vision("音乐声中，室内忽然变得烟雾朦胧......\n", me);
        call_out("appear", 2, me);
}

void appear(object me)
{
        message_vision("室内的烟雾逐渐凝固起来，赫然幻化为一个人形，竟然便是主人双儿！\n", me);
        call_out("aim", 2, me);
}

void aim(object me)
{
        message_vision("只见双儿随手从墙上摘下一挺冲锋枪，满脸天真地端了起来。\n", me);
        call_out("shoot", 2, me);
}

void shoot(object me)
{
        message_vision("在强劲的摇滚音乐声中，双儿猛地大叫一声，同时扣动扳机，疯狂地向四周扫射！\n", me);
        message_vision("$N避无可避，整个身体被打成筛子模样，慢慢滑倒在地上。\n", me);
        me->die();
        me->delete_temp("being_shooting");
        me->interrupt_me();
}
