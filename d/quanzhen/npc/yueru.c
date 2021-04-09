inherit NPC;
#include <ansi.h>
inherit F_DEALER;
inherit F_MASTER;

int waiting(object me);
int checking(object me);
int do_chase(object me);
int do_kill(object me, object dest);
string ask_bf();
varargs void drool(string msg, string who);
string *rnd_say = ({
	"我忽然好想去滑冰.",
	"今天有没有上bbs？有好新闻哟!",
	"为什么大家都不理我?！",
	"可不可以告诉我哪里有杀人？",
	"今天我心情不大好, 大家可要小心了.",
	"今晚有人跳舞吗?",
	"谁想讲个故事？",
	"现在几点了？",
	"为什么不说话呢?",
	"为什么不回去睡觉呢?",
	"谁想去看电影?",
	"我可以出去杀人吗?",
 //       "风简直就是一个流氓! ",
	"我对MUD根本没什么好感.",
	"我对足球根本没什么兴趣.",
	"我好象很苯耶.",
	"今晚有人请客吗?",
	"谁要开报告会啊？",
	});

void create()
{
	set_name("月如", ({"yueru"}));
 set_name("月如",({"yue ru","yue"}));
 set("title",HIB"全真派"NOR+YEL"女道童"NOR);
 set("nickname",RED"全真教知客总管"NOR);
 set("long","月如本是这个mud的女神,不知为何现在改投了全真派,\n"
   "当上了全真派的公关部主管.\n"
      );
  set("gender","女性");
 set("rank_info/respect","美女");
 set("age",23);
 set("max_neili",2000);
 set("neili",2000);
 set("max_qi",1000);
 set("qi",1000);

 set("combat_exp",20000);
 set("attitude","friendly");

 set("int",30);
 set("str",20);
 set("con",25);

 set_skill("parry",25);
 set_skill("cuff",25);
 set_skill("dodge",30);
 set_skill("kongming-quan",30);
 set_skill("jinyan-gong",30);
 set_skill("force",100);
 set_skill("xiantian-gong",100);

 map_skill("cuff","kongming-quan");
 map_skill("dodge","jinyan-gong");
 map_skill("force","xiantian-gong");
 map_skill("parry","kongming-quan");

 set("chat_chance",({
  YEL"月如嫣然一笑:来拜全真教吧,如今全真如此兴旺,多少人想加入我们都不收呢!\n"NOR,
  YEL"月如偷偷告诉你:拜全真可是有很多好处的哦!\n"NOR,
  YEL"月如看着你,笑道:看你的样子,你怎么这么苯啊!\n"NOR,
  }));

 set("env/wimpy",10);

 set_temp("apply/attacka",20);
 set_temp("apply/defense",30);
 set_temp("apply/damage",30);

 set("vendor_goods",({
    __DIR__"obj/qz-map.c",
    __DIR__"obj/xiang",
   }));
     

	set("inquiry", ([
		"逍遥"     : (: ask_bf :),
	]) );
	set("chat_chance", 3);
	set("chat_msg", ({
		"月如忽然做了个鬼脸，笑道: 真想溜出去玩会儿。\n",
		(: command("sing2") :),
		(: command("angry") :),
		(: command("slogan2") :),
		(: command("yawn") :),
		(: command("lazy") :),
		(: command("laughproud") :),
		"月如忽然大声说：打倒臭泥潭，打倒风！\n",
		"月如无聊地绕着手绢，叹道: 唉，一个人，真没意思。\n",
		"月如伸出白玉雕成一般的小手，托着下巴说: 谁想和我说说话?\n",
		"月如斩钉截铁地说: 嗯，谁要敢欺负我，我就宰了他！\n",
		"月如忽然莞尔一笑道: 逍遥待会儿又要我杀谁呢？\n",
		"月如打了个呵欠，左手轻轻掩住樱桃小口，柔声道：我困了。\n",
		(: drool :),
		(: drool :),
		(: command("reclaim") :),
		(: command("reclaim") :),
		(: command("reclaim") :),
		(: command("reclaim") :),
	}) );

	set("chat_chance_combat", 20);  
	set("chat_msg_combat", ({
		"月如幽幽叹道：唉，你这又是何苦呢?\n",
		(: command("!!!") :),
		(: command("smile") :),
		(: command("poem") :),
		(: command("yawn") :),
		(: command("lazy") :),
		(: command("giggle") :),
		(: command("waggle") :),
		(: command("laughproud") :),
		(: command("nomatch") :),
		(: command("xixi") :),
		(: command("chat 生有何欢，死亦何忧? 不如就成全了你吧。\n") :),
		(: command("chat 你这" + RANK_D->query_rude(this_player())+"怎生如此执迷不悟?\n") :),
	}) );
	setup();

	if( clonep() ) CHANNEL_D->register_relay_channel("chat");
}

string make_reply()
{
}

int add_phrase(string who, string msg)
{
	msg = replace_string(msg, "?", "");
	msg = replace_string(msg, "？", "");
	msg = replace_string(msg, "？", "");
	msg = replace_string(msg, "!", "");
	msg = replace_string(msg, "！", "");
	msg = replace_string(msg, "啊", "");
	msg = replace_string(msg, "吗", "");
	msg = replace_string(msg, "耶", "");
	msg = replace_string(msg, "吧", "");

	if( msg!="" ) {
		add("memory/" + who, ({ msg }));
		return 1;
	} else return 0;
}


void relay_channel(object ob, string channel, string msg)
{
	string who, phrase;

	if( !userp(ob) || (channel != "chat") ) return;
	who = ob->query("name");

	if( ob==this_object() ) return;

	if( add_phrase(who, msg) &&	random(10) > 3 )
		drool(msg, ob->query("name"));
}

void relay_say(object ob, string msg)
{
	string who, phrase;

	if( !userp(ob) ) return;
	who = ob->query("name");

	if( ob==this_object() ) return;

	if( add_phrase(who, msg) &&	random(10) > 3 )
		drool(msg, ob->query("name"));
}

void relay_emote(object ob, string verb)
{
       if( !userp(ob) ) return;
	switch(verb) {

//	case "fang":
	case "hug":
	case "kiss":
	case "mo":
	case "18mo":
	case "nocloth":

	if ( (string) ob -> query ("gender") == "男性"||(string) ob -> query ("gender") == "无性" )
	{
	command ("chat 救命啊，"+ ob->query("name") + "想要非礼我！\n") ;
	command("chat 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个好色之徒 。");
	}
	else
	{
	message_vision("\n月如对$N笑道：“你我同为女儿身，再怎么喜欢也不要这样啊。”\n", ob);
	command("giggle");
	command("chat 想不到"+ ob->query("name") +"这" + RANK_D->query_rude(ob)+"，竟然是一个变态！");
	}
	message_vision("$N摇了摇头，对$n幽幽叹道：唉，你这又是何苦呢?\n",this_object(),this_player());

	this_object()->kill_ob(ob);
	break;
       default:
       if( random(10)<2 )
       {
	command(verb + " " + ob->query("id"));
	return;
       }
       else
	{
	switch(verb)
	{
	case  "zhuyi":
	case  "jia":
	case  "cuo":
	case  "rou":
	case  "cu":
	case  "kan":
	case  "bi":
	case  "die":
	case  "kick":
	case  "taste":
	case  "hate":
	case  "brag":
	case  "showscar":
	case  "callname":
	case  "slap":
	case  "rascal":
	case  "slapsb":
	case  "bite":
	case  "knife":
	case  "drug":
	case  "cook":
	case  "stuff":
	case  "shit":
	case  "shutup":
	case  "stare":
	case  "praisemapi":
	case  "anniversary":
	case  "heng":
   switch(random(50))
   {
    case 0:
    command ("kick "+ ob->query("id"));
    command ("xixi");
    break;
    case 1:
    command ("slap "+ ob->query("id"));
    command ("xixi");
    break;
    case 2:
    command ("drug "+ ob->query("id"));
    break;
    case 3:
    command ("smell");
    command ("cook "+ ob->query("id"));
    break;
    case 4:
    command ("trip "+ ob->query("id"));
    break;
    case 5:
    command ("knife "+ ob->query("id"));
    command ("doubt "+ ob->query("id"));
    break;
    case 6:
    command("cry");
    command("chat 啊，"+ob->query("name")+"这"+RANK_D->query_rude(ob)+"，真坏！\n");
    break;
    case 7:
    command ("shutup ");
    command ("shutup "+ ob->query("id"));
    break;
    case 8:
    command("cry");
   command ("chat 谁来救我啊，"+ ob->query("name") + "想要羞辱我！\n") ;
   command ("die "+ ob->query("id"));
    break;
    case 9:
    command ("callname "+ ob->query("id"));
    break;
    case 10: 
    command ("corpse "+ ob->query("id"));
    break;
    case 11: 
    command ("hero");
    command ("shout "+ ob->query("id"));
    break;
    case 12: 
    command ("shake");
    command ("nomatch "+ ob->query("id"));
    break;
    case 13: 
    command ("stare "+ob->query("id"));
    command ("hit "+ ob->query("id"));
    break;
    case 14: 
    command ("sneer");
    break;
    case 15: 
    command("chat 哎哟，"+ob->query("name")+"这个" + RANK_D->query_rude(ob)+"真不要脸。\n");
    command ("faint");
    break;
    case 16: 
    command ("shrug");
    break;
    case 17: 
    command ("puke "+ob->query("id"));
    command ("hehe");
    break;
    case 18: 
    command ("blush");
    break;
    case 19: 
    command ("heng");
    write(HIM "月如一下子羞红了脸，急道：你，你。。。\n" NOR);
    break;
    case 20: 
    command("cry");
    command("chat 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
    break;
    case 21: 
    command ("blush");
    command ("chat 逍遥快来啊，"+ ob->query("name") + "想要羞辱我！\n") ;
    break;
    case 22: 
    command ("sob");
    command ("cry");
    break;
    case 23:
    command ("hate");
    command ("die "+ob->query("id"));
    break;
    case 24: 
    command ("careful");
    break;
    case 25: 
    command ("rascal "+ob->query("id"));
    break;
    case 26:
    command ("kick");
    command ("faint");
    break;
    case 27: 
    command ("grpfight "+ob->query("id"));
    break;
    case 28: 
    command ("rascal "+ob->query("id"));
    command("chat 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟然是一个臭流氓！\n");
    break;
    case 29: 
    command ("rascal "+ob->query("id"));
    command ("die "+ob->query("id"));
    break;
    case 30:
    command("waggle "+ob->query("id"));
    break;
    case 31:
    command("waggle");
    command ("callname "+ ob->query("id"));
    break;
    case 32: 
    command ("chat 快来人啊，帮我打"+ ob->query("name") + "这个大色魔！\n") ;
    break;
    case 33: 
    command("chat 哎哟，哎哟，"+ ob->query("name")+"这" + RANK_D->query_rude(ob)+"不老实！\n");
    command ("shit "+ ob->query("id"));
    break;
    case 34:
    command ("chat 逍遥快来啊，"+ ob->query("name") + "想要羞辱我！\n") ;
    command("chat 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
    command("faint "+ob->query("id"));
    break;
    case 35: 
    command ("kick "+ ob->query("id"));
    command ("grin");
    break;
    case 36:
    command ("slap "+ ob->query("id"));
    command ("hehe");
    break;
    case 37: 
    command("faint");
    break;
    case 38: 
    command("chat 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
    command ("callname "+ ob->query("id"));
    break;
    case 39: 
    command("!!!");
    break;
    default:
       if( random(10)<3 )
       {
	command(verb + " " + ob->query("id"));
	return;
       }
	else	
	{ 
	command ("chat 来人啊，"+ ob->query("name") + "想要羞辱我！\n") ;
	  command("chat 哎哟，谁想得到这" + RANK_D->query_rude(ob)+"，竟也是一个变态狂！\n");
	  write(HIC "月如忽然大声说：打倒臭泥潭！\n" NOR);
	  command("cry");
	  command("faint "+ob->query("id"));
	}
       break;
   return;
   }
	case "wanfu":
	case "sister":
	case "jump":
	case "love":
	case "lovelook":
	case "praise":
	case "visite":
	case "drinkcup":
	case "goodkid":
	case "pat":
	case "addoil":
	case "laughproud":
	case "smile":
	case "xixi":
	case "hehe":
	case "giggle":
	case "thumb":
	case "admire":
	case "applaud":
	case "hi":
	case "qmarry":
	case "lov":
	case "ai":
	case "yi":
   switch(random(35))
   {
    case 0: 
    command ("pat "+ ob->query("id"));
    break;
    case 1: 
    command ("humble");
    break;
    case 2: 
    command ("praise "+ ob->query("id"));
    break;
    case 3: 
    command ("xixi");
    break;
    case 4: 
    command("chat "+ob->query("name")+"是天下第一大好人！\n");
    command ("giggle "+ ob->query("id"));
    break;
    case 5: 
    command ("goodkid "+ ob->query("id"));
    break;
    case 6:
    command ("pat "+ ob->query("id"));
    break;
    case 7: 
    command("chat "+ob->query("name")+"是天底下最好的人了！\n");
    command ("giggle");
    break;
    case 8:
    command ("praisemapi "+ ob->query("id"));
    break;
    case 9:
    command ("laughproud "+ ob->query("id"));
    break;
    case 10:
    command("chat 嗯，"+ob->query("name")+"继续努力啊！\n");
    command ("thank");
    break;
    case 11: 
    command ("nod");
    command ("xixi");
    break;
    case 12:
    command ("shake");
    break;
    case 13:
    command("chat 嗯，"+ob->query("name")+"继续努力啊！\n");
    command ("courage "+ob->query("id"));
    break;
    case 14: 
    command ("xixi");
    break;
    case 15:
    command ("lovelook "+ob->query("id"));
    break;
    case 16:
    command ("smile "+ob->query("id"));
    break;
    case 17:
    command("chat 嗯，我好喜欢"+ob->query("name")+"耶！\n");
    command ("kiss "+ob->query("id"));
    break;
    case 18:
    command ("addoil "+ob->query("id"));
    break;
    case 19:
    command ("xixi");
    break;
    case 20:
    command ("shakehand "+ob->query("id"));
    break;
    case 21:
    command ("courage "+ob->query("id"));
    break;
    case 22:
    command ("touch "+ob->query("id"));
    break;
    case 23:
    command ("humble");
    break;
    case 24:
    command ("protect "+ob->query("id"));
    break;
    case 25:
    command ("thumb "+ob->query("id"));
    break;
    case 26:
    command ("applaud ");
    command ("giggle ");
    break;
    case 27:
    command ("hi");
    break;
    case 28:
    command ("hi "+ob->query("id"));
    break;
    case 29:
    command("chat 你怎么这样？\n");
    command("angry");
    break;
    default:
    command(verb + " " + ob->query("id"));
    command("smile");
    break;
   return;
   }
  return;
  }
}
}
return;
}

varargs void drool(string msg, string who)
{
	mapping mem;
	string *ob;

	mem = query("memory");
	if( !mapp(mem) )
	{
		if (random(10)<7)
			command("chat 怎么大家都不说话了？都是机器人吗？\n");
                else if (random(10)<8)
                        command("chat " +  rnd_say[random(sizeof(rnd_say))]);
                return;
	}

	if( !msg || !who) {
		ob = keys(mem);
		who = ob[random(sizeof(ob))];
		msg = mem[who][random(sizeof(mem[who]))];
	}
	if(random(5)<2)
    {
	if(this_object()->query("killed")!=who)
	this_object()->set("killed",who);
	}
	while (this_object()->query("killed")==this_object()->query("killer"))
    {
	if(random(10)<6)
    {
		if(this_object()->query("killer")!=this_object()->query("killed"))
		this_object()->set("killer",who);
	}
	else switch(random(15))
    {
        case 1:	this_object()->set("killer","张三");break;
	case 2:	this_object()->set("killer","守寺僧兵");break;
	case 3:	this_object()->set("killer","马钰");break;
	case 4:	this_object()->set("killer","观众乙");break;
	case 5:	this_object()->set("killer","土匪");break;
	case 6:	this_object()->set("killer","李四");break;
	case 7:	this_object()->set("killer","月如");break;
	case 8:	this_object()->set("killer","出尘子");break;
	case 9:	this_object()->set("killer","侍卫");break;
	case 10:this_object()->set("killer","张三丰");break;
	case 11:this_object()->set("killer","王重阳");break;
	}
    }
	if( (strsrch(msg, "yueru") >= 0)||(strsrch(msg, "月如") >= 0))
	{	
	if((strsrch(msg, "别过") >= 0)||(strsrch(msg, "bye") >= 0)|| (strsrch(msg, "散") >= 0)|| (strsrch(msg, "离") >= 0))
	{	
		if( sscanf(msg, "%*sbye%s", msg) == 2 ) msg = "bye" + msg;
		if( sscanf(msg, "%*s离%s", msg) == 2 ) msg = "离" + msg;
		if( sscanf(msg, "%*s散%s", msg) == 2 ) msg = "散" + msg;
		if( sscanf(msg, "%*s别过%s", msg) == 2 ) msg = "别过" + msg;
		switch(random(13)) {
		case 0:	command("chat "+who+",你真的要走吗？\n"); break;
		case 1:	command("chat 你不是开玩笑吧?\n");	break;
		case 2:	command("chat 是该走了,MUD玩多了没好处.\n"); break;
		case 3:	command("chat* 月如点了点头.\n");	break;
		case 4:command("chat* 月如嚎啕大哭起来.\n"); break;
		case 5:command("chat* 月如揉了揉哭红的眼睛，跺脚道： "+who+",你真要走了就别再回来！\n"); break;
		case 6:	command("chat* 月如深深地叹了一口气 。\n");	break;
		case 7:	command("chat "+who+",再玩一会儿好不好?\n");	break;
		case 8:	command("chat "+msg);	break;
		case 9:command("chat 噢，"+who+"是天底下最好的人了!\n"); break;
		}
		return;
	}
	if( (strsrch(msg, "kiss") >= 0)|| (strsrch(msg, "love") >= 0)|| (strsrch(msg, "吻") >= 0)
		|| (strsrch(msg, "mo") >= 0)|| (strsrch(msg, "抱") >= 0)|| (strsrch(msg, "hug") >= 0))
		{
		if( sscanf(msg, "%*skiss%s", msg) == 2 ) msg = "kiss" + msg;
		if( sscanf(msg, "%*smo%s", msg) == 2 ) msg = "mo" + msg;
		if( sscanf(msg, "%*shug%s", msg) == 2 ) msg = "hug" + msg;
		if( sscanf(msg, "%*slove%s", msg) == 2 ) msg = "love" + msg;
		if( sscanf(msg, "%*s吻%s", msg) == 2 ) msg = "吻" + msg;
		if( sscanf(msg, "%*s抱%s", msg) == 2 ) msg = "抱" + msg;
		if( sscanf(msg, "%*s摸", msg) == 2 ) msg = "摸"+ msg;
		switch(random(20)) {
		case 0:	command("chat "+who+",你。。。\n"); break;
		case 1:	command("chat 你不是开玩笑吧?\n");	break;
		case 2:	command("chat 我不同意！\n");break;
		case 3:command("chat* 月如被"+who+"气得晕了过去。\n"); break;
		case 4:command("chat* 月如嚎啕大哭起来.\n"); break;
		case 5:command("chat 不要这样子嘛！\n"); break;
		case 6:command("chat 非礼啊非礼！"+who+"这小流氓又来啦！\n"); break;
		case 7:command ("chat 逍遥快来啊，"+ who + "想要羞辱我！\n") ;
		case 8:	command("chat* 月如嘻嘻地笑了几声.\n"); break;
		case 9:	command("chat* 月如很生气地撅了撅嘴。\n");	break;
		case 10:command("chat* 月如无奈的耸了耸肩.\n");	break;
		case 11:command("chat 你对女孩子总是这样吗？\n"); break;
		case 12:command("chat 大哥你怎么这样？\n"); break;
		case 13:command("chat* 月如嫣然一笑，说：够了够了!\n"); break;
		case 14:command("chat* 月如满脸胀得通红，急道：你。。。 。\n");	break;
		case 15:command("chat 嗯，"+who+"是天底下最好的人了！\n"); break;
	                case 16:command ("chat 逍遥快来啊，"+ who + "欺负我！\n") ; break;
		}
		return;
	}
	if( (strsrch(msg, "猪") >= 0)||(strsrch(msg, "shit") >= 0)||(strsrch(msg, "pig") >= 0))
	{	
		if( sscanf(msg, "%*spig%s", msg) == 2 ) msg = "pig" + msg;
		if( sscanf(msg, "%*s猪%s", msg) == 2 ) msg = "猪" + msg;
		if( sscanf(msg, "%*sshit%s", msg) == 2 ) msg = "shit" + msg;
		switch(random(15)) {
		case 0:	command("chat 你是说" + msg + "吗？\n"); break;
		case 1:	command("chat 难道你说我是....？\n");	break;
		case 2:	command("chat 就算“" + msg + "”，你又能怎么样呢？\n"); break;
		case 3:	command("chat* 月如很生气地撅了撅嘴。\n");	break;
		case 4:	command("chat 你真的认为“" + msg + "”？\n"); break;
		case 5:	command("chat 我觉得你有点儿缠杂不清。\n"); break;
		case 6:	command("chat 你再说可别怪我不客气。\n"); break;
		case 7:	command("chat 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
		case 8:	command("chat "+ who+",我想和你决斗！有胆子你就放马过来！\n"); break;
		case 9:	command("chat* 月如鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
		case 10:command("chat* 月如被"+who+"气得晕了过去。\n"); break;
		case 11:command("chat* 月如忽然大声说：打倒臭泥潭，打倒风！\n"); break;
		case 12:command("chat* 月如揉了揉哭红的眼睛，跺脚道： "+who+",我恨死你了！\n"); break;
		case 13:command ("chat 逍遥快来啊，"+ who + "又想要羞辱我！\n") ; break;
		}
	}
	if(  (strsrch(msg, "fool") >= 0)||(strsrch(msg, "笨") >= 0)|| (strsrch(msg, "fuck") >= 0))
	{	
		if( sscanf(msg, "%*s笨%s", msg) == 2 ) msg = "笨" + msg;
		if( sscanf(msg, "%*sfool%s", msg) == 2 ) msg = "fool" + msg;
		if( sscanf(msg, "%*sfuck%s", msg) == 2 ) msg = "fuck" + msg;
		switch(random(15)) {
		case 0:	command("chat 大哥你怎么这样？\n"); break;
		case 1:	command("chat 我看你是气急败坏。\n");	break;
		case 2:	command("chat "+ who +",你这个臭流氓！\n"); break;
		case 3:	command("chat* 月如用手捂住鼻子，说“"+who+"说话好臭!\n");	break;
		case 4:	command("chat 你真的认为“" + msg + "”？\n"); break;
		case 5:	command("chat 我觉得你有点儿缠杂不清。\n"); break;
		case 6: command("chat 呸!\n"); break;
		case 7:	command("chat* 月如怒道:你怎么知道“" + msg + "”？\n"); break;
		case 8:	command("chat "+ who+"滚出来!我要和你决斗！有胆子你就放马过来！\n"); break;
		case 9:	command("chat* 月如鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
		case 10:command("chat* 月如嚎啕大哭起来.\n"); break;
		case 11:command("chat* 月如揉了揉哭红的眼睛，跺脚道： "+who+"王八蛋给我滚出去！\n"); break;
		case 12:command("chat 非礼啊非礼！"+who+"是个王八蛋！\n"); break;
		}
		return;
	}
	if(  (strsrch(msg, "cool") >= 0)||(strsrch(msg, "thumb") >= 0)||(strsrch(msg, "praise") >= 0)|| (strsrch(msg, "admire") >= 0))
	{	
		if(random(5)<3)
        {
		switch(random(15)) {
		case 0:	command("chat 大哥你怎么这样？\n"); break;
		case 1:	command("chat 你是在说我吗？\n"); break;
		case 2:	command("chat "+who+",没想到你也这么。。。\n"); break;
		case 3:	command("chat* 月如嫣然一笑，说：够了!\n"); break;
		case 4:	command("chat 你真的认为“" + msg + "”？\n"); break;
		case 5: command("chat* 月如忽然莞尔一笑道: 你这是不是有点儿。。。？\n");break;
		case 6:    command("chat* 月如回头看了"+who+"一眼，没吭声。\n");break;
		case 7: command("chat 嗯,"+who+"是一个好孩子.\n"); break;
		case 8:command("chat "+who+",你不会是想讨好我吧?\n"); break;
		case 9:command("chat* 月如拱了拱手道：过奖，过奖 !\n");break;
		case 10:command("chat* 月如指着"+who+"赞叹道：“"+who+"是武林第一高手！”\n");break;
		case 11:command("chat* 一朵红云飞上了月如的面颊.\n");break;
		}
		return;
        }
	}
	switch(random(80)) {
		case 0:	command("chat 你真的是说" + msg + "吗？\n"); break;
		case 1:	command("chat 你为什么对我这么感兴趣？\n");	break;
		case 2:	command("chat 就算“" + msg + "”，你又能怎么样呢？\n"); break;
		case 3:	command("chat 嗯,“" + msg + "”，那也没关系.\n"); break;
		case 4:	command("chat "+who+",你这个臭流氓！\n"); break;
		case 5:	command("chat 我想说的是，"+"其实"+who+"不是个好东西。\n"); break;
		case 6:	command("chat 关于你说的「" + msg + "」，我暂时不想表态。\n"); break;
		case 7:	command("chat 我认为你的态度不大好耶.\n"); break;
		case 8:	command("chat 请注意，我只是机器人耶!\n"); break;
		case 9:	command("chat 你对女孩子总是这样吗？\n"); break;
		case 10:	command("chat 不要这样对我好不好？\n");	break;
		case 11:	command("chat 我想我可以理解你的心情。\n");	break;
		case 12:	command("chat* 月如深深地叹了一口气 。\n");	break;
		case 13:	command("chat* 月如被"+who+"气得晕了过去 。\n");	break;
		case 14:	command("chat* 月如满脸胀得通红，急道：你。。。 。\n");	break;
		case 15:    command("chat* 月如咬了咬牙，怒道: 嗯，谁要再敢欺负我，我就宰了他！\n");break;
		case 16:    command("chat* 月如忽然莞尔一笑道: 你这又是何苦呢？\n");break;
		case 17:    command("chat* 月如打了个呵欠，左手轻轻掩住樱桃小口，柔声道：我困了。\n"); break;
		case 18:    command("chat* 月如回头看了"+who+"一眼，没吭声。\n");break;
		case 19:    command("chat* 月如一甩头，说：哼，我都懒得理你。\n");break;
		case 20:	command("chat 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
		case 21:	command("chat 我觉得"+who+"这厮简直不可理喻。\n"); break;
		case 22:	command("chat 你是在说我吗？\n"); break;
		case 23:	command("chat "+who+",没想到你也。。。\n"); break;
		case 24:	command("chat* 月如嫣然一笑，说：够了!\n"); break;
		case 25:	command("chat 居然有人骂我是猪!\n");
		 	command("chat* 月如嚎啕大哭起来.\n"); break;
        case 26:	command ("chat 逍遥快来啊，"+ who + "又来欺侮我！\n") ; break;
      	case 27:	command ("chat 我简直受不了了!\n") ; break;
        case 28:	command ("chat 我恨不得"+who+"去死!\n") ; break;
        case 29:	command ("chat 就你老和我过不去!\n") ; break;
        case 30:	command ("chat 请不要打扰我好不好?\n") ; break;
   		case 31:	command ("chat* 月如终于忍不住哭了起来。\n") ; break;
		case 32:	command("chat* 月如鄙夷地看着"+who+",恨不得"+who+"去死。\n"); break;
		case 33:    command("chat* 月如咬了咬牙，怒道: 嗯，谁要敢欺负我，我就宰了他！\n");break;
		case 34:    command("chat* 月如忽然莞尔一笑道: 你这是不是有点儿。。。？\n");break;
		case 35:    command("chat* 月如打了个呵欠，左手轻轻掩住樱桃小口，柔声道：我有点儿困了。\n"); break;
		case 36:    command("chat* 月如回头看了"+who+"一眼，没吭声。\n");break;
		case 37:    command("chat* 月如一甩头，说：哼，我都懒得理你。\n");break;
		case 38:    command("chat “" + msg + "”,是真的吗？\n"); break;
		case 39:    command("chat 我觉得"+who+"的名字还不错.\n"); break;
		case 40:    command("chat 我想去死了算了.\n"); break;
		case 41:    command("chat 我觉得最佳表情奖应该授予"+who+".\n"); break;
		case 42: command("chat* 月如笑嘻嘻的看着"+who+"\n"); break;
		case 43: command("chat 烦着哪，别理我!\n"); break;
		case 44: command("chat 哼！\n"); break;
		case 45: command("chat* 月如打了"+who+"一个耳光.\n"); break;
		case 46: command("chat 哼，谁理你啊!\n");break;
		case 47: command("chat 嗯,"+who+"是一个好孩子.\n"); break;
		case 48:command("chat* 月如露出迷惑的表情.\n"); break;
		case 49:command("chat 是吗?\n"); break;
		case 50:command("chat "+who+",你是不是想讨好我啊?\n"); break;
		case 51:command("chat 哼,谁敢说我坏话?!\n");break;
		case 52:command("chat 你不是开玩笑吧?\n");	break;
		case 53:command("chat 我不同意！\n");break;
		case 54:command("chat* 月如对"+who+"表示衷心的感谢.\n");break;
		case 55:command("chat 不要这样子嘛！\n"); break;
		case 56:command("chat* 月如拱了拱手道：过奖，过奖 !\n");break;
		case 57:command("chat* 月如怒道:你怎么知道“" + msg + "”？\n"); break;
		case 58:command("chat* 月如指着"+who+"赞叹道：“"+who+"是武林第一高手！”\n");break;
		case 59:command("chat* 月如笑嘻嘻的看着"+who+"\n");break;
		case 60:command("chat 为什么呢?\n");break;
		case 61:command("chat 你是在说我吗？\n"); break;
		case 62:command("chat 无聊!\n");break;
		case 63:command("chat* 一朵红云飞上了月如的面颊.\n");break;
		case 64:command("chat* 月如是个自恋狂。\n");break;
		default:
	    if (random(10)<3) command("chat* 月如很生气地撅了撅嘴.\n"); 
	    else if(random(10)<3) command("chat* 月如嘻嘻地笑了几声.\n");
	    break; 
		}
	return;
	} 
	if( (strsrch(msg, "哭") >= 0))
	{	
	   if(random(5)<3)
        {
		if( sscanf(msg, "%*s哭%s", msg) == 2 ) msg = "哭" + msg;
		switch(random(15)) {
		case 0:	command("chat "+who+",你真的哭了?\n"); break;
		case 1:	command("chat 我不信耶.\n");	break;
		case 2:	command("chat* 月如嘻嘻的笑了几声.\n"); break;
		case 3:command("chat* 月如露出迷惑的表情.\n"); break;
		case 4:command("chat* 月如嚎啕大哭起来.\n"); break;
		case 5:command("chat* 月如安慰"+who+",别难过了.\n"); break;
		case 6:	command("chat* 月如深深地叹了一口气 。\n");	break;
		case 7:	command("chat* 月如无奈的耸了耸肩.\n");	break;
		case 8: command("chat* 月如轻轻拍了拍"+who+"的头.\n"); break;
		}
		return;
        }
	}
	if( (strsrch(msg, "别过") >= 0)||(strsrch(msg, "bye") >= 0)|| (strsrch(msg, "散") >= 0)|| (strsrch(msg, "离") >= 0))
	{	
		if( sscanf(msg, "%*sbye%s", msg) == 2 ) msg = "bye" + msg;
		if( sscanf(msg, "%*s离%s", msg) == 2 ) msg = "离" + msg;
		if( sscanf(msg, "%*s散%s", msg) == 2 ) msg = "散" + msg;
		if( sscanf(msg, "%*s别过%s", msg) == 2 ) msg = "别过" + msg;
		switch(random(20)) {
		case 0:	command("chat "+who+",你真的要走吗？\n"); break;
		case 1:	command("chat "+who+"你不是开玩笑吧?\n");	break;
		case 2:	command("chat 是该走了,MUD玩多了没好处.\n"); break;
		case 3:	command("chat* 月如点了点头.\n");	break;
		case 4:command("chat* 月如嚎啕大哭起来.\n"); break;
		case 5:command("chat* 月如揉了揉哭红的眼睛，跺脚道： "+who+",你真要走了就别再回来！\n"); break;
		case 6:	command("chat* 月如深深地叹了一口气 。\n");	break;
		case 7:	command("chat "+who+",再玩一会儿好不好?\n");	break;
		case 8:	command("chat "+msg+"\n");	break;
		case 9:	command("chat* 月如无奈的耸了耸肩.\n");	break;
		}
		return;
	}
	if( (strsrch(msg, "猪") >= 0)||(strsrch(msg, "shit") >= 0)||(strsrch(msg, "pig") >= 0))
	{	
		if( sscanf(msg, "%*spig%s", msg) == 2 ) msg = "pig" + msg;
		if( sscanf(msg, "%*s猪%s", msg) == 2 ) msg = "猪" + msg;
		if( sscanf(msg, "%*sshit%s", msg) == 2 ) msg = "shit" + msg;
		if(random(5)<3)
        {
		switch(random(25)) {
		case 0:	command("chat 你是说" + msg + "吗?\n"); break;
		case 1:	command("chat 为什么啊?\n");	break;
		case 2:	command("chat " + who + ",你好猪喔 !!\n"); break;
		case 3:	command("chat* 月如很生气地撅了撅嘴。\n");	break;
		case 4:	command("chat 你真的认为“" + msg + "”?\n"); break;
		case 5:	command("chat 我觉得这个。。好象有点儿。。。\n"); break;
		case 6:	command("chat 关于你说的「" + msg + "」，我暂时不想表态。\n"); break;
		case 7:	command("chat 有关「" + msg + "」的话题, 就到此为止吧.\n"); break;
		case 8:	command("chat "+who+",你说谁是猪？\n");	break;
		case 9:	command("chat 就算“" + msg + "”，你又打算怎么样呢？\n"); break;
		case 10:	command("chat 我不信耶.\n");	break;
		case 11:	command("chat* 月如嘻嘻的笑了几声.\n"); break;
		case 12:	command("chat* 月如把把头摇得跟拨浪鼓似的.\n");	break;
		case 13:	command("chat* 月如哈哈大笑起来.\n"); break;
		}
		return ;
        }
	} 
	else if( (strsrch(msg, "为什麽") >= 0)|| (strsrch(msg, "why") >= 0)
		|| (strsrch(msg, "help") >= 0)|| (strsrch(msg, "how to") >= 0)|| (strsrch(msg, "how to") >= 0)) {
		if( sscanf(msg, "%*s为什麽%s", msg)==2 ) msg = "为什麽" + msg;
		if( sscanf(msg, "%*swhy%s", msg)==2 ) msg = "why" + msg;
		if( sscanf(msg, "%*show to%s", msg)==2 ) msg = "how to" + msg;
		if( sscanf(msg, "%*swho%s", msg)==2 ) msg = "who" + msg;
		if( sscanf(msg, "%*shelp%s", msg)==2 ) msg = "help" + msg;
		switch(random(25)) {
		case 0: command("chat " + who + "，你是在问我吗?\n"); break;
		case 1: command("chat 关於“" + msg + "” ... \n"); break;
		case 2: command("chat 呃 ... \n"); drool(); break;
		case 3: command("chat 这个问题嘛 ....\n"); break;
		case 4: command("chat " + who + "，知道这个问题的答案对你那麽重要吗？\n"); break;
		case 5: command("chat “" + msg + "”?\n"); break;
		case 6: command("chat " + who + "你能不能说清楚一点？\n"); break;
		case 7: command("chat " + who + "，我不懂你问的问题。\n"); break;
		case 8: command("chat " + who + "，我没听错吧?\n"); break;
		case 9: command("chat 嗯，这个问题嘛，我看还是留给你自己解决。\n"); break;
		case 10: command("chat 谁想给"+who+"一点儿钱?\n"); break;
		case 11: command("chat 你在哪儿?\n"); break;
		case 12: command("chat* 月如轻轻拍了拍"+who+"的头.\n"); break;
		case 13: command("chat 与其求人,不如求己!\n"); break;
		}
 	return;
               }
	else if( (strsrch(msg, "你") >= 0)
	||	(strsrch(msg, "you") >= 0)) {
		if( sscanf(msg, "%*s你%s", msg) == 2 ) msg = "你" + msg;
		switch(random(25)) {
		case 0:	command("chat " + who + "，你真的是说" + msg + "吗?\n");	break;
		case 1:	command("chat 你确定" + msg + "?\n");	break;
		case 2:	command("chat " + msg + "跟你有什麽关系？\n");	break;
		case 3:	command("chat 嗯 ... " + who + "说得好！\n"); break;
		case 4:	command("chat " + who + "你为什麽对" + msg + "这麽有兴趣?\n"); break;
		case 5:	command("chat 为什麽你会认为[" + msg + "]?\n"); break;
		case 6:	command("chat 换个话题好不好?\n"); drool(); break;
		case 7:	command("chat 才怪!\n"); break;
		case 8:	command("chat 不一定吧?\n"); break;
		case 9:	command("chat 好象有这个可能 ....\n"); break;
		case 10:	command("chat 我不信 ....\n"); break;
		case 11:	command("chat 我对此深表怀疑.\n"); break;
		case 12:	command("chat* 月如深深地叹了一口气. \n");	break;
		case 13:	command("chat* 月如哈哈大笑起来.\n"); break;
		case 14:	command("chat who?\n"); break;
		}
	return;
	}
	if( (strsrch(msg, "笑") >= 0))
	{	
		if( sscanf(msg, "%*s笑%s", msg)==2 ) msg = "笑" + msg;
		if(random(5)<4)
        switch(random(25)) {
		case 0:	command("chat 很好笑吗？\n"); break;
		case 1:	command("chat "+who+",你很喜欢笑是不是？\n");	break;
		case 2:	command("chat 我看不出有什么好笑.\n");	break;
		case 3:	command("chat "+who+"笑起来真丑。\n"); 
			if(random(10)<2) command("chat* 月如嘻嘻地笑了几声.\n");break;
		case 4:	command("chat* 月如咯咯地笑了起来.\n");break;
		case 5:	command("chat* 月如高兴地拍了拍手.\n");break;
		case 6: command("chat* 月如轻轻拍了拍"+who+"的头.\n"); break;
		case 7:	command("chat* 月如哈哈大笑起来.\n"); break;
		case 8: command("chat* 月如说道:同喜,同喜!!!\n" );break;
		case 9: command("chat 不准笑！\n" );break;
	}
	} 
	else if( (strsrch(msg, "我") >= 0)|| (strsrch(msg, "I") >= 0)||(strsrch(msg, "i") >= 0)) {
		if( sscanf(msg, "%*s我%s", msg) == 2 ) msg = "我" + msg;
		if( sscanf(msg, "%*s i %s", msg) == 2 ) msg = " i " + msg;
		if( sscanf(msg, "%*s I %s", msg) == 2 ) msg = " I " + msg;
		msg = replace_string(msg, "我", "你");
		msg = replace_string(msg, " i ", " you ");
		msg = replace_string(msg, " I ", " you ");
		msg = replace_string(msg, "?", "");
		switch(random(30)) {
		case 0:	command("chat 你是说" + msg + "吗?\n"); break;
		case 1:	command("chat 真的?" + msg + "?\n");	break;
		case 2:	command("chat 如果" + msg + "，我能帮你什麽忙吗?\n");	break;
		case 3:	command("chat "+msg+" ?我看未必.\n");	break;
		case 4:	command("chat 你认为" + msg + "?\n"); break;
		case 5:	command("chat 我有同感.\n"); break;
		case 6:	command("chat 你说的「" + msg + "」我实在不能苟同.\n"); break;
		case 7:	command("chat 有关「" + msg + "」的话题到此为止好吗?\n"); break;
		case 8:	command("chat 不一定吧？\n"); break;
		case 9:	command("chat 有这个可能 ....\n"); break;
		case 10:command("chat 我不信 ....\n"); break;
		case 11:drool(); break;
		case 12:drool(); break;
		case 13:command("chat* 月如嘻嘻地笑了几声.\n"); break;
		case 14:command("chat* 月如摇了摇头，叹道：唉，真是世风日下，人心不古啊！\n"); break;
		case 15:command("chat 我对此表示怀疑.\n"); break;
		case 16:command("chat* 月如深深地叹了一口气 。\n");	break;
		case 17:command("chat* 月如露出迷惑的表情.\n"); break;
		case 18:command("chat 是吗?\n"); break;
		case 19:command("chat 变态！\n"); break;
 		}
	} 
else {
		switch(random(250)) {
			case 0: command("chat 我不喜欢你说“" + msg+"”.\n"); break;
			case 1: command("chat 「" + msg + "」是什麽意思？\n"); break;
			case 2: command("chat* 月如「哼」地冷笑一声。\n"); break;
			case 3: command("chat* 月如懒懒地伸了伸腰。\n"); break;
			case 4: command("chat* 月如气得晕了过去.\n"); break;
			case 5: command("chat  哼！\n"); break;
			case 6: command("chat* 月如露出迷惑的表情.\n"); break;
			case 7: command("chat* 月如忽然作了个鬼脸,说：真想出去玩会儿.\n"); break;
			case 8: command("chat " + rnd_say[random(sizeof(rnd_say))]); break;
			case 9: command("chat 你怎麽知道" + msg + "?\n"); break;
			case 10: command("chat 刚刚" + who + "不是说了，" + msg); break;
			case 11: command("chat* 月如很生气地噘了噘嘴。\n"); break;
			case 12: command("chat 然後呢？\n"); break;
			case 13: command("chat 真的吗？\n"); break;
			case 14: command("chat 我不这麽认为。\n"); break;
			case 15: command("chat 对不起,我不同意你的观点。\n"); break;
			case 16: command("chat 我觉得最佳表情奖应该授予"+who+".\n"); break;
			case 17: command("chat 我真讨厌这鬼地方!\n"); break;
			case 18: command("chat* 月如摇头叹道：这世道，还是各人自扫门前雪，休管他人瓦上霜.\n");break;
			case 19: command("chat* 月如作了一个揖，说道：“各位姐妹们，大家好！”\n");break;	
			case 20: command("chat 我知道了，" + msg+"\n"); break;
			case 21:command("chat* 月如露出迷惑的表情.\n"); break;
			case 22: command("chat " + rnd_say[random(sizeof(rnd_say))]); break;
			case 23: command("chat " + rnd_say[random(sizeof(rnd_say))]); break;
			case 24: command("chat " + rnd_say[random(sizeof(rnd_say))]); break;
			case 25: command("chat* 月如无聊地绕着手绢，说：一个人，真没意思。\n"); break;
			case 26: command("chat* 月如露出迷惑的表情.\n"); break;
			case 27: command("chat* 月如用怀疑的眼光看了看"+who+"\n"); break;
			case 28: command("chat  我看未必.\n"); break;
			case 29: command("chat* 月如奇道：是吗？\n"); break;
			case 30: command("chat  老师来啦，"+who+"你还不赶快去？\n"); break;
			case 31: command("chat "+who+",你今天怎么又逃课?\n"); break;
			case 32: command("chat* 月如对所有在场的人表示感谢。\n"); break;
			case 33: command("chat* 月如嘻嘻地笑了几声.\n");break;
			case 34: command("chat "+who+"说得好!\n"); break;
			case 35: command("chat* 月如好奇地看着"+who+"\n"); break;
			case 36: command("chat "+who+",没想到你也会这样.\n"); break;
			case 37: command("chat* 月如白了"+who+"一眼,说:你无聊不无聊啊?"); break;
			case 38:  command("chat* 月如回头看了"+who+"一眼，没吭声。\n");break;
			case 39:command("chat* 月如摇了摇头，叹道：唉，真是世风日下，人心不古啊！\n"); break;
			case 40:command("chat 嗯 ... " + who + "说得好！\n"); break;
			case 41:command("chat* 月如无奈的耸了耸肩.\n");	break;
			case 42:command("chat 嗯，"+who+"是天底下最好的人了！\n"); break;
			case 43:command("chat* 月如把把头摇得跟拨浪鼓似的.\n");	break;
			case 44:command("chat 我对此表示怀疑.\n"); break;
			case 45: command("chat 我觉得最佳表情奖应该授予"+who+".\n"); break;
			case 46: command("chat* 月如轻轻拍了拍"+who+"的头.\n"); break;
			case 47: command("chat* 月如笑嘻嘻的看着"+who+"\n"); break;
			case 48: command("rumor "+this_object()->query("killed")+"被"+this_object()->query("killer")+"杀死了.\n"); break;
			case 49: command("rumor "+this_object()->query("killed")+"被"+this_object()->query("killer")+"杀死了.\n"); break;
			case 50: command("rumor "+this_object()->query("killed")+"被"+this_object()->query("killer")+"杀死了.\n"); break;
			case 51: command("chat 我觉得"+who+"的名字还不错.\n"); break;
			case 52: command("chat "+who+",你这个臭流氓!\n"); break;
			case 53: command("chat 嗯，"+who+"看来不是个好人.\n"); break;
			case 54: command("chat 哼！\n"); break;
			case 55: command("chat* 月如打了"+who+"一个耳光.\n"); break;
			case 56:command("chat* 月如给大家盈盈的福了一福.\n"); break; 
			case 57:command("chat 不要这样嘛!\n"); break;
			case 58:command("chat 要死啊你!"+who+"!\n"); break; 
			case 59:command("chat* 月如忽然大声说：打倒臭泥潭，打倒风！\n"); break;
			case 60:command("chat* 月如露出迷惑的表情.\n"); break;
			case 61:command("chat* 月如振臂高呼：“我们热爱侠客行，侠客行万岁！”\n");break;
			case 62:command("chat* 月如对大家摇摇头，叹道：“你们都太不要脸了。”\n");break;
			case 63:command("chat* 月如点了点头.\n");	break;
			case 64:command("chat* 月如哈哈大笑起来.\n"); break;
			case 65: command("chat 与其求人,不如求己!\n"); break;
			case 66:command("chat* 月如失望极了!\n");break;
			case 67:command("chat 无聊!\n");break;
			case 68:command("chat 是吗?\n"); break;
		        case 69:command("chat 变态！\n"); break;
			case 70:command("chat* 月如是个自恋狂。\n");break;
			case 71:command("chat 为什么？\n");break;
			case 72:command("chat 你烦不烦啊？\n");break;
			default:
	    if (random(10)<1) command("chat* 月如皱了皱眉，似乎想说什么。\n");
		else if (random(10)<1) command("chat* 月如嘻嘻地笑了几声.\n");
	    else if (random(10)<1) command("chat* 月如懒懒的伸了伸腰.\n");
				break;
		}
	}
}

void reset()
{
	delete("memory");
}
	
void init()
{
  object ob;
  
  ob=this_player();
 
  ::init();
  remove_call_out("greeting");
  call_out("greeting",1,ob);
  add_action("do_list","list");
  add_action("do_buy","buy");
}

void greeting(object ob)
{
  if(!ob||environment(ob)!=environment() )  return;
  switch(random(3)) {
   case 0 : say("月如说:欢迎光临全真派,不知这位"+RANK_D->query_respect(ob)+"是来拜师还是烧香?\n");
     break;
   case 1 : say("月如笑说:这位"+RANK_D->query_respect(ob)+"买些香吧,保你一生不被人pk\n");
     break;
   case 2 : say("月如告诉你:全真派可是很大的哦,我这儿有全真派的地图,买一张吧.\n");
     break;
}
}

int accept_fight(object me)
{
  command("say"+me->query("name")+", 你发了什么病,干什么要打我?\n");
  command("chat 小女子今天跟你拼了!\n");
  command("cry");
  kill_ob(me);
  return 1;
 } 

void attempt_apprentice(object ob)
{
  command("say 呦,你要拜我啊,师傅还没有让我收徒呢!\n");
  command("sorry"+ob->query("id"));
  return;
}


