// emei.c 事件：武当山天柱峰顶夜陨

#include <ansi.h>

void create() { seteuid(getuid()); }

// 开始创建事件
void create_event()
{
        // 每凌晨12点
        EVENT_D->at_after(0, 0, -30, -1);
}

// 奖励
protected void do_bonus(object room)
{
        object *obs,*usrs;
        object ob;
        string msg;
        int lvl;
        int r;

        obs = all_inventory(room);
      	usrs = ({});
       
        if (sizeof(obs) < 1)
                return;
        foreach (ob in obs)
        {
          	if(!userp(ob)||!living(ob))
             	continue;
            usrs += ({ob});
        }
        if (sizeof(usrs) < 1)
        	return;
        ob = usrs[random(sizeof(usrs))];

        r = random(200);
        if (r <= 5)
        {
                msg = HIR "只听天空骤然传来一阵刺耳的摩擦声，你仰望上苍，发现穹苍里已豁然出现\n"
                          "无数颗流星。夜陨如雨飞坠，锋芒划空，尔落入天池之中，又再激起万股七\n"
                          "色浪涛，漆黑夜穹竟犹如白昼一般。你不禁感叹，大自然之威，当真神鬼莫\n"
                          "测。\n" NOR;

                msg += HIC +  ob->name() + "仔细的观察了流星雨的全过程，发现其中竟有很多奥秘可以融于武学。\n" NOR;
                ob->add("potential", 3000);
                ob->add("combat_exp", 5000);

                message("vision", msg, ob);

                
                {
                	if(!userp(ob)||!living(ob))
                		return;
                        if ((lvl = ob->query_skill("dodge", 1)) >= 80 &&
                            ob->can_improve_skill("dodge"))
                                ob->improve_skill("dodge", 80000,1);

                        if ((lvl = ob->query_skill("throwing", 1)) >= 80 &&
                            ob->can_improve_skill("throwing"))
                                ob->improve_skill("throwing", 80000,1);

                }
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "听说武当天柱峰顶上夜空竟现流星雨，五彩缤纷，煞为壮观。");
                log_file("static/event", sprintf("%s出现流星雨奇观。\n",ctime(time())));
        } else
        if (r < 50)
        {
                msg = RED "只听远处一阵刺耳的摩擦声，举目望去，发现竟有流星从天边划过，怎奈距\n"
                          "隔委实太远，根本无法看清。\n" NOR;

                msg += HIC + ob->name() + "观罢流星，隐隐的对暗器功夫有了一丝体会。\n" NOR;

                obs->improve_skill("throwing", 3000);
                message("vision", msg, ob);

        } else
        {
                switch (random(2))
                {
                case 0:
                        msg = WHT "眼见天边一片明亮，知是流星雨将至，可怎奈间隔遥且云层厚，却无缘得见。\n" NOR;
                        break;
                default:
                        msg = WHT "眼见天边一片明亮，但是水气，雾气和云层交杂，让你什么都看不清楚。\n" NOR;
                        break;
                }
                msg += HIG "你心中连叹：“太可惜了！”\n" NOR;

                message("vision", msg, obs);
        }
}

// 事件触发
void trigger_event()
{
        object room;

        // 武当天柱峰顶夜陨
        if (objectp(room = find_object("/d/wudang/ding")))
                do_bonus(room);

        create_event();
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "天池流星雨":
                return "武当天柱峰顶夜空能见流星雨，煞为壮观。\n";

        case "夜空流星":
                return "夜空常有流星陨落，颇为美丽。\n";
        }
}

