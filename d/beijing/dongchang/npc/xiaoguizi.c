// xiaoguizi.c 小桂子

#include <ansi.h>

inherit NPC;

string ask_saodi();
string ask_wancheng();

void create()
{
        set_name("小桂子", ({"xiao guizi", "gui",}));
        set("title", YEL"『小太监』"NOR);
        set("long",
                "这是一个新进的小太监，正在好奇的东张西望，
长的倒是眉清目秀，就是一脸惫懒的神情，显得颇为顽劣。\n"
        );

        set("gender", "无性");
        set("rank_info/respect", "公公");

        set("attitude", "heroism");
        set("class", "eunuch");

        set("inquiry",([
                "扫地"  : (: ask_saodi :),
                "完成"  : (: ask_wancheng :),
//                "关防印": (: ask_yin :),
        ]));

        set("age", 14 + random(5));
        set("shen_type", -1);

				set("pin", 9);
//				set("yin_count", 5);
				
				set("combat_exp", 1000);
	
        set("chat_chance", 15);
        set("chat_msg", ({
//                (: random_move :)
        }) );
        
				setup();

        carry_object("/d/beijing/dongchang/obj/guanfu")->wear();
//        add_money("silver", 50);
}

void init()
{
}

string ask_saodi()
{
	object me, player, broom, tar;
	int time, i;
	string *zijin, place;
	
	me = this_object();
	player = this_player();
	time = player->query("mud_age");

	if(player->query("class") != "eunuch") 
		return RANK_D->query_respect(player) + "与东厂素无瓜葛，不知何来此言？";
	if(player->query("score") >= 100)
		return "这项任务对你来说太简单了，我还有其他任务交给你。";
	if(player->query_temp("saodi/sao")) 
		return "我不是已经吩咐你了么，怎么你还没去扫地啊？";
	if(time - player->query_temp("saodi/time") < 60)
		return "你扫地也累了，先下去休息一会儿吧。";
	
	zijin = get_dir("/d/beijing/zijin/");
	for(i = 0; i < sizeof(zijin); i++)
	{
		place = zijin[random(sizeof(zijin))];
		place = "/d/beijing/zijin/" + place;
	
		tar = find_object(place);
		if(!objectp(tar))
			tar = load_object(place);
		if(tar->query("short") != HIY"通道"NOR && tar->query("short") != HIY"宫中小道"NOR)
			break;
	}
	
	broom = new("/d/beijing/dongchang/obj/broom.c");
	if(!objectp(broom)) 
		tell_object(player, "BUG，请通知巫师。\n");
	
	broom->set("target_place", file_name(tar));
	broom->set("long", "这是一把大扫帚，你可以用它来扫地（saodi）。\n你的任务是去" + tar->query("short") + "扫地。\n");
	broom->move(player);
	
	player->set_temp("saodi/sao", 1);
	player->set_temp("saodi/time", time);
			
	tell_object(player, "小桂子递给你一把扫帚。\n");
	return "你去把" + tar->query("short") + "打扫一下吧！";
}

string ask_wancheng()
{
	object me, player;
	int pot, exp;
	
	me = this_object();
	player = this_player();
	
	if(player->query("class") != "eunuch") 
		return RANK_D->query_respect(player) + "与东厂素无瓜葛，不知何来此言？";
	if(!player->query_temp("saodi/sao")) 
		return "我并未吩咐你去扫地啊？";		

      pot = 5 + random(20);
      exp = 30 + random(70);
      player->add("potential", pot);
      player->add("pot/dongchang", pot);
      player->add("combat_exp",exp);
      player->add("exp/dongchang",exp);

			player->delete_temp("saodi/sao");
			player->delete_temp("saodi/ok");
			player->add("dongchang/job_saodi", 1);
			player->add("score", 1);
			
			tell_object(player,HIW"你被奖励了：\n" + 
			chinese_number(exp) + "点实战经验\n" +	
			chinese_number(pot) + "点潜能\n"+	
			"你对东厂的贡献度增加了。\n" NOR);

		return "哈哈，做得不错！";	
}