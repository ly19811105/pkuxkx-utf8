// qiantang.c 事件：钱塘江潮信

#include <ansi.h>

void create() { seteuid(getuid()); }

#define STATUS_PROMPT           1
#define STATUS_START            2
#define STATUS_END              3

// 开始创建事件
void create_event()
{
        // 明年8月份18日涨潮，提前一天提示
        EVENT_D->at_after(1, -8, -17, -12, STATUS_PROMPT);
}

// 奖励
protected void do_bonus(object room)
{
        object *obs,*usrs;
        string msg;
        int r;
	object ob;
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

        msg = HIC "只听“隆隆”一阵雷鸣响过，潮水如涌一般的向岸边卷来。\n"
                  "刹那间，漫海沸腾，波涛万顷，潮高丈馀，万马奔腾，真有\n"
                  "“涛来势转雄，猎猎驾长风。雷震云霓里，山飞霜雪中”的\n"
                  "壮丽气势！正所谓“远若素练横江，声如金鼓；近则亘如山\n"
                  "岳，奋如雷霆”。一时间你不禁沉浸当中，天地万物都已然\n"
                  "忘怀了。\n" NOR;
        message("vision", msg, obs);
        msg = "听说八月十八" + implode(sizeof(obs) > 4 ? obs[0..3]->name(1)
                                                       : obs->name(1), "、") +
              "等人在钱塘江观潮。";
        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        
        if (sizeof(obs) < 1)
                return;
          {       
		if(!userp(ob)||!living(ob)||ob->query("combat_exp") < 10000000)
	                	return;
	        msg = HIG + ob->name() +  "望着汹涌的潮水，若有所悟，对武功又有了新的体会。\n" NOR;
	        message("vision", msg, ob);
	        ob->add("combat_exp", 10000 + random(5000));
	        ob->improve_potential(1000 + random(1000));
	        ob->improve_skill("force", 10000 + random(10000), 1);
	}
}

// 事件触发
void trigger_event(int status)
{
        object room;

        room = find_object("/d/quanzhou/jiang");

        // 钱塘江潮信
        switch (status)
        {
        case STATUS_PROMPT:
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "八月十八又要到了，听说不少人前往钱塘江观潮。");
                log_file("static/event", sprintf("%s出现潮信奇观。\n",ctime(time())));
                // 明天18点钟起潮
                EVENT_D->at_after(0, 0, 1, -18, STATUS_START);
                break;
                
        case STATUS_START:
                if (objectp(room))
                        do_bonus(room);
                // 一个小时以后落潮
                EVENT_D->at_after(0, 0, 0, 1, STATUS_END);
                break;

        case STATUS_END:
                if (objectp(room))
                        message("vision", "潮水渐渐的退了下去，你这才"
                                          "仿佛从梦中醒了过来。\n", room);
                // 继续执行default中的内容

        default:
                create_event();
                break;
        }
}

// 描述
string query_detail(string topic)
{
        switch (topic)
        {
        case "钱塘江潮信":
                return "每年八月十八钱塘江涨潮，非常准时，故称之为潮信。每次潮水来临"
                       "时波涛汹涌，气势逼人，十分壮观。\n";
        }
}

