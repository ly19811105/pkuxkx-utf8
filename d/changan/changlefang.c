#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"长乐坊"NOR);
        set("long", @LONG
这是长安城内最繁华的赌场长乐坊，整个长安城的皇亲国戚、富绅名士都过来
一掷千金。旁边就是长安城内最著名的青楼怡红院。赌场旁边贴有一张告示
(notice)，对赌博有兴趣的可以看看告示。
LONG);
        set("no_fight", 1);
        set("no_perform", 1);
        set("no_steal", 1);
        set("no_sleep_room", 1);
        set("outdoors", "changan");
        set("objects", ([
                "/d/changan/npc/zhuangjia" : 1,
        ]));
        set("item_desc", ([
        "notice": @LONG
本赌坊的赌局只要有资格的玩家都可以成为庄家开立赌局，在庄家设定范围内任何其他玩家
都可以参加该庄家开办的赌局，在赌局结束以后胜利的玩家提取完自己的本金和盈利的财物以后，
庄家提取剩下的所有财物作为自己投入本金的盈亏记录。先简单说一下本赌坊开办赌局相关的重
要名词解释：
庄家：有巫师、新手导师、十大富豪、拥有超过1000根金条的存款（黄金不算）并且具有100m经
验的玩家之一资格者可以成为庄家自主开办赌局。

赌局：单一赌局中各个赔率必须是互斥的，最后庄家也只能公布其他一个赔率为胜方。一个庄家
可以因为某些目的开办任意多个赌局。

投注期限：投注期限限制在1小时到半个月范畴内，具体时间由庄家自由设定。

赔率：每个赌局至少有两个以上赔率，每个赔率由庄家设定为N:M形式，其中N，M表示玩家投入本
金和该赔率获胜以后玩家在系统抽水钱盈利，比如2：1，表示如果一个玩家投入该赔率10根金条，
最后如果该赔率获胜，在系统抽水前，该玩家获得盈利5根金条，最后一共回到玩家手上是15根金
条。

抽水：玩家在领取盈利的时候，本金不会被系统抽取税收，但是盈利部分会被系统抽取一定比例
的税收，初始抽水比例是10：1，也就是10%，但是随着该赌局投注的玩家越来越多，赌金越来越
大，抽水比例也随之下降，最终能够达到50：1，也就是2%的比例。

押金：庄家开立的每个赔率都要投入保证金，保证金是保证该赔率输了的情况下，足够赔付获胜
赔率的盈利要求，保证金最少是100根金条或者等值9颗雷月，具体押金限制和赌局开办的收受财
物范围有关。押金缴纳有两种形式，第一种是庄家开始赌局的时候必须缴纳初始的押金，第二种
是开始赌局以后，投注期间庄家可以和其他玩家一样押注，庄家押注全部变成押金。

财物：赌局所收财物范围有两种，第一种是金条，第二种是宝石，不收黄金、装备、丹药等等其
他形式的财物，宝石统一折算成以雷月为单位的计数方式，系统会根据你输入的雷月数，自动从
你身上扣除最接近的宝石当作押金注入，自动寻找的宝石至少是雷月及雷月以上级别的宝石。盈
利返回的时候对于不足一根金条的按照黄金折算返回，不足一个雷月的折算到水月返回，返回的
时候根据投注的宝石偏阳性还是阴性来决定赔付的是雷月还是雷日。领取盈利的时候最好是人少
的时候过去，领取的财物如果身上负重不够，会自动堆放地上。

×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
庄家命令：
bet命令，所有和创建/维护赌局相关的命令，都在本命令的各个参数下面。命令格式如下：
    bet {open|modify|odds|add|start|close} 赌局ID
其中赌局ID是标识你开办赌局的唯一索引，最好是简单易记的英文缩写。
bet open ***选项作用是创建赌局，使用该命令格式以后会创建以你输入赌局唯一ID为索引的赌
局，创建过程中根据系统指引一步一步完成所有信息输入工作。
bet modify ***选项是修改对应赌局的相关描述信息。
bet odds ×××选项是修改对应赌局的相关赔率值，庄家在赌局关闭投注前都可以修改赌局的各个
赔率，在关闭投注以后庄家不允许修改赔率。
bet add ×××选项是增加一个赔率，庄家在开放投注前可以用该选项来增加对应赌局的赔率。
bet start ×××选项是开放投注命令，庄家投入押金开放投注，之后其他玩家可以进行投注。
bet close ×××选项是庄家强行关闭赌局，在关闭投注前庄家可以强行关闭赌局，关闭以后所有
参与者可以无损拿回自己的本金，没有任何损失。

win命令：该命令是庄家公布某赌局的胜利方用的，一个赌局有且仅有一个胜利赔率，公布以后
系统会自动计算参与各方的盈利情况，玩家可以在公布以后领取自己的本金和盈利。命令格式是：
    win 赌局ID 赔率ID

×××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
玩家命令：
find命令：find命令作用是查找赌局，并且查看赌局和赔率的具体信息，在开放投注期间对有兴
趣的赔率进行押注。find命令格式如下：
    find [-w|-e|-s|-o|-u userid]
find命令后面不跟任何参数表示显示所有赌局
find -w表示仅显示处于开放投注阶段的赌局
find -e表示仅显示处于投注截至阶段的赌局
find -s表示仅显示处于公布结果阶段的赌局
find -o表示仅显示处于各种关闭阶段的赌局
find -u userid表示仅显示某个庄家开办的赌局

wager命令：wager命令作用是庄家或者玩家领取自己的本金和收益。命令格式是：
    wager 赌局ID
在以下几种情况下可以领取收益：
玩家在庄家公布结果以后七天内，投注获胜赔率的玩家可以领取收益。
庄家在赌局关闭以后领取余下的自己所有押金，收益中玩家未领走部分，玩家未领走的所有财物。
玩家和庄家在庄家将赌局进行强行关闭以后，领取自己投注的本金。
玩家在庄家关闭投注以后七天内未公布结果，可以所有玩家平分庄家的押金。

LONG
]));
        set("exits", ([
          "south" : __DIR__"tonghuastreet-3",
          "west" : __DIR__"yihongyuan"
        ]));
        set("changan", 1); // 0-郊外 1-外城 2-皇城 3-禁宫 4-城墙
        setup();
}

void init()
{
	add_action("do_none","exert");
}


int do_none()
{
        write("赌场的打手跑过来阻止了一场争斗。\n");
        return 1;
}