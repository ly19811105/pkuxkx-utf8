// story:shenzhao 凝血神爪

#include <ansi.h>

int give_gift();


mixed *story = ({
        "只听那黑衣大汉大笑道：“顾炎武，黄宗羲，吕留良，看你们今天往哪里逃？给我拿下了！”",
        "四名亲兵立即应道：“是，谨遵瓜管带吩咐。”",
        "瓜管带道：“回京后见了鳌少保，人人不愁生官发财。”",
        "一名亲兵笑道：“那都是瓜管带提拔栽培，单凭我们四个，那有这等福分？”",
        "船头忽然有人嘿嘿一笑，说道：“凭你们四人，原也没这等福分。”",
        "船舱门呼的一声，向两旁飞开，只见一人负手背后，脸露微笑。",
        "瓜管带道：“官老爷们在这里办案，你是谁？”",
        "那人微笑不答，迈步踏进船舱。顿时刀光闪动，四柄单刀分从四方劈落。",
        "那人手起手落，连出四掌，分别拍在四名亲兵的胸口，咯咯声响，四人肋骨齐断。",
        "瓜管带见势不妙，连忙纵身一跃，从船舱缺口中跳了出去。",
        "那人奔到船头，正欲追赶，却见一书生提起竹篙，挥手掷出。",
        "竹篙犹似飞蛇，急射而前。但听瓜管带“啊“的一声，斥革已插入他后心，将他钉在地上。",
        "两人奔上岸边，见瓜管带已经死得透了，这才相互报以一笑。",
        "那人和那书生心中都暗自称奇，心想：“这人是谁，武功如此之高，当真世所罕有。”",
        "两人走进船舱，解开顾黄吕三人的穴道，又将四名亲兵的尸体抛入运河，重点灯烛。",
        "顾黄吕三人不住道谢，问起两人姓名。",
        "那书生道：“贱名适才承蒙黄先生齿及，在下姓陈，草字近南。敢问这位英雄大名？”",
        "那人微笑道：“无威无德，岂当‘英雄’二字，在下燕苍，承蒙陈总舵主见笑了。”",
        "陈近南道：“阁下武功高强，但阁下侠义热血更为可贵，今日和阁下携手一战，畅快无比。”",
        "燕苍笑道：“陈总舵主名满天下，今日一见，武功果然了得！”",
        "陈近南微笑道：“看阁下是武林中人，这套凝血神爪是集我毕生精力所创，今日便赠予阁下，多行侠事。”",
        "燕苍道：“什么破玩意?随手把凝血神爪给扔了”",
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

        int i, lev;
        object env,ob;
        object *players;
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
        if ((lev = ob->query_skill("claw", 1)) < 100)
                ob->set_skill("claw", lev + 10);

if (ob)
{
        tell_object(ob, HIC "你从陈近南那里学习高级的爪法。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + ob->name(1) +
                              "从陈近南那里学习到了高级的爪法。");
}
        STORY_D->remove_story("new8");
      }
        return 1;
}
