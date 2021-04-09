//wang.c
//by hehe
//2003.3.20
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_me();
int ask_hua();
int ask_duan();
int do_answer(string);

void create()
{
	set_name("王夫人",({"wang furen","wang","furen"}));
	set("gender", "女性");
	set("rank_info/respect", "夫人");
    set("title",HIM"曼佗罗山庄主人"NOR);
  	set("long",
    "她就是曼佗罗山庄的主人，她看上去虽以四十有加，但风韵尤存。\n");
    set("age", 40);
	set("attitude", "friendly");
	set("shen_type", 0);
	set("str", 20);
	set("int", 22);
	set("con", 28);
	set("dex", 23);

	set("max_qi", 1500);
	set("max_jing", 1500);
	set("neili", 1000);
	set("max_neili", 1500);
	set("jiali", 0);
	set("combat_exp", 80000);
	set("score", 15000);

    set_skill("murong-xinfa", 70);
    set_skill("dodge",70);
    set_skill("force", 70);
	set_skill("shenyuan-gong", 70);
	set_skill("yanling-shenfa", 70);
    set_skill("parry", 70);
	set_skill("literate", 70);
    set_skill("strike", 65);
	map_skill("force", "shenyuan-gong");
	map_skill("dodge", "yanling-shenfa");

    prepare_skill("dodge", "yanling-shenfa");

	set("shen_type",1);set("score",5000);setup();

         carry_object("/d/murong/npc/obj/shoe")->wear();
         carry_object("/d/murong/npc/obj/skirt")->wear();

    set("inquiry", ([
		"name" : "我就是曼佗罗山庄的主人，见到我难道没有什么表示吗？\n",
        "here" : "这里是曼佗罗山庄的庄院之所在，此处名为云锦楼？\n",
        "rumors" : "最近我那表亲慕容博不幸仙逝了。\n",
        "王语嫣" : "语嫣是我的宝贝女儿，你可别想打她的主意。\n",
        "慕容复" : "慕容复是我那不成器的侄儿，练就了以彼之道还施彼身的绝技，名震江湖。\n",
        "琅镮福地" : (: ask_me :),
        "曼佗罗山庄" : "这里就是曼佗罗山庄，我就是这里的主人。\n",
        "还施水阁" : "那是燕子坞的秘密之所在，不过琅镮福地的藏书比那里可是多的多呀。\n",
		"茶花" : (: ask_hua :),
		"段正淳" : (: ask_duan :),	
	]));
}
void init()
{
	add_action("do_answer","answer");
}
int ask_me()
{
	command("say 你能带的茶花来，看来你对茶花还是很有研究的。");
	command("say 不过那里是我曼陀山庄的宝地，没有我的允许，外人不能随便进入!\n");
	command("say 不如我们来研究一下茶花。");
	return 1;
}
int ask_hua()
{
	object me=this_player();
	command("say 嗯，我来说一些花的描述，你来说是什么花名......\n");
	command("say 如果表现的好的话，或许会考虑你去“琅镮福地”去看一下。\n");
	command("say 现在你听好了，我可不说第二遍。\n");
	call_out("question1",0,me);
	return 1;
}
int question1(object me)
{
	command("say 第一道题:\n");
	command("say 大理有一种名种茶花，是天下的极品，一株上共开十八朵花，朵朵颜色不同，\n
	红的就是全红，紫的便是全紫，决无半分混杂。而且十八朵花形状朵朵不同，各有各的妙处，\n
	开时齐开，谢时齐谢，这是什么花？");
	//十八学士
	command("say 提示一下，答案是四个字");
	command("say 想好了回答(answer)我\n");
	me->set_temp("murong/q1",1);
	return 1;
}

int question2(object me)
{
	command("say 第二道题:\n");
	command("say 大理有一种名种茶花，八朵异色同株，八朵之中必须有深紫和淡红的花各一朵，\n
	那是铁拐李和何仙姑，要是少了这两种颜色，虽然是八色异花，也不能算也不叫我说的这种，那叫做\n
	'八宝妆'，也算是名种，但比我说的这种差了一级。\n");
	//八仙过海
	command("say 提示一下，答案是四个字");
	command("say 想好了回答(answer)我\n");
	me->set_temp("murong/q2",1);
	return 1;
}
int question3(object me)
{
	command("say 第二道题:\n");
	command("say 大理有一种名种茶花，三朵异色同株，凡是正品,三朵花中必须紫色者最大，那是虬髯客，\n
	白色者次之，那是李靖，红色者最娇艳而最小，那是红拂女。如果红花大过了紫花、白花，便属\n
	副品，身份就差得多了。\n");
	//风尘三侠
	command("say 提示一下，答案是四个字");
	command("say 想好了回答(answer)我\n");
	me->set_temp("murong/q3",1);
	return 1;
}
int question4(object me)
{
	command("say 第三道题:\n");
	command("say 这一种茶花，论颜色，比十八学士少了一色，偏又是驳而不纯，\n
	开起来或迟或早，花朵又有大有小。它处处东施效颦，学那十八学士，却总是不像，\n
	那不是个半瓶醋的酸丁么？因此我们叫它作......\n");
	//落第秀才
	command("say 提示一下，答案是四个字");
	command("say 想好了回答(answer)我\n");
	me->set_temp("murong/q4",1);
	return 1;
}
int do_answer(string arg)
{
	object me=this_player();
	if(!arg)
	{
		command("say 想好了吗？");
		return 1;
	}
	if(me->query_temp("murong/q1"))
	{
		if((string)arg=="十八学士")
		{
			command("say 好，你答对了第一题了，接着进行下一道\n");
			call_out("question2",0,me);
			me->delete_temp("murong/q1");
			return 1;
		}
		else
		{
			command("say 你答错了");
			command("say 原来你是个骗子，来啊，给我捆了!");
			call_out("kickout", 0, me);
			return 1;
		}
	}
	if(me->query_temp("murong/q2"))
	{
		if((string)arg=="八仙过海")
		{
			command("say 好，你答对了第二题了，接着进行下一道\n");
			call_out("question3",0,me);
			me->delete_temp("murong/q2");
			return 1;
		}
		else
		{
			command("say 你答错了");
			command("say 原来你是个骗子，来啊，给我捆了!");
			call_out("kickout", 0, me);
			return 1;
		}
	}
	if(me->query_temp("murong/q3"))
	{
		if((string)arg=="风尘三侠")
		{
			command("say 好，你答对了第三题了，接着进行下一道\n");
			call_out("question4",0,me);
			me->delete_temp("murong/q3");
			return 1;
		}
		else
		{
			command("say 你答错了");
			command("say 原来你是个骗子，来啊，给我捆了!");
			call_out("kickout", 0, me);
			return 1;
		}
	}
	if(me->query_temp("murong/q4"))
	{
		if((string)arg=="落第秀才")
		{
			command("say 没想到你居然知道这么多！");
			me->delete_temp("murong/q4");
			me->set_temp("murong/finish",1);
			command("say 让我考虑一下.....\n");
			call_out("finish",10,me);
			return 1;
		}
		else
		{
			command("say 你答错了");
			command("say 原来你是个骗子，来啊，给我捆了!");
			call_out("kickout", 0, me);
			return 1;
		}
	}
}
int kickout(object me)
{
	if (!present(me,find_object("/d/murong/myunjin.c")))
	{
		return 1;
    }
    message_vision("王夫人喝道：“来啊，把他关起来。\n",me);
    message_vision("突然出来几个婢女用绳子把你捆了起来。\n",me);
    message_vision("你感到你的后脑勺受到重重一击，你昏了过去。\n",me);
    message_vision("昏昏沉沉中你感觉被人丢到一个地方，你重重的摔在地上。\n",me);
    me->move("/d/murong/mshishi");
    me->unconcious();
    return 1;
}
int finish()
{
	object me;
	me=this_player();
	if(me->query_temp("murong/finish"))
	{
		command("say 既然你精通茶花一道，很合我的口味，就破例允许你进入\n
		“琅镮福地”去参观一下，记得不要乱拿里面的东西阿!\n");
		me->set_temp("murong/langhuan",1);
		me->delete_temp("murong/finish");
	return 1;
	}
	else
	{
		command("say 既然你精通茶花一道，很合我的口味，很好很好\n");
		return 1;
	}
}
int ask_duan()
{
  object me=this_player();
	mapping myfam;
  myfam = (mapping)me->query("family");
        
  if (myfam && myfam["family_name"] != "大理王府"){
    return 0;
  }
	if(!me->query_temp("dali/ask_aluo")){
	  return 0;
	}

	if ((int)me->query("yiyangzhi/ask_aluo")>=3){
		command("say 我不是已经告诉过你吗？");
		command("away "+me->query("id"));
		return 1;
  }	
  
  if ((int)me->query_condition("learn_dagoubang") > 0 ){
    return 0;
  }	
  
	if ((int)me->query("yiyangzhi/ask_aluo")<3){
		me->add("yiyangzhi/ask_aluo",1);
    me->apply_condition("learn_dagoubang",60);//懒得写，借用这个condition
	  return 0;
	}
	else{
	  command("sigh1");
	  command("say 瞧你三番五次的询问，多半是真的受了那个负心人的所托，你不妨把我的消息告诉他。");
	  return 1;
	}
}
