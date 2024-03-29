//train1.c
//modified from xo
//by zoom
//2003.3.30

#include <ansi.h>

inherit ROOM;

void create()
{
set("short", HIR"第一站:基本指令"NOR);
set("long", @LONG
欢迎来到新手学堂，这里是北大侠客行新手学堂中基本指令的培训地点。
初到这个世界，一切都这么陌生，不要担心，学会了这些基本指令，自然如鱼得
水，畅游无阻。
     
    第一个要熟悉的指令是look，简写为 l ，顾名思义，这个指令是用来看周围
的环境，加上参数，也可以看生物、方向。例如：l south，就是看目前所在位置
南面的房间中的情况，这对手无缚鸡之力的新手来说是十分重要的， 可以知道你
的周围是否有危险人物。还可以l name 来看其他生物(包括人和动物)的描述，加
上自己的id就是看自己的描述了。
    第二个要熟悉的指令是走路，在用look看清环境后，比方说此地，出口是up，
你可以输入u来往上走，然后输入d走回来。常用的方向还有 e(东),s(南),w(西),
n(北),se(东南),sw(西南),nw(西北),ne(东北),u(上),d(下),enter(进),out(出)。
这些都是简写的指令，如果不闲麻烦可以输入方向的整个单词，如east,south，这
在有些地方是需要的。
    第三个要熟悉的指令是说话，试试输" new hi,大家好。"跟大家打个招呼吧。
这样发出来的消息大家都可以看见，热心的人也可以给你帮助。help channel 可
以查看能够使用的聊天频道。如果不喜欢某个频道，可以用tune <频道>来关闭。
再想看到时，随便在这个频道里说句话就可以了。
    再有就是查看自己的状态，试试输入 hp 。指令score可以查看自己的一些参
数。当然刚出生，14岁的时候有些是看不到的。指令 skills 来查看自己的技能。
    请输入指令i来查看自己身上的东西。手上拿的东西和身上穿着的衣服，在用
look <人物> 指令时会显示出来，如 □短打劲装(Cloth)，□表示正穿着,你可以
remove cloth来脱掉它，wear cloth来穿着上它。还可以输入l cloth来看它的描述。
    如果觉得命令太多，记不住，没关系，慢慢熟悉就好了，还可以help cmds
查询都有哪些指令。如果觉得某些指令难记的话，可以自己设定一个指令来代替。
请输入help alias来查看帮助。例如alias zhaohu chat hi,大家好。这样以后只
要输入zhaohu就能和大家打招呼了，是不是方便了许多？

    最后，一个最有用的指令就是help，通过看帮助可以得到很多有用的信息。

LONG );
set("no_fight", 1);
	set("exits",  ([
        "up"  : __DIR__"train2.c",
        "down"  : __DIR__"entrance.c",
      ]));
        setup();
        replace_program(ROOM);
}
