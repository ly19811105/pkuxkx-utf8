// arbiter 仲裁者for炸弹人游戏 
// by Vast@pkuxkx 2009.2

/*目前尚未解决的问题 
	a.
	b.玩家自己下注的游戏方式；
	c.
*/
#include <ansi.h>

inherit NPC;

int ask_play();
int ask_reward();

void create()
{
	set("title", HIW"公正严明"NOR);
	set_name("仲裁者", ({ "arbiter",  "zhong cai"}));
	set("gender", "男性");
	set("long", "    此人面无表情，神情严肃，处事公平、公正、公开。
想玩游戏，自然得找他问问，赢了之后别忘了向他要奖励哦！\n");
	set("age", 30);

	set("combat_exp", 500000);
	
	set("attitude", "friendly");
	
	set("grandmaster", 1);

	set("participator", ([
		"player1" : "", 
		"player2" : "",
		"player3" : "",
		"player4" : "",
		]));
		
  set("inquiry", ([
       "玩游戏" : (: ask_play :),
       "奖励" : (: ask_reward :),
    ]));
    
	setup();
  carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
	if(who->query_temp("bomb/money_paid"))
		return notify_fail("仲裁者冷冷地说道：“你已经付过钱了，我可不想占你的便宜！”\n");
		
	if (ob->query("money_id") && ob->value() >= 100000) //10 gold
  {
		who->set_temp("bomb/money_paid",1);
		return 1;
  }
	return 0;
}

int ask_play()
{
	object me = this_player();
	object ob = this_object();
	object *player = allocate(4), r0, r1, r2, r3, r4;
	mapping partner;
	int i, count, flag;
	int a, b, c, d, v;
	string player_name, msg;
	
	partner = ob->query("participator");
	count = ob->query("total");
	flag = ob->query("playing");
	msg = "";
	
	if(flag)
		{
			tell_object(me, "游戏正在进行中，请稍候！\n");
			return 1;
		}
	if(me->query_temp("bomberman"))
		{
			tell_object(me, "你已经报名啦！\n");
  	if(count > 0)
  			{
  				if(objectp(partner["player1"]))
  					msg += partner["player1"]->name() + "(" + partner["player1"]->query("id") + ")" + "\n";
  				if(objectp(partner["player2"]))
  					msg += partner["player2"]->name() + "(" + partner["player2"]->query("id") + ")" + "\n";
  				if(objectp(partner["player3"]))
  					msg += partner["player3"]->name() + "(" + partner["player3"]->query("id") + ")" + "\n";
  				if(objectp(partner["player4"]))
  					msg += partner["player4"]->name() + "(" + partner["player4"]->query("id") + ")" + "\n";
  				tell_object(me, "目前报名的人有：\n" + msg);
  			}			
			return 1;			
		}
	if(me->query_temp("bomb/money_paid"))
		{
			switch(count)
			{
				case 3: //游戏立即开始
					partner["player4"] = me;
					me->delete_temp("bomb/money_paid");			
					player[0] = partner["player1"];
					player[1] = partner["player2"];
					player[2] = partner["player3"];
					player[3] = partner["player4"];

					if(objectp(player[0])) a = 1;
					if(objectp(player[1])) b = 2;
					if(objectp(player[2])) c = 4;
					if(objectp(player[3])) d = 8;
					
					v = a + b + c + d;
					//防止有人在报名后退出游戏
					switch(v)
					{
						case 15:
						break;
						case 14:
							partner["player1"] = partner["player2"];
							partner["player2"] = partner["player3"];
							partner["player3"] = partner["player4"];
							partner["player4"] = "";
							me->set_temp("bomberman", 1);
							me->delete_temp("bomb/money_paid");
							tell_object(me, "报名成功，请等候其他玩家参加！\n");
							ob->set("participator", partner);
							ob->set("total", 3);
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏三缺一啦！要报名的请抓紧时间！\n"NOR,users());	
							return 1;			
						break;
						case 13:
							partner["player2"] = partner["player3"];
							partner["player3"] = partner["player4"];
							partner["player4"] = "";
							me->set_temp("bomberman", 1);
							me->delete_temp("bomb/money_paid");
							tell_object(me, "报名成功，请等候其他玩家参加！\n");
							ob->set("participator", partner);
							ob->set("total", 3);
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏三缺一啦！要报名的请抓紧时间！\n"NOR,users());	
							return 1;
						break;
						case 12:
							partner["player1"] = partner["player3"];
							partner["player2"] = partner["player4"];
							partner["player3"] = "";
							partner["player4"] = "";
							me->set_temp("bomberman", 1);
							me->delete_temp("bomb/money_paid");
							tell_object(me, "报名成功，请等候其他玩家参加！\n");
							ob->set("participator", partner);
							ob->set("total", 2);
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏还差两人啦！要报名的请抓紧时间！\n"NOR,users());	
							return 1;
						break;
						case 11:
							partner["player3"] = partner["player4"];
							partner["player4"] = "";
							me->set_temp("bomberman", 1);
							me->delete_temp("bomb/money_paid");
							tell_object(me, "报名成功，请等候其他玩家参加！\n");
							ob->set("participator", partner);
							ob->set("total", 3);
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏三缺一啦！要报名的请抓紧时间！\n"NOR,users());	
							return 1;
						break;
						case 10:
							partner["player1"] = partner["player2"];
							partner["player2"] = partner["player4"];
							partner["player3"] = "";
							partner["player4"] = "";
							me->set_temp("bomberman", 1);
							me->delete_temp("bomb/money_paid");
							tell_object(me, "报名成功，请等候其他玩家参加！\n");
							ob->set("participator", partner);
							ob->set("total", 2);
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏还差两人啦！要报名的请抓紧时间！\n"NOR,users());	
							return 1;
						break;
						case 9:
							partner["player2"] = partner["player4"];
							partner["player3"] = "";
							partner["player4"] = "";
							me->set_temp("bomberman", 1);
							me->delete_temp("bomb/money_paid");
							tell_object(me, "报名成功，请等候其他玩家参加！\n");
							ob->set("participator", partner);
							ob->set("total", 2);
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏还差两人啦！要报名的请抓紧时间！\n"NOR,users());	
							return 1;
						break;
						case 8:
							partner["player1"] = partner["player4"];
							partner["player2"] = "";
							partner["player3"] = "";
							partner["player4"] = "";
							me->set_temp("bomberman", 1);
							me->delete_temp("bomb/money_paid");
							tell_object(me, "报名成功，请等候其他玩家参加！\n");
							ob->set("participator", partner);
							ob->set("total", 1);
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏一缺三啦！要报名的请抓紧时间！\n"NOR,users());	
							return 1;
						break;
						
						default:
							message( "channel:" + "chat", HIY + "【情报】炸弹人游戏出bug啦！请通知巫师！\n"NOR,users());
							return 1;
						break;
					}
					
					if(userp(player[0]) && userp(player[1]) && userp(player[2]) && userp(player[3]))
						{
							if(!r1 = find_object(__DIR__"room00.c"))
								r1 = load_object(__DIR__"room00.c");
							if(!r2 = find_object(__DIR__"room04.c"))
								r2 = load_object(__DIR__"room04.c");
							if(!r3 = find_object(__DIR__"room40.c"))
								r3 = load_object(__DIR__"room40.c");
							if(!r4 = find_object(__DIR__"room44.c"))
								r4 = load_object(__DIR__"room44.c");
								
							r1->set("survivor", 4); 
							player[0]->move(r1);
							player[1]->move(r2);
							player[2]->move(r3);
							player[3]->move(r4);
							for(i = 0; i < 4; i++)
							{
								player[i]->start_busy(1);
								player[i]->delete_temp("bomberman");
								tell_object(player[i], HIR"游戏开始！\n"NOR);
							}
						message( "channel:" + "chat", HIY + "【情报】炸弹人游戏开始啦！\n"NOR,users());
						ob->set("total", 0);
						ob->set("playing", 1);//游戏开始标志
						
						ob->set("participator", ([
														"player1" : "", 
														"player2" : "",
														"player3" : "",
														"player4" : "",
															]));
						}
				break;
				
				case 2:
					partner["player3"] = me;
					me->set_temp("bomberman", 1);
					me->delete_temp("bomb/money_paid");
					ob->set("total", count + 1);
					ob->set("participator", partner);	
					tell_object(me, "报名成功，请等候其他玩家参加！\n");
					message( "channel:" + "chat", HIY + "【情报】炸弹人游戏三缺一啦！要报名的请抓紧时间！\n"NOR,users());
				break;
				
				case 1:
					partner["player2"] = me;					
					me->set_temp("bomberman", 1);
					me->delete_temp("bomb/money_paid");
					ob->set("total", count + 1);
					ob->set("participator", partner);
					tell_object(me, "报名成功，请等候其他玩家参加！\n");
					message( "channel:" + "chat", HIY + "【情报】炸弹人游戏还差两人啦！要报名的请抓紧时间！\n"NOR,users());
				break;
				
				default:
					partner["player1"] = me;
					me->set_temp("bomberman", 1);
					me->delete_temp("bomb/money_paid");
					ob->set("total", count + 1);
					ob->set("participator", partner);
					tell_object(me, "报名成功，请等候其他玩家参加！\n");
					message( "channel:" + "chat", HIY + "【情报】炸弹人游戏一缺三啦！要报名的请抓紧时间！\n"NOR,users());
				break;
			}
			return 1;
		}
	
	tell_object(me, "仲裁者面无表情地说道：“参加游戏需先交10两黄金，人数够4人，游戏自动开始！”\n");
	
	if(count > 0)
			{
  				if(objectp(partner["player1"]))
  					msg += partner["player1"]->name() + "(" + partner["player1"]->query("id") + ")" + "\n";
  				if(objectp(partner["player2"]))
  					msg += partner["player2"]->name() + "(" + partner["player2"]->query("id") + ")" + "\n";
  				if(objectp(partner["player3"]))
  					msg += partner["player3"]->name() + "(" + partner["player3"]->query("id") + ")" + "\n";
  				if(objectp(partner["player4"]))
  					msg += partner["player4"]->name() + "(" + partner["player4"]->query("id") + ")" + "\n";
  				tell_object(me, "目前报名的人有：\n" + msg);
			}
	return 1;
}

int ask_reward()
{
	object me = this_player();
	int n;
	
	n = me->query("bombman/win");
	
	if(me->query_temp("bomber_winner"))
		{
			tell_object(me, "仲裁者给了你30两黄金！\n");
			if(n > 0)
			tell_object(me, "仲裁者对你颔首道：“你已经取得了" + chinese_number(n) + "局炸弹人游戏的胜利！”\n");
			MONEY_D->pay_player(me, 300000);
			me->delete_temp("bomber_winner");
			return 1;
		}
	tell_object(me, "仲裁者狠狠瞪了你一眼道：“你想讹我么？”\n");
	return 1;
}
