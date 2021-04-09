//train4.c
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

int do_leave();
void create()
{
set("short", HIG"北大侠客行"NOR);
set("long", @LONG

欢迎访问[1;32m北大侠客行[37;0m网站，地址是   [1;32mhttp://www.pkuxkx.com[37;0m 

                             _\\|//_
                            (' . . ')
┌━━━━━━━━━━━━-ooO-(_)-Ooo-━━━━━━━━━━━━━━┐
┃                                                                 ┃
┃                     [1;37m欢迎进入北大侠客行[37;0m                          ┃
┃                                                                 ┃
┠-----------------------------------------------------------------┨
┃								   ┃
┃[1;32mhelp[37;0m 		[36m查看北大侠客行帮助[37;0m                                 ┃
┃                                                                 ┃ 
┃[1;32mnews[37;0m		[36m最新改动通知[37;0m					   ┃ 
┃                                                                 ┃
┃[1;32m[新手提示][37;0m    [37m新手最好到www.pkuxkx.com下载pzmud462[37;0m          ┃
┃              [37m那里集成了pkuxkx中的常用路径，对新手有很大帮助。[37;0m   ┃
┃                                                                 ┃
┃其他相关的详细资料及文章可以参看论坛:http://www.pkuxkx.net       ┃
┃                                                                 ┃
└━━━━━━━━━━━━━━◇   ◇━━━━━━━━━━━━━━━┘
 
    [1;32m如果你已经熟悉这里的环境，就可以离开这里了，以后也不能再到这里。[37;0m
  
    [1;32m请输入指令[1;37mdecide[1;32m并选择门派获得使者的帮助。[37;0m

    [1;32m或者输入指令[1;37mleave[1;32m离开这里，开始闯荡江湖。[37;0m

LONG );
set("no_fight", 1);
set("exits",  ([
        "down"  : __DIR__"train5.c",
      ]));
        set("objects", ([
                __DIR__"npc/shizhe_exit" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_leave", "leave");
}

int do_leave()
{
        object me;
        me = this_player();

	me->move("/d/city/kedian");
	me->set("startroom","/d/city/kedian");
	me->set("xuetang",1);
        message("vision",
                        me->name() + "不知道从哪里冒出来的，吓了你一跳。\n",
                        environment(me), ({me}) );
	tell_object(me,HIY"恭喜你来到这江湖！我是新手精灵，我会陪伴你一段时间。\n"NOR+HIW"如果你缺钱，可以去做一个朱熹抄经的任务,或者平一指的配药任务，就可以赚到必要的启动资金了。help task-newbie。\n平时在路上看到蝙蝠血甲，玉竹杖，冰魄杖的，记得卖到当铺去，来钱也很快！\n"NOR);

return 1;
}
