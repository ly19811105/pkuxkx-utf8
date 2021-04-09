// wuliang.c 事件：无量山玉壁剑舞

#include <ansi.h>

void create() { seteuid(getuid()); }

// 开始创建事件
void create_event()
{
        // 明日晚上8点
        EVENT_D->at_after(0, 0, -1, -20);
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
        
        r = random(500);
        if (r <  3)
        {
                msg = HIW  "只见皎洁的月光下，两个飘逸绝伦的身影倒映在对面山壁之上，持剑翩翩起\n"
                           "舞，剑光顿挫，仙影回翔。你不由惊叹：寰宇之中，竟有如此绝奥之技，今\n"
                           "日有缘得见仙人之姿，实在是福分非浅。\n" NOR;

                message("vision", msg, obs);

                ob->add("potential", 10000);
                ob->add("combat_exp", 50000);

                // 增加武学修养基本剑法及基本身法
                        if (ob->query("combat_exp") > 35000000)
                        {
                                tell_object(ob, HIG "你心中暗自掂量，这二人当真是"
                                                "世上高手，不过自己似乎也可办到。\n" NOR);
	                         r = random(100);
				if(r == 9)
				{
				  	  tell_object(ob, HIC "你看着对面的仙人的剑舞，心中若有所思，似乎隐隐发现了什么。\n" NOR);
					  if (ob->query_int() > 50&&random(ob->query("kar")) > 20)
				            {
				               ob->improve_skill("sword", ob->query_int(),1);            
				                               
				            }	
					 else
					{
							
					tell_object(ob, "那个念头转的实在太快，你略一迟疑，顿时消散的无影无踪，一种怅然若失的感觉浮上心头。\n" NOR);		
							
					}
				}
                        }
			
                        if ((lvl = ob->query_skill("sword", 1)) >= 120 )
                                ob->improve_skill("sword", 50000,1);

                        if ((lvl = ob->query_skill("dodge", 1)) >= 120 )
                                ob->improve_skill("dodge", 50000,1);
                        tell_object(ob, HIG "你对仙人的剑舞颇有所感，武学上顿时有了新的领悟。\n" NOR);
		
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "听说无量玉壁又出仙人剑舞，仙影玄奇，令人匪夷所思。");
                log_file("static/event", sprintf("%s出现剑舞奇观。\n",ctime(time())));
        } else
        if (r < 30)
        {
                switch (random(3))
                {
                case 0:
                        msg = HIY "只见对面玉壁上仙影一闪即过，身形之敏捷，令你根本无法捕捉。\n" NOR;
                        break;
                case 1:
                        msg = HIY "只见对面玉壁上闪过几道仙影，似乎是施展一种奇妙无比的武功绝学。\n" NOR;
                        break;
                default:
                        msg = HIY "忽然间两个飘逸绝伦的身影显映在对面山上，但仙影转瞬即逝，你根本无法看清。\n" NOR;
                        break;
                }
                msg += HIG + ob->name() + "受到了仙影的感悟，武学方面又有了一些体会。\n" NOR;
                 ob->add("combat_exp", 1000+random(1000));

                message("vision", msg, ob);

        } else
        {
                switch (random(3))
                {
                case 0:
                        msg = WHT "眼见皎洁的月光升起，可是一团云飘过，遮盖了月光，你眼前顿时一片漆黑。\n" NOR;
                        break;
                case 1:
                        msg = WHT "你目不转睛的注视着对面的玉壁，可刹那间雷声轰鸣，山风卷云，将月光遮了个严实。\n" NOR;
                        break;
                default:
                        msg = WHT "夜晚已至，可一团团浓厚的云层却笼罩着天空，你连对面的山头都无法看清。\n" NOR;
                        break;
                }
                msg += HIG "你不禁叹息道：“怎奈缘分未至，无缘窥视仙影！”\n" NOR;

                message("vision", msg, obs);
        }
}

// 事件触发
void trigger_event()
{
        object room;

        // 无量山玉壁剑舞
        if (objectp(room = find_object("/d/wuliang/yubi")))
                do_bonus(room);

        create_event();
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "无量山玉壁剑舞":
                return "皎洁的月光下，无量山壁上有仙人偏偏起舞，神姿仙态"
                       "平生难得一见。\n";

        case "无量山玉壁仙影":
                return "皎洁的月光下，壁上能隐隐约约倒影出仙人之姿。实乃"
                       "世间仅有。\n";

        }
}


