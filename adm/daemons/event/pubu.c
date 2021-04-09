// puliu.c 事件：桃源瀑布

#include <ansi.h>

void create() { seteuid(getuid()); }

// 开始创建事件
void create_event()
{
        // 明天12点钟瀑流最急
        EVENT_D->at_after(0, 0, 1, -12);
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

        r = random(300);
        if (r < 5)
        { 
                msg = HIR "只听轰隆隆声音大做，发耳欲聩，令人心神俱摇！你抬头看去，只见\n"
                          "晨曦中桃园瀑布笼罩着层层雾气，分外要人。水流飞泻，气势惊人！\n" NOR;
                msg += HIG + ob->name() + "望着湍急的瀑布飞练，为这世间美景惊叹不已，从"
                           "中不禁领悟到了武学的道理。\n" NOR; 
                ob->add("combat_exp", 10000);
                ob->add("potential", 5000);
                	if(!userp(ob)||!living(ob))
                		return;
                	if(ob->query_skill("parry",1) > 60)
                		ob->improve_skill("parry", 30000,1);
                 
                        if ((lvl = ob->query_skill("unarmed", 1)) >= 60)
                                ob->improve_skill("unarmed", 30000,1);

                message("vision", msg, ob);

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "听说桃源瀑布激流澎湃，奇景非凡，无数游人叹羡不已。");
                log_file("static/event", sprintf("%s出现瀑布奇观。\n",ctime(time())));
        } else 
        if(r < 30)
        {
                msg = HIY "一阵轰隆轰隆的得声音传来，你抬头一样，只见晨曦中瀑布腾起层层雾气。\n" NOR;
                switch (random(3)) 
                { 
                case 0: 
                        msg += HIY "看着这壮丽的瀑流，你不禁感叹，正所谓「飞流直"
                                    "下三千尺，疑是银河落九天」啊。\n" NOR; 
                        break; 
                case 1: 
                        msg += HIY "瀑流就像一席倒挂的白帘，气势如虹，天地都不禁为之失色。\n" NOR; 
                        break; 
                default: 

                        msg += HIY "瀑流直如水银泄地一般，水花四溅。\n" NOR; 
                        break; 
                } 
                msg += HIG + ob->name() + "观赏着飞流直下的水瀑，不由得感叹自然造化的奇妙，隐"
                           "隐然对武学也有了一点领会。\n" NOR; 
                 ob->add("combat_exp", 1000+random(1000));
                ob->add("potential", 400+random(200));

 
                message("vision", msg, ob);

        } else
        {
                switch (random(3))
                {
                case 0:
                        msg = WHT "瀑流渐渐缓了下来。\n" NOR;
                        break;
                case 1:
                        msg = WHT "瀑流总是不见有增强的趋势。\n" NOR;
                        break;
                default:
                        msg = WHT "瀑流有如小桥流水，叮叮咚咚，离你所期望的相差甚远。\n" NOR;
                        break;
                }
                msg += HIG "你心中大感失望。\n" NOR;

                message("vision", msg, obs);
        }
} 
 
// 事件触发 
void trigger_event() 
{ 
        object room; 
        // 桃源瀑流 
        if (objectp(room = find_object("/d/yideng/yideng/pubu1"))) 
                do_bonus(room); 
 
        create_event(); 
} 

// 描述 
string query_detail(string topic) 
{ 
        switch (topic) 
        { 
        case "桃源激流": 
                return "桃源瀑布水流湍急，时有激流澎湃，乃是罕见的景观。\n"; 
 
        case "桃源瀑布": 
                return "大理的桃源瀑布自然风光迷人，瀑流美丽壮观。\n"; 
        }
} 

