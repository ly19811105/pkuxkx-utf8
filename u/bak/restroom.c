//竞技场休息室
#include <ansi.h>
inherit ROOM;
#define JINGJIZHIWANG "/u/male/test/jingjizhiwang"
#define BOJI "/u/male/boji.c"
void create()
{
        set("short", HIC"竞技场休息室"NOR );
        set("long", HIY@LONG
    这就是竞技场后面的休息室，在这里你可以看到不停地有人
进进出出的将尸体从竞技场里抬出来，你隐隐约约得还可以听到
竞技场里搏击的声音，弱肉强食是这里永恒的旋律，多少人在这
里一夜成名，也有多少人在这里失去自己宝贵的生命。飞蛾扑火
有人认为是一种寻求光明的壮举，也有人认为是自不量力的惨淡
下场。在这里生与死、荣与辱也就在你的一念之间。


     竞技规则就贴在墙上(rule).

     你还可以通过命令record,查询竞技之王的记录。
    
     相关内容：help shengsi
LONG NOR
        );

        set("sleep_room", 1);
        set("item_desc", ([
                "rule" : 
      HIG@LONG
        竞技场内乃生死相搏之所，进去后不得喧哗(chat\rumor\tell等一律
禁止）。任何人进入竞技室之后只能对竞技者下kill，并且在下kill前，所有
perform都一律禁止！在与竞技者的较量中，玩家的内力将会自动变满，jiali
也将清零，并且在厮杀过程中也不允许jiali！这一点请玩家注意。但是在打斗
过程中，玩家可以用fill命令将自己内力补满。(但是fill命令的使用会少许降
低最后的奖励.)
     在竞技过程中任何形式的逃跑都将是不被允许的，竞技一开始，就必须有
人伤亡才算结束！
     关于奖励，玩家在打斗过程中原则上应尽快杀死对手(利用perform)，因为你
杀死对手所用的时间越短,会对你后面的奖励有所贡献,但是千万不要为了求快,堆积
使用perform,因为如果系统判定你无效的perform太多(比如你busy的时候仍然疯狂
的使用perform),对你最后的奖励会大打折扣!而对于perform比较弱的玩家,也不要
气馁,因为使用周期比较长杀伤力不大的pf也可能得到较高的分数!在以后的竞技中，
你获胜之后得到的奖励也会递增，当然你的对手也会越强。为公平起见，你的
对手的装备将会随时和你的一样。但是当你们打斗的时候，如果你从开始持有兵器
一直到最后,没有做任何的unwield操作(在打斗过程中,换装备和换武器是被允许的)
你获得胜利得到的奖励也将会是空手获胜得到奖励的1.5倍！！但是你的奖励不会
马上计入你的帐上，你要想把得到的奖励变成真正的奖励，你可以到这里(休息
室)使用jifen命令，你在前面竞技得到的奖励将会被计入你的实际参数中，但是
这一轮的竞技也就中断，你的下一场竞技将会从第一场开始！


        这是一场勇敢者的游戏，虽然最后得到好处的往往会是在竞技中懦弱
的人，但是你是愿意做一只扑火的飞蛾，还是做一个永远躲在壳里浅尝而止但
是可以安享岁月的缩头乌龟呢？赶快作出你的决定吧！
LONG NOR
        ]));
        set("no_fight", 1);
        set("exits", ([ /* sizeof() == 1 */
                "enter1" : "/d/city/jingjishi1",
                "enter2" : "/d/city/jingjishi2",
                "enter3" : "/d/city/jingjishi3",
                "enter4" : "/d/city/jingjishi4",
                "enter5" : "/d/city/jingjishi5",
                "enter6" : "/d/city/jingjishi6",
                "enter7" : "/d/city/jingjishi7",
                "enter8" : "/d/city/jingjishi8",
                "enter9" : "/d/city/jingjishi9",
                "enter10" : "/d/city/jingjishi10",
          "down" : "/d/city/biwuchang",
        ]));
        set("no_clean_up", 0);
        setup();
}

int show()
{
string lines,last_wang;
int last_level;
lines=read_file(JINGJIZHIWANG);
if(lines)
  sscanf(lines,"%s %d",last_wang,last_level);
else
{
last_level=20;
last_wang="千面";
}
write(MAG"\n\n现在的竞技记录由"+last_wang+"以连续"+chinese_number(last_level)+"场不败的战绩所保持!\n\n"NOR);
return 1;
}

void init()
{
        add_action("show","record");
        add_action("do_jifen","jifen");
        add_action("do_none","perform");
        add_action("do_none","yong");
        add_action("do_none","steal");
}
int do_none()
{
  return 1;
}
int valid_leave(object me, string dir)
{
object zhe,room;
room=load_object(__DIR__"jingjishi1");
if(dir=="enter1"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi2");
if(dir=="enter2"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi3");
if(dir=="enter3"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi4");
if(dir=="enter4"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi5");
if(dir=="enter5"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi6");
if(dir=="enter6"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi7");
if(dir=="enter7"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi8");
if(dir=="enter8"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi9");
if(dir=="enter9"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
room=load_object(__DIR__"jingjishi10");
if(dir=="enter10"&&! objectp( zhe = present("boji zhe", room)))
{
zhe=new(BOJI);
zhe->move(room);
return::valid_leave(me,dir);
}
return::valid_leave(me,dir);
}
int do_jifen()
{
object me;
me=this_player();
if(!me->query_temp("jingji_exp"))
{
  write(HIB"你没有在竞技中获得任何奖励！\n"NOR);
return 1;
}
  write(HIB"你总共得到"+chinese_number(me->query_temp("jingji_exp"))+"点经验和"+chinese_number(me->query_temp("jingji_potential"))+"点潜能！\n"NOR);
  write(HIB"你下一场竞技将从第一场开始！\n"NOR);
me->add("combat_exp",me->query_temp("jingji_exp"));
me->add("potential",me->query_temp("jingji_potential"));
me->set_temp("jingji_exp",0);
me->set_temp("jingji_potential",0);
me->set_temp("xiangbo_level",0);
me->set_temp("last_exp",0);
return 1;
}
