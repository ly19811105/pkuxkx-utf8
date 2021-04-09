//金庸，负责出师和发放特技   
//by kiden             

inherit NPC;   
#include <ansi.h>         

int accept_object(object who, object ob);   
string ask_chushi();            
int do_confirm();      
string ask_jienan();     
string random_special(object who);  
int ask_special();    
string *specialsk=({
    "corporeity","ironskin","health","energy","chainless","sociability","greedy","agile",
    "might","spirituality","athanasy","intellect","constitution","perceive","lucky",   
    });      
void create()         
{
	         set_name("金庸", ({ "jin yong","jin" }) );    
           set("gender", "男性");   
           set("age", 65);           
           set("per",40);            
           set("long", "金庸金大侠，高手中的高手，偶像中的偶像。\n"); 
           set("combat_exp", 2000000000);     
           set("shen_type", 0);      
           set("attitude", "friendly");       
           set("apply/attack",  30000);       
           set("apply/defense", 30000);       
           set("inquiry",([          
           "出师"       : (:ask_chushi:),     
           "special"    : (:ask_special:),  
           "特技"       : (:ask_special:),  
           "劫难"       : (:ask_jienan:),     
           "金庸全集"   : "我把他遗留在北侠了，你能帮我找回来么？",
           "飞狐外传"   : "你得找胡斐要一下。",   
           "雪山飞狐"   : "你得找胡斐要一下。",
           "连城诀"     : "这个得找狄云。",
           "天龙八部"   : "去灵鹫宫找找虚竹子吧。",
           "射雕英雄传" : "郭大侠现在在襄阳，这本书他保管着呢。",
           "白马啸西风" : "你得先找到鸳鸯刀才行。",
           "鹿鼎记"     : "在韦小宝那里。",
           "笑傲江湖"   : "忘记了，不是在令狐冲那里就是在任盈盈那里。",
           "书剑恩仇录" : "找霍青桐或者陈家洛去吧。",
           "神雕侠侣"   : "自然得找杨过",
           "侠客行"     : "找石中玉，他现在在侠客岛。",
           "倚天屠龙记" : "张无忌应该知道。",
           "碧血剑"     : "袁承志去了琉球岛，你或许可以找一下独臂神尼，她也许知道。",
           "鸳鸯刀"     : "听说长白山有个落第秀才，他知道一些有关鸳鸯刀的消息。",
           "越女剑"     : "听说在苏州城东。",			      
           ]));  
           set_skill("unarmed", 2000);        
           set_skill("parry", 2000); 
           set_skill("dodge", 2000); 
           setup();    
           carry_object("/clone/misc/cloth")->wear();             
}             
void init()   
{             
           add_action("do_confirm", "confirm");     
}             

string ask_chushi() 
{             
          object me=this_player(); 
          if ((int)me->query("combat_exp") < 50000000)   
               {     
                tell_object(me, "你经验太低，怎么出师啊？\n");      
                return "你的经验太低了！";  
               }      
          if ((int)me->query("reborn/all")<1)     
               {     
                command("pat "+me->query("id")); 
                command("addoil "+me->query("id"));            
                return "你需要接收考验，历经劫难，方可出师！"; 
                }   
          if ((int)me->query("reborn/chushi")>=1 || (int)me->query("chushi/done")>=1) 
               {     
               command("hammer "+me->query("id"));            
               return "你不是出过师了么？一人一生只能出师一次！";   
               }   
               me->set_temp("reborn_chushi",1); 
               command("consider");    
               return "你真的确认要出师吗？请确认（confirm）！";    
}             
int do_confirm()    
{             
          object me=this_player();
          if ((int)me->query_temp("reborn_chushi")<1)          
          {   
             return 0; 
          }   
          me->set("reborn/chushi",1);
          me->set("chushi/done",1);
          me->delete("class");    
          me->set("chushi/last_family",me->query("family/family_name"));        
          me->delete("family");   
          me->delete_temp("reborn_chushi");
          me->set("title","无门无派，世外高人"); 
          me->set("score",0);     
          message("chat",HIY+"【闲聊】金庸(Jin yong):"+this_player()->name()+      
           "勤修苦练，经受劫难和考验，成功出师！\n"NOR,users());
         
         log_file("static/reborn",sprintf("%s(%s) 于%s出师，当前经验(%d)，潜能(%d)！\n",
         me->query("name"),me->query("id"),ctime(time()),me->query("combat_exp"),me->query("pontential"))); 
         return 1; 
}             
string ask_jienan() 
{  
      	 int i;           
         object me=this_player();
         object* inv = deep_inventory(me);
         if ((int)me->query("combat_exp") < 50000000)   
              {     
               tell_object(me, "你经验太低，去了也白搭啊！\n");      
               return "你的经验太低了。";  
              }       
         if ((int)me->query("reborn/all")>=1)    
              {     
                command("hammer "+me->query("id"));    
                return "你不是经历过劫难了么？"; 
              }     
         if ((int)me->query("reborn/chushi")>=1 || (int)me->query("chushi")>=1 )          
              {     
                command("hammer "+me->query("id"));    
                return "你无需经历劫难了！";     
              }
         for(i=sizeof(inv)-1; i>=0; i--)
                if(inv[i]->is_character()) return "你身上背的是什么啊？放下来先！";  
         if (query("on_chushi")>0 && (string)query("chushi_id")!=me->query("id"))
         	      return "对不起，有人正在出师，你等一段时间吧。";          	   
         if ((int)me->query("reborn/jinyong_all")<1)   
              {     
                command("consider");       
                command("look "+me->query("id"));
                return "在接受考验之前，你要帮我找回《金庸全集》。"; 
              }     
         else  
              {     
                command("nod");   
                message("vision","金庸在你眼前一拂袖，你发现自己来到了一个新的地方！ \n",me);
                set("on_chushi",1);
                set("chushi_id",me->query("id")); 
                me->add("combat_exp",-300000);          
                me->move("/d/reborn/r1");  
                return "你帮我找回了金庸全集，我就送你去接受考验和劫难。";        
              }     
}             

int accept_object(object me, object ob)    
{             
        object book;
        if( !me || environment(me) != environment() ) return 0;      
        if ( !objectp(ob) ) return 0;   
        if ( !present(ob, me) ) return 0;        
        if ((int)me->query("combat_exp") < 50000000)   
              {     
               tell_object(me, "你经验太低，找了也白搭啊！\n");      
               return 0;  
              }     
        if ((int)me->query("reborn/jinyong_all") >= 1 || (int)me->query("reborn/all")>=1)
              {     
               tell_object(me, "谢谢，我已经找到了！\n");            
               return 0;  
              }     
        if ((int)me->query("reborn/chushi") >= 1 || (int)me->query("chushi")>=1)         
              {     
              tell_object(me, "谢谢，我已经找到了！\n");            
              return 0;  
             }     
        if ( (string)ob->query("id") == "feihu waizhuan")           
             {     
              me->set_temp("reborn/jinyong1", 1);     
             }     
        if ( (string)ob->query("id") == "xueshan feihu")            
             {     
              me->set_temp("reborn/jinyong2", 1);     
             }     
        if ( (string)ob->query("id") == "liancheng jue")            
             {     
              me->set_temp("reborn/jinyong3", 1);     
             }     
        if ( (string)ob->query("id") == "tianlong babu")            
             {     
              me->set_temp("reborn/jinyong4", 1);     
             }     
        if ( (string)ob->query("id") == "shediaoyingxiong zhuan")   
             {     
              me->set_temp("reborn/jinyong5", 1);     
             }     
        if ( (string)ob->query("id") == "baimaxiao xifeng")         
             {     
              me->set_temp("reborn/jinyong6", 1);     
             }     
        if ( (string)ob->query("id") == "luding ji")  
             {     
              me->set_temp("reborn/jinyong7", 1);     
             }     
        if ( (string)ob->query("id") == "xiaoao jianghu")           
             {     
              me->set_temp("reborn/jinyong8", 1);     
             }     
        if ( (string)ob->query("id") == "shujianechou lu")          
             {     
              me->set_temp("reborn/jinyong9", 1);     
             }     
        if ( (string)ob->query("id") == "shendiao xialv")           
             {     
              me->set_temp("reborn/jinyong10", 1);    
             }     
        if ( (string)ob->query("id") == "xiake xing") 
             {     
              me->set_temp("reborn/jinyong11", 1);    
             }     
        if ( (string)ob->query("id") == "yitiantulong ji")          
             {     
              me->set_temp("reborn/jinyong12", 1);    
             }     
        if ( (string)ob->query("id") == "bixue jian") 
             {     
              me->set_temp("reborn/jinyong13", 1);    
             }     
        if ( (string)ob->query("id") == "yuanyang dao")             
             {     
              me->set_temp("reborn/jinyong14", 1);    
             }     
        if ( (string)ob->query("id") == "yuenv jian") 
             {     
              me->set_temp("reborn/jinyong15", 1);    
             }     
        call_out("destroy", 1, ob);    
        if (me->query_temp("reborn/jinyong1")  &&     
                me->query_temp("reborn/jinyong2")  && 
                me->query_temp("reborn/jinyong3")  && 
                me->query_temp("reborn/jinyong4")  && 
                me->query_temp("reborn/jinyong5")  && 
                me->query_temp("reborn/jinyong6")  && 
                me->query_temp("reborn/jinyong7")  && 
                me->query_temp("reborn/jinyong8")  && 
                me->query_temp("reborn/jinyong9")  && 
                me->query_temp("reborn/jinyong10") && 
                me->query_temp("reborn/jinyong11") && 
                me->query_temp("reborn/jinyong12") && 
                me->query_temp("reborn/jinyong13") && 
                me->query_temp("reborn/jinyong14") && 
                me->query_temp("reborn/jinyong15")   )
               {   
                me->delete_temp("reborn");      
                me->set("reborn/jinyong_all",1);
                tell_object(me, "谢谢你帮我找回金庸全集！\n");      
               }   
        else       
                tell_object(me, RANK_D->query_respect(me) + "快把剩下的找齐吧。\n");    
                call_out("destroy",1,ob);       
                  return 1;            
}             


void destroy(object ob)           
{             
        destruct(ob);             
        return;     
}             

string random_special(object who)
{
        string msg;
        for(int i=0;i<10;i++)
        {
         msg=specialsk[random(sizeof(specialsk))];
         if(who->query("special_skill/"+msg)) continue;
         break;
        } 
        return msg;    
}

int ask_special()
{
	      string spe;//特技
	      object me=this_player();
	      if (me->query("combat_exp")<1000000){
	      	command("say 你的经验不够，还不够资格使用特殊技能。");
	      	command("addoil "+me->query("id"));
	      	return 1;
	      }
	      if (me->query("combat_exp")>=1000000 && !me->query("asked_special1")){
	      		spe=random_special(me);
	      		me->set("special_skill/"+spe,1);
	      		me->set("asked_special1",1);
	      		command("chat 恭喜"+me->query("name")+"获得一项特技："+spe+"。");
	      		command("chat* gongxi "+me->query("id"));
	      		return 1;
	      }
	      if (me->query("combat_exp")>=10000000 && !me->query("asked_special2")){
	      		spe=random_special(me);
	      		me->set("special_skill/"+spe,1);
	      		me->set("asked_special2",1);
	      		command("chat 恭喜"+me->query("name")+"又获得一项特技："+spe+"。");
	      		command("chat* addoil "+me->query("id"));
	      		return 1;
	      }
	      if (me->query("combat_exp")>=50000000 && me->query("reborn/all") 
	      	&& !me->query("asked_special3")){
	      		spe=random_special(me);
	      		me->set("special_skill/"+spe,1);
	      		me->set("asked_special3",1);
	      		command("chat 恭喜"+me->query("name")+"再获得一项特技："+spe+"。");
	      		command("chat* admire "+me->query("id"));
	      		return 1;
	      }
	     command("hmm");
	     command("say 你现在不能要特技。");
	     return 1;
} 
