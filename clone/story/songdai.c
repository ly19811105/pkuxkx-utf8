// story:songdai.c

#include <ansi.h>

int give_gift();

protected mixed *story = ({
        "宋江：哎！戴兄弟，你那头怎么样？",
        "戴宗：没问题，都是熟人。不过人事还是不能少。",
        "宋江：不要紧，不要紧，多少人事我这里都有。",
        "戴宗：不麻烦哥哥了，我这里有几两散碎银子，可以摆平他们了。",
        "宋江：怎么能让兄弟破财呢？我这儿有，我这儿有。",
        "宋江摸出十两黄金递给戴宗。",
        "戴宗眼睛瞪的老大：哥哥，你怎么这么有钱？",
        "宋江嘿嘿的笑，暗想：可不能说是从阎婆惜那里搞的。含含糊糊道：江湖上兄弟送的。",
        "戴宗点头道：好好，我这就去打点一下。",
        "宋江：兄弟慢行。",
        "戴宗迈出门，心想：他妈的，反正是朋友送的！顺手把九两黄金塞进了口袋。",
        "宋江：弟兄们..发黄金了...",
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

int give_gift()
{
        STORY_D->give_gift("/clone/money/gold", 20,
                           HIM "\n“啪”的一声一些黄金掉到你面前。\n\n" NOR);
        return 1;
}