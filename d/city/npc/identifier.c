// identifier.c
// 小宝套装掉落几率变低
#include <ansi.h>
inherit NPC;
#include <identify.h>

string ask_pu();
string RandomDigtal();
int do_answer(string arg);
int ask_tiaozhan();
int ask_cancel();
int ask_finish();
string ask_best();
string ask_special();

void create()
{
  set_name("百晓生", ({ "bai xiaosheng", "bai" }) );
  set("gender", "男性" );
  set("age", 48);
  set("long", 
    "百晓生乃是江湖奇书《江湖兵器谱》的作者，他对于兵器防具的研究天下闻名，他也正是依靠此艺为生。\n");
  set("str", 25);
  set("dex", 20);
  set("con", 17);
  set("int", 15);
  set("shen_type", -1);
  set("chat_chance", 3);
  set("chat_msg", ({
    "百晓生说道: 鉴定天下兵器防具，粗鉴一次二两黄金，细鉴一次十两黄金。\n",
  }) );
  set_skill("unarmed", 30);
  set_skill("dodge", 25);
  set_temp("apply/attack", 25);
  set_temp("apply/defense", 25);
  set("combat_exp", 2500);

  set("attitude", "peaceful");
 
  set("inquiry", ([
    "鉴定" : "不是我百晓生吹牛，兵器鉴定，我要自认第二，天下无人敢说第一！不信你随便那件东西来我看看！\n",
    "粗鉴" : "所谓粗鉴就是只鉴定兵器防具有哪些功能，而不细查其效力。\n",
    "细鉴" : "细鉴就是告诉你兵器防具的所有功能和其效力，甚是耗费精力，收费当然也高。\n",
    "鉴定之术" : "想学习鉴定之术可先从兵器谱上学习50级，之后就要通过我的挑战才能提高。\n",
    "兵器谱":(: ask_pu :),
    "挑战":(: ask_tiaozhan :),
	"纪录":(: ask_best :),
	"特技点数":(: ask_special :),
    "cancel":(: ask_cancel :),
    "finish":(: ask_finish :),
        ]) );
  set("pu_count",random(6)-4);

  setup();
}

void init()
{
        add_action("do_answer", "answer");
}

string ask_best()
{
	object me = this_player();
	if(me->query("baixiaosheng/bestrecord") > 0)
	{
		return sprintf("阁下的最好纪录是：%d分%d秒。\n",me->query("baixiaosheng/bestrecord")/60,me->query("baixiaosheng/bestrecord")%60);
	}
	return "阁下还没有完成过我的挑战。\n";
}

string ask_special()
{
	object me = this_player();
	if (me->query("baixiaosheng/bestrecord") > 0)
	{
	
		if(me->query("baixiaosheng/bestrecord") > 270)
		{
			return sprintf("阁下的最好纪录是：%d分%d秒。还不符合获得特技点数的要求\n",me->query("baixiaosheng/bestrecord")/60,me->query("baixiaosheng/bestrecord")%60);
		}
		else
		{
			if (me->query("baixiaosheng/special"))
			{
				return "你已经获取过此项奖励了，请不要再来问了\n";
			}
			me->set("baixiaosheng/special",1);
			me->add("special/levelup_point",1);
			CHANNEL_D->do_channel(this_object(), "jh", "小道消息："+me->query("name")+"因为快如闪电的百晓生任务速度，常人莫及，获得了一点特技升级点数奖励。\n",-1);
			return "恭喜阁下，取得了一点特技升级点数。\n";
		}
	}
	return "你都没有任何记录，来浑水摸鱼啊!\n";
}


string ask_pu()
{
        object ob,me;
        me = this_player();
        if(!me->query("ludingshan"))
                return "你还没解开鹿鼎山的秘密，兵器谱对阁下无用！";
  
        if (query("pu_count") < 1)
        return "你来晚了，兵器谱已经被有缘人取走了。";
        add("pu_count", -1);
        ob = new("clone/book/bingqipu");
        ob->move(this_player());
        return RANK_D->query_respect(this_player()) + "武功盖世，此兵器谱就赠与你吧!";
}

//显示物品的鉴定级别
//所有鉴定级别定义采用标准定义，具体见IL_系列define，不管内部如何定义，外部统一采用该返回值定义
varargs int get_idflevel(object item)
{
  object ob=this_object(),me;
  
  me=item->query_temp("owner");
  
  if ( !objectp(me) )
    return IL_INIT;
  
  if (me->query_temp("id_price") >= 100000)
  {
    me->add_temp("id_price",-100000);         
    message_vision("百晓生说道：这位" + RANK_D->query_respect(me) + "出手如此阔绰，在下定会施展平生之所学为你仔细鉴定此宝！。\n",me);
    return IL_FULL;
  } else if (me->query_temp("id_price") >= 20000)
  {
    me->add_temp("id_price",-20000);         
    message_vision("百晓生漫不经心地说道：哦，且让我看看这是个什么东西。\n",me);
    return IL_SIMPLE;
  } else
  {
    message_vision("百晓生愕然道：我平白无故为什么要为你鉴定？让我鉴定一次至少二两黄金呢！你兹到不？\n",me);
    return IL_INIT;
  }
}

int destletter(object ob)
{
  if(ob)
  destruct(ob);
  return 1;
}

int accept_object(object me, object ob)
{
    int source;
    string temp;
    source = 0;
    
    if( ob->query("letterback")==7 && ob->query("owner")==me->query("id"))
    {
      message_vision("$N接过$n手里的家信，感动的热泪盈眶：这是老婆写给我的信，我，我不会亏待你的！",this_object(),me);
      me->set_temp("extrajob/bxs",1);
      call_out("destletter",1,ob);
      return 1;
    }
    
    if (ob->query("money_id"))
    {
      me->add_temp("id_price",ob->value());
      message_vision("百晓生满脸堆笑：不知这位" + RANK_D->query_respect(me) + "有什么需要在下鉴定的，尽管拿给我瞧瞧。\n",me);
      return 1;
    }
    
    if( ob->is_identify()!=IDF_EQUIP )
    {
      message_vision("百晓生愤然作色道：这种东西还需要鉴定么？\n",me);
      return 0;
    }
    
    ob->set_temp("owner", me);
    this_object()->start_busy(2);
    
    ob->set_idflevel(this_object());
    source=ob->get_idflevel();

    if ( source==IL_INIT )
      return 0;
    else if (source == IL_SIMPLE)
      message_vision("百晓生捧着$n上上下下仔仔细细的打量了一遍。\n",me,ob);
    else 
      message_vision("百晓生捧着$n上上下下仔仔细细的打量了一遍，又掏出怀中的兵器谱反复对照一番。\n",me,ob);
    
    temp = "百晓生告诉你：\n";
    temp+=ob->identify(source);

    tell_object(me,temp);
    call_out("giveback",0,ob,me);
    return 1;
}  

int giveback(object ob,object me)
{
    ob->move(me);
    message_vision("百晓生把" + ob->name() + "还给了" + me->name() + "。\n",me);
    return 1;
}

int ask_tiaozhan()
{
  
      object me = this_player();
      object ob=this_object();
      object where;
      string code;
      int ydexp, mrexp, xfexp, hbexp;

      ydexp = ((int)me->query("yidao/times"));
      mrexp = ((int)me->query("exp/murong"));
      xfexp = ((int)me->query("exp/xiaofeng"));
      hbexp = ((int)me->query("exp/hubiao"));
      
      if ( me->query("combat_exp") < 3000000 )
      {
         message_vision("$N笑道：你经验太低了，根本完成不了我的挑战。\n",ob);
         return 1;
      }
      if (time()-me->query_temp("baixiaosheng/codetime")<120)
      {
         message_vision("$N笑道：你不是刚要求过验证？又来了？等会吧，把机会留给别人。\n",ob);
         return 1;
      }
      if (me->query("baixiaosheng/tiaozhan"))
      {
         message_vision("$N说道：挑战已经开始了，还不快去做？\n",ob);
         return 1;
      }
      
      if (me->query("yidao/on_job"))
      {
         message_vision("$N说道：胡一刀大侠交给你的任务完成了吗？搞定再说吧。\n",ob);
         return 1;
      }
      
      if (me->query("in_dart"))
      {
         message_vision("$N说道：林镇南大侠交给你的任务完成了吗？搞定再说吧。\n",ob);
         return 1;
      }
      
      if (me->query("murong/yuxi"))
      {
         message_vision("$N说道：慕容复大侠交给你的任务完成了吗？搞定再说吧。\n",ob);
         return 1;
      }
      
      if(me->query("xiaofeng/on_job"))
      {
         message_vision("$N说道：萧峰大侠交给你的任务完成了吗？搞定再说吧。\n",ob);
         return 1;
      }
		if(me->query("hansz/on_job"))
	{
         message_vision("$N说道：韩蕲王交给你的任务完成了吗？搞定再说吧。\n",ob);
         return 1;
	}
      if(!wizardp(me) && time() - me->query("baixiaosheng/tz_time") < 720)
      {
         message_vision("$N说道：歇会，等等再要吧。\n",ob);
         return 1;
      }

      if (me->query("antirobot/deactivity") > 2) 
         message("vision",HIR"百晓生瞪圆了眼睛对你说到：“又他奶奶的是你！我看你是机器人吧。”\n"NOR,me);
         
      me->set("baixiaosheng/tz_time",time());
      if (me->query("env/bxs_old_pattern"))
      {
         me->set_temp("baixiaosheng/randomcode",RandomDigtal());
         printf("%s","/d/luoyang/npc/display.c"->Display((string)this_player()->query_temp("baixiaosheng/randomcode")));
         printf("%s","\n");  

         command("say 请在30秒内回答(answer/huifu)出口令的内容。");
         command("say 如果没看清，请ask bai about 挑战 再问一次。");
         return 1;
      }

      while (!objectp(where) || 
          !where->isroom()||
          TASK_D->place_belong(where)=="不明区域"||
          base_name(where) == "/adm/daemons/taskd"||
          where->query("no_fullme_scan"))
      {where=TASK_D->random_place();}

      code=where->query("short");
      code=COLOR_D->uncolor(code);
      me->set_temp("baixiaosheng/randomcode",code);
      me->set_temp("baixiaosheng/codetime",time());
      ANTIROBOT_D->mxpantirobot_ex(me,code);
         
      command("say 请在30秒内回答(answer/huifu)出口令的内容。");
      command("say 如果没看清，请ask bai about 挑战 再问一次。");
      return 1;
}

string RandomDigtal()
{
   string *ABC=({"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"});
   string *DIG=({"0","1","2","3","4","5","6","7","8","9"});
   string MyCode;
   MyCode=ABC[random(sizeof(ABC))]+ABC[random(sizeof(ABC))]+DIG[random(sizeof(DIG))]+DIG[random(sizeof(DIG))];
   return MyCode;
}

int do_answer(string arg)
{
  object me=this_player();
  object ob=this_object();
  int ydexp, mrexp, xfexp, hbexp,hszexp;
  
  ydexp = ((int)me->query("yidao/times"));
  mrexp = ((int)me->query("exp/murong"));
  xfexp = ((int)me->query("exp/xiaofeng"));
  hbexp = ((int)me->query("exp/hubiao"));
	hszexp=(int)me->query("exp/hansz");
  if ((int)me->query_temp("baixiaosheng/randomcode")==0)
         return 0;

  if (me->query("yidao/on_job"))
  {
         message_vision("$N说道：胡一刀大侠交给你的任务完成了吗？搞定再answer吧。\n",ob);
         return 1;
  }
      
  if (me->query("in_dart"))
  {
         message_vision("$N说道：林镇南大侠交给你的任务完成了吗？搞定再answer吧。\n",ob);
         return 1;
  }
      
  if (me->query("murong/yuxi"))
  {
         message_vision("$N说道：慕容复大侠交给你的任务完成了吗？搞定再answer吧。\n",ob);
         return 1;
  }
      
  if(me->query("xiaofeng/on_job"))
  {
         message_vision("$N说道：萧峰大侠交给你的任务完成了吗？搞定再answer吧。\n",ob);
         return 1;
  }
  if(me->query("hansz/on_job"))
  {
         message_vision("$N说道：韩蕲王交给你的任务完成了吗？搞定再answer吧。\n",ob);
         return 1;
  }
  message("vision",me->name()+"回答道：“是"HIR+arg+NOR"么?”\n",environment(me));
  if (arg==(string)me->query_temp("baixiaosheng/randomcode") )
  {
         write("百晓生微微颔首道：“口令无误，请接受挑战吧，"+BLINK+HIG+"十二"+NOR+"分钟之内完成慕容，萧峰或者韩蕲王，胡一刀，护镖任务各一次，现在开始，马上行动。”\n");
         me->delete_temp("baixiaosheng/randomcode");
         me->set("baixiaosheng/tiaozhan",1);
         ANTIROBOT_D->same_as_fullme(me);
         me->set("baixiaosheng/yd_exp",ydexp);
         me->set("baixiaosheng/xf_exp",xfexp);
         me->set("baixiaosheng/mr_exp",mrexp);
         me->set("baixiaosheng/hb_exp",hbexp);
		 me->set("baixiaosheng/hsz_exp",hszexp);
         me->delete("baixiaosheng/hb_time");          //删除领护镖任务次数记录，为以后预留的护镖和百晓生衔接作准备。
         return 1;
  }
  else
         write("百晓生摇摇头说道：“不对！”\n"); 
  return 1;
}

int dash()
{
  log_file("wiz/bxs_test_time",sprintf("%s\n","分割"));
}

int ask_cancel()
{
      object me = this_player();
      object ob=this_object();
      
      if (!me->query("baixiaosheng/tiaozhan"))
      {
         message_vision("$N说道：你啥也没要，取消个屁呀！\n",ob);
         return 1;
      }
      
      if ( time() - me->query("baixiaosheng/tz_time")<300 )
      {
         message_vision("$N说道：刚领了任务就想取消啊？\n",ob);
         return 1;
      }
        
      message_vision("$N说道：完不成就算了，对你来说，是有点难度。\n",ob);
      log_file("wiz/bxs_test_time",sprintf("%s%s\n",me->query("id"),"失败"));
      me->delete("baixiaosheng/tiaozhan");
      return 1;   
}

int ask_finish()
{
      object me = this_player();
      object ob=this_object();
      object obj,baoshi2,material;
      string gem,msg;
      int quest_time;
      int sk,i,num,nrn;
      sk = ((int)me->query_skill("identification",1));
      
      if (!me->query("baixiaosheng/tiaozhan"))
      {
         message_vision("$N说道：你问我这个问题，心里不惭愧吗？\n",ob);
         return 1;
      } 
      
      if( me->query("yidao/times") <= me->query("baixiaosheng/yd_exp"))
      {
         message_vision("$N说道：你还没完成胡一刀任务呢，抓紧时间啊。\n",ob);
         return 1;
      }
      
      if( me->query("exp/murong") <= me->query("baixiaosheng/mr_exp"))
      {
         message_vision("$N说道：你还没完成慕容任务呢，抓紧时间啊。\n",ob);
         return 1;
      }
      
      if( me->query("exp/xiaofeng") <= me->query("baixiaosheng/xf_exp")&&me->query("exp/hansz") <= me->query("baixiaosheng/hsz_exp"))
      {
         message_vision("$N说道：你还没完成萧峰或者韩蕲王的任务呢，抓紧时间啊。\n",ob);
         return 1;
      }
      
      if( me->query("exp/hubiao") <= me->query("baixiaosheng/hb_exp"))
      {
         message_vision("$N说道：你还没完成护镖任务呢，抓紧时间啊。\n",ob);
         return 1;
      }
	   quest_time = time() - me->query("baixiaosheng/tz_time");
      log_file("wiz/bxs_test_time",sprintf("%s%d\n",me->query("id"),quest_time));
      if(quest_time > 750+random(30))
      {
         if(quest_time <1080)
         {
            me->delete("baixiaosheng/tiaozhan");
            if ( sk<500 )
            {
               message_vision("$N说道：很可惜，你已经超时了，不过还不算太离谱，宝石没有了，我先教你点鉴定之术吧。\n",ob);
               write(HIC"\n你的「鉴定之术」进步了！\n"NOR);
               me->set_skill("identification",sk+1);
            }
            else 
               message_vision("$N说道：很可惜，你已经超时了，不过还不算太离谱，宝石没有了。\n",ob);
            return 1;
         }
         else if (quest_time <1800 )
         {
            me->delete("baixiaosheng/tiaozhan");
            if ( sk<75 )
            {
               message_vision("$N说道：很可惜，你已经超时太多了，我只能教你一点入门的鉴定之术。\n",ob);
               write(HIC"\n你的「鉴定之术」进步了！\n"NOR);
               me->improve_skill("identification",1000);
            }
            else 
               message_vision("$N说道：很可惜，你已经超时太多了，宝石没有了。\n",ob);
            return 1;
         }
         message_vision("$N说道：很可惜，你已经超时了，重新挑战吧。\n",ob);
         me->delete("baixiaosheng/tiaozhan");
         return 1;
      }
      
			if(!me->query("baixiaosheng/bestrecord") || me->query("baixiaosheng/bestrecord") > quest_time)
			{
				me->set("baixiaosheng/bestrecord",quest_time);
				message_vision(sprintf("$N说道：恭喜你，你打破了挑战的记录。你的最快成绩是 %d分%d秒。\n",
					(quest_time)/60,
					(quest_time)%60),ob);
			}
      obj = new("/obj/gem/gem");
        
   /*   i = random(20);
      if (i < 3) gem = "yan";
      else if (i < 6) gem = "mu";
      else if (i < 9) gem = "sui";
      else if (i < 12) gem = "jin";
      else if (i < 15) gem = "bing";
      else if (i < 16) gem = "gu";
      else if (i < 17) gem = "yu";
      else if (i < 18) gem = "jiao";
      else gem = "jia";  */
	  
// 修改百晓生任务奖励，减少五行宝石，增加禽兽宝石。 by lordstar 2017/10/16
	if (random(100)>=45)  // 55%概率禽兽 
	{
		i = random(4);
		if (i == 3) gem = "gu";
		else if (i == 2) gem = "yu";
		else if (i == 1) gem = "jia";
		else gem = "jiao";  
	}
	else 
	{
		i = random(5);
		if (i == 4) gem = "yan";
		else if (i == 3) gem = "mu";
		else if (i == 2) gem = "sui";
		else if (i == 1) gem = "jin";
		else gem = "bing";
	}
      
      num = 10000 - random(554);   
      obj->set_level(num,num,gem);    
      obj->move(this_player());

      write("\n百晓生给你一颗"+obj->name()+"！\n");  
      CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "在百晓生任务中获得一颗"+obj->name()+"!");
      msg = this_player()->name()+"在百晓生任务中得到一"+obj->query("unit")+obj->name()
               +"[等级："+obj->query("level")+"]。";   
  nrn=random(10000);
  if (nrn>9950)
  {
	if (nrn>9996)
		{
			baoshi2= new("obj/taozhuang/xiaobao/boots");
			baoshi2->set("forge/max",1);
		}
	else if (nrn>9990) 
		{
			baoshi2= new("obj/taozhuang/xiaobao/boots");
		}
	else if (nrn>9980) 
		{
			baoshi2= new("obj/taozhuang/xiaobao/cloth");
			baoshi2->set("forge/max",1);
		}
	else if (nrn>9970) 
		{
			baoshi2= new("obj/taozhuang/xiaobao/dagger");
			baoshi2->set("forge/max",1);
		}
	else if (nrn>9960) baoshi2= new("obj/taozhuang/xiaobao/cloth");
	else if (nrn>9950) baoshi2= new("obj/taozhuang/xiaobao/dagger");
	baoshi2->move(me);
    CHANNEL_D->do_channel(this_object(), "rw", me->query("name")+"完成百晓生任务，获得"+baoshi2->query("name")+"一件。");
  }
      MONITOR_D->report_system_msg(msg); 
      log_file("static/bxs",sprintf("%s:%s(%s)百晓生任务中获得一颗"+obj->name()+"，时间%d秒！\n",  
      ctime(time()),me->query("name"),me->query("id"),quest_time)); 
      me->delete("baixiaosheng/tiaozhan");
      if ( sk<3000 )
      {
        message_vision("$N说道：大侠果然身手不凡，过挑战一次，我奖励你颗宝石，并教你一些鉴定技术吧。\n",ob);
        write(HIC"\n你的「鉴定之术」进步了！\n"NOR);  
        me->set_skill("identification",sk+2);
      }
      else
        message_vision("$N说道：大侠果然身手不凡，过挑战一次，我奖励你颗宝石。\n",ob);
      if (quest_time<480&&me->query_temp("tbyj_obtain/start"))
      {
		  me->set_temp("tbyj_obtain/success",1);
		  command("whisper "+me->query("id")+" 太白阴经估计你要到手了。");
      }
	  if (quest_time < 450 && quest_time > 360)
	  {
		  if (random(5)==0)
		  {
		obj = new("/obj/remedy/drug/daliwangou.c");
		obj->move(this_player());
		write("\n百晓生给了你一颗"+obj->name()+"！\n");  
		CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "在百晓生任务中狗运亨通，获得了一颗"+obj->name()+"!");
    log_file("static/bxs",sprintf("%s:%s(%s)百晓生任务中获得一颗"+obj->name()+"！\n",  
      ctime(time()),me->query("name"),me->query("id")));  
		  }

	  }
	  else if (quest_time < 360 && quest_time > 300)
	  {
		  if (random(4)==0)
		  {
		obj = new("/obj/remedy/drug/daliwanlu.c");
		obj->move(this_player());
		write("\n百晓生给了你一颗"+obj->name()+"！\n");  
		CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "在百晓生任务中啾啾鹿鸣，获得了一颗"+obj->name()+"!");
   log_file("static/bxs",sprintf("%s:%s(%s)百晓生任务中获得一颗"+obj->name()+"！\n",  
      ctime(time()),me->query("name"),me->query("id")));  
 

		  }
	  }
	  else if (quest_time < 300 && quest_time > 240)
	  {
		 if (random(3)==0)
		 {
		obj = new("/obj/remedy/drug/daliwanhu.c");
		obj->move(this_player());
		write("\n百晓生给了你一颗"+obj->name()+"！\n");  
		CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "在百晓生任务中虎虎生威，获得了一颗"+obj->name()+"!");
    log_file("static/bxs",sprintf("%s:%s(%s)百晓生任务中获得一颗"+obj->name()+"！\n",  
      ctime(time()),me->query("name"),me->query("id")));  

		 }
	  }
	  else if (quest_time < 240)
	  {
		 if (random(2)==0)
		 {
		obj = new("/obj/remedy/drug/daliwanhu.c");
		obj->move(this_player());
		write("\n百晓生给了你一颗"+obj->name()+"！\n");  
		CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "在百晓生任务中虎虎生威，获得了一颗"+obj->name()+"!");
    log_file("static/bxs",sprintf("%s:%s(%s)百晓生任务中获得一颗"+obj->name()+"！\n",  
      ctime(time()),me->query("name"),me->query("id")));  

		 }

	  }
	  if ((quest_time < (int)(me->query("baixiaosheng/bestrecord"))) && (me->query("baixiaosheng/bestrecord") < 270))
	  {
		obj = new("/obj/gem/gem");
		obj->set_level(num,num,gem);    
		obj->move(this_player());
        message_vision("$N说道：大侠果然身手敏捷，快如闪电，值得鼓励！\n",ob);
		 write("\n百晓生又给你一颗"+obj->name()+"！\n");  
		CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "在百晓生任务中拼死拼活又获得一颗"+obj->name()+"!");
		msg = this_player()->name()+"在百晓生任务中又得到一"+obj->query("unit")+obj->name()
               +"[等级："+obj->query("level")+"]。";  
     log_file("static/bxs",sprintf("%s:%s(%s)百晓生任务中获得一颗"+obj->name()+"！\n",  
      ctime(time()),me->query("name"),me->query("id")));  
 		
		obj = new("/obj/remedy/drug/daliwanhu.c");
		obj->move(this_player());
		write("\n百晓生给了你一颗"+obj->name()+"！\n");  
		CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "在百晓生任务中虎虎生威，获得了一颗"+obj->name()+"!");
      log_file("static/bxs",sprintf("%s:%s(%s)百晓生任务中获得一颗"+obj->name()+"！\n",  
      ctime(time()),me->query("name"),me->query("id")));  

  
	  }
//增加无常造化丹药材掉落。by lordstar 20171102
	if (!me->query("hsz_auto"))
	{
		nrn = 0;
		if (quest_time<270)
		{
			if (random(10000)>9900) nrn = 1;
		}
		else if (quest_time<300)
		{
			if (random(10000)>9940) nrn = 1;
		}
		else if (quest_time<480)
		{
			if (random(10000)>9980) nrn = 1;
		}
		if (nrn>0)
		{			
			material=new("/obj/remedy/drug/wuchang-material");
			if (objectp(material))
			{
				material->set("owner", me->query("id"));
				material->move(me);
				tell_object(me, "百晓生又送你一份罕见的珍贵药材作为额外馈赠。\n");
			}
		}
	}
  	  
      me->add("newjobs/completed/bxs",1);
      if (!me->query("biography/jobs/bxs"))
      {
        me->set("biography/jobs/bxs",time());//个人传记记录bxs时间ZINE
      }
	  me->set("jobs/bxs/last_time",time());
      return 1;      
}