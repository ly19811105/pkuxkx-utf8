// story:zagang.c

#include <ansi.h>

string give_gift();

protected mixed *story = ({
        "不好啦～～～不好啦～～～",
        "司马光：怎么了？出什么事了？",
        "小孩甲：死不了掉到缸里了。",
        "司马光咳嗽一声，道：我还以为什么大不了的事，他不是死不了嘛！慌甚么。",
        "众小孩乱成一团。",
        "冰～～糖～～葫～～芦～～",
        "司马光蓦然而起：他奶奶的，我记得死不了还欠我一串糖葫芦！",
        "小孩乙：是有这么回事，不过你要不马上找到家长把死不了捞上来，就别指望了！",
        "哼！司马光冷冷笑道：区区小事，何足挂齿？",
        "......",
        "司马光举起一块石头，狠狠的砸了下去，“哐当”，缸破水出。",
        "死不了苟延残喘。",
        "司马光翻起死不了，道：死不了啊死不了，你欠我的那串冰糖葫芦还记不记得？",
        "死不了：你说啥？",
        "乒乓！",
        "死不了被司马光扔到了缸里。",
        "死不了从缸里扔出了一串冰糖葫芦。",
        (: give_gift :)
});

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

string give_gift()
{
        STORY_D->give_gift("/clone/story/obj/bingtang", 1,
                           HIM "\n“啪”的一声一棵冰糖葫芦掉到你面前。\n\n" NOR);
        return 0;
}
