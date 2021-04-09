// story:bizhen 玄铁令——学习碧针清掌

#include <ansi.h>

nosave string char_id;
nosave string char_name;

int give_gift();
object select_character();

mixed *story = ({
        "只听那那黑衣高个儿怒喝：“吴道通，你是决计不交出来的啦？”",
        "吴道通哼了一声，双手分执铁钳两股，竟将铁钳拆了开来，变成了一对判官笔。",
        "吴道通大喝一声，冲如人群。双笔使开，招招取人穴道，以一敌三，仍然占到了上风。",
        "西北角屋面上站着一名矮瘦老者，双手叉在腰间，冷冷的瞧着三人相斗。",
        "片刻之后………",
        "只听喀喇喇的一声响，那高个双掌扎扎实实的击在吴道通胸口，也不知断了多少根肋骨。",
        "矮瘦老者见状陡的飞身上前，抓起吴道通的身子，见他已停了呼吸。",
        "矮瘦老者眉头微皱，喝道：“剥了他衣服，细细搜查。”",
        "四名下属应道：“是！”立即剥去吴道通的衣衫。只见他背上长衣之下负着一个包裹。",
        "两名黑衣汉子迅速打开包裹，但见包中有包，矮瘦老者挟手攫过，捏了一捏，面色陡变。",
        "矮瘦老者怒道：“他奶奶的！骗人的玩意，不用看了！快到屋里搜去。”",
        "十余名黑衣汉子又进了烧饼店，只听呛啷呛啷，店里的碗碟、桌椅、全部给摔了出来。",
        "几个时辰之后，众人将烧饼店墙壁、灶头也都拆了。",
        "这时众人已将烧饼铺中搜了个天翻地覆，连地下的砖也已一块块挖起来查过。",
        "矮瘦老者见再也查不到什么，喝道：“收队！” ",
        "唿哨声连作，跟着马蹄声响起，几十个汉子片刻间走了个干干净净。",
        "…………",
        "暮霭苍茫中，那人漫步而至，看到四周一片狼籍，心中微感诧异。",
        "那人突然发现吴道通的尸体横卧街中，右手单手作爪状，似乎在死前想要抓取什么。",
        "顺着吴道通右手的方向瞧去，那人只见他右手三尺之外有一块烧饼。",
        "那人拣起那块烧饼，轻轻一拉，发现其中藏着黑黝黝的一块铁片。",
        "那人顿时想起一事，随手拔起地下一柄长剑，顺手往铁片上斫去，叮的一声，长剑断为两截。",
        "那人心中狂喜，心道：“想来这便是江湖中传闻的赏善罚恶令，想不到今日竟让我得到。”",
        "相传持此赏善罚恶令者，可以上侠客岛喝腊八粥。",
        "那人心道：“此地不宜久留，我这就上侠客岛去。”说罢，悄然飘失在夜幕中。",
        (: give_gift :),
});

string prompt() { return HIG "【武林奇遇】" NOR; }

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

        int i;
        object env,ob;
        object *players;
                object gob;
        string msg;

        players = users();
        if (sizeof(players) >= 10)
        {
                for (i = 0; i < 10; i++)
                {
                        ob = players[random(sizeof(players))];
                        if (wizardp(ob)) continue;
                        if (ob->is_fighting()) continue;
                        if (!environment(ob)) continue;
                        if (ob->query_temp("netdead")) continue;

                }
        if(!ob) return 1;
        gob = new("/d/xiakedao/obj/shangshanfae-ling.c");
        gob->move(ob, 1);
if (ob)
{
        tell_object(ob, HIC "你得到了赏善罚恶令。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说赏善罚恶令落在了" + ob->name(1) +
                              "的手里。");
}
        STORY_D->remove_story("new16");
      }
        return 1;
}
