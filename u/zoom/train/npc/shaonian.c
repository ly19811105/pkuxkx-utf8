//shaoniao.c 少年
//by zoom
//2004.3.30

#include <ansi.h>

inherit NPC;

int ask_me(string, object);
void greeting(object);

void create()
{
	set_name("少年", ({ "shao nian", "nian", "man"}));
	set("long", "他看过去像个普通的农家子弟，看过去非常的结实。\n");
	set("gender", "男性");
	set("age", 18);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 30);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("race", "人类");	
	set("max_qi", 200);
	set("eff_qi", 200);
	set("qi", 200);
	set("max_jing", 200);
	set("eff_jing", 200);
	set("jing", 200);
	set("max_neili", 200);
	set("eff_neili", 200);
	set("neili", 200);
	set("max_jingli", 200);
	set("eff_jingli", 200);
	set("jingli", 200);
	set("combat_exp", 10000);
	set("score", 1000);

	set_skill("force", 20);
	set_skill("dodge", 20);
	set_skill("parry", 20);
	set_skill("cuff", 20);
	set_skill("sword", 20);
	
	set("inquiry", ([
			"庄主"   :  "庄主在书房。\n",
			"经验"   :  (: ask_me, "exp" :),
			"fight"   :  (: ask_me, "fight" :),
			"打架"   :  (: ask_me, "fight" :),
			"比划"   :  (: ask_me, "fight" :),
			"hit"   :  (: ask_me, "hit" :),
			"攻击"   :  (: ask_me, "hit" :),
			"kill"   :  (: ask_me, "kill" :),
			"杀人"   :  (: ask_me, "kill" :),
                        "生死相拼"   :  (: ask_me, "kill" :),
			"潜能"   :  (: ask_me, "pot" :),
		]));
	setup();
}

void init()
{
        object me = this_player();        

        ::init();

        if( interactive(me) )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}

void greeting(object me)
{	
	if (me->query_temp(this_object()->query("id")) == 0 )
	{	command("hi " + me->query("id"));
		command("say 
          这位" + RANK_D->query_respect(me) + 
                   "是刚来的吧。快加紧练功，早日到江湖上出人投地。
    如果你在练功上有什么疑问，就来问我吧。比如说
    什麽是"+HBRED+HIW"经验"NOR+"，"+HBRED+HIW"潜能"NOR +"，如何"+HBRED+HIW"打架"NOR+"等等。");
		me->set_temp(this_object()->query("id"), 1);
	}
}
int ask_me(string name, object ob)
{
     if ( name == "exp" )
       {
	 command("say 
          你的经验高低决定了你的武功技能的高低。比方说，你的 
    经验是 1000，你技能最高只能到 22: (22-1)^3 / 10 < 1000。
    和人比划，经验越高胜算也就越高。得经验最简单的方法是和非 
    玩家（ＮＰＣ）打架。ＮＰＣ的经验如果和你相差太大，你是得
　　不到什麽经验的。怎样才知道一个ＮＰＣ是不是适合你，你需要
　　多问问老玩家。现在有好多任务可以做，有很多适合新手的，各
    门各派都有不同的方法。多向师兄，师姐们请教吧。");
	 return 1;
       }
     else if ( name == "fight")
       {	
	 command("say 
          打架有两种，一种是比划(fight)，另一种是生死相拼(kill)
    。比划时，你的精或气损失过多时，你就会认输停手。但有时对
   手会不想和你比划。如果你想要逼之出手，就要攻击(hit)对方或者
   杀死对方了。与对手生死相拼很危险：对方不杀死你是不会停手的。
   为了安全，你可以把你的逃跑指数设高(set wimpy 60)。60表示当你
   的精或气跌低过百分之六十，你就会自动逃跑。但有时对手的攻势太
   强或招式太厉害，你还是会逃不开的。所以与人搏命时要特别小心。
   如果你想和我比划，就用“fight man”。不过我的经验值很高的喔。");
	 return 1;
       }
     else if ( name == "hit")
       {	
	 command("say 
          你想和对方较量，对方又不想和你打的时候，你可以攻击
   他，逼他和你打。不过攻击有些npc是很危险的，他会主动杀(kill)你。");
	 return 1;
       }
     else if ( name == "kill")
       {	
	 command("say 
         如果你要想杀谁，你可以用kill sb。 杀人有些时候要付出
   些代价的。你要是在城里杀玩家，会被官府通辑。你要是杀了个城
   里有头有脸的ＮＰＣ，官府也会通辑你的。被通辑的人，巡捕，捕
   头，官兵，武将等见了都会追杀的。你要是被人杀了也不用太难过
   ，你只会少些经验和技能。人在江湖，哪一个不曾杀过人？又有哪
   一个没有被杀过？一般来说，你如果在二十岁前死亡次数少于十次
   就很不错了。不过切记，不要攻击玩家，小心引发众怒。");
	 return 1;
       }
     else if ( name == "pot")
       {
	 command("say 
         潜能是用来向师父学功夫的。每向师父学一次，就需要花一
   点潜能。得潜能的最简单方法和经验一样，和ＮＰＣ打架。也和经
   验一样，只有和与你功夫相近的ＮＰＣ打架才能得潜能。做任务得
   潜能也是很快的，各门各派都有不同的方法。多向师兄，师姐们请
   教吧。");
	 return 1;
       }
}
