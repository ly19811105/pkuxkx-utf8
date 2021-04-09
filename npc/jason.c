//Created by whuan@pkuxkx
//投名状任务：玩家加入土匪集团，如需取得信任，需要纳投名状
/*=======================================================
1. 取物（北侠现有物品，0-10信任时取得）
2. 杀人（北侠现有npc，以正派npc为主）
3. 寻物（系统分配一个物品到一个区域例如扬州，不指定地方，玩家可能要找遍全城方能找到，可能在地上，也可能在npc身上）
4. 劫色（系统分配一个美女，玩家需要去劫色，美女会有保镖随行）
5. 劫镖（系统分配一个镖，到指定地点等候1分钟，会出现镖队，有镖师随行）
=======================================================*/
inherit NPC;

#include <ansi.h>
#include "list.c"  //杀人和取物的list

int ask_job();  //投名状
int ask_join(); //加入

void create()
{
        set_name("残叶", ({ "can ye", "jason"}) ); //名字可以再改
        set("gender", "男性" );
        set("nickname", "赛诸葛");
        set("age", 31);
        set("long", "山寨的二当家，想要加 入需要问过他才行。\n");
        set("attitude", "peaceful");

        set("str", 29);
        set("dex", 26);
        set("con", 24);
        set("int", 22);
        set("per", 18);

        set("combat_exp", 20000000);
        set("score", 50000);

        set("shen", -100000);
        set("max_qi", 5000);
        set("max_jing", 2000);
        set("neili",2000);
        set("max_neili",3000);
        set("max_jingli", 1800);

        set_skill("blade",200);
        set_skill("dodge",200);
        set_skill("force",200);
        set_skill("parry",200);
        set_skill("strike",200);
        
        //特殊功夫暂定

        set("inquiry", ([
                "加入" : (: ask_join :),
                "join" : (: ask_join :),
                "投名状" : (: ask_job :),
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/city/obj/changjian")->wield();
        add_money("silver", 10);
}

int ask_join()
{
        object ob=this_player(), me=this_object();
        if ((int)ob->query("shen") > 1000)
        {
            message_vision(HIR"$N对$n大怒道：你也想加入？一看你就不是好人! \n"NOR,me,ob);
            return 1;
        }
        if ((int)ob->query("jiaofei/join")>0)
        {
            message_vision(HIR"$N怒道：$n你是来消遣老子的么，该干啥干啥去。滚！\n"NOR,me,ob);
            return 1;
        }        
        if ((int)ob->query("combat_exp") < 500000)
        {
            message_vision(HIR"$N用鄙夷的眼光看着$n道：就你这点功夫，打酱油都嫌不够! \n"NOR,me,ob);
            return 1;
        }

        message_vision(HIR"$N上下左右打量了$n几眼道：想在咋们这里混饭吃，可不容易。"+
        "为了显示你的诚意，你必须纳投名状。\n"NOR,me,ob);       		
        ob->set("jiaofei/join",1); //加入成功，设置标志
        //可以设置改变nick，job_title和title，暂时未加入
        return 1;
}

string ask_job()
{
        object ob=this_player(), me=this_object();
        int jobscore=(int)ob->query("jiaofei/xinren"); //信任度
        int jobtype;//任务类型，由jobscore决定
        mapping quest1,quest2;//取物和杀人的列表
        object where,baowu,meinv,biaoche,baobiao,biaoshi,tanzi,*inv;
        string msg,short;

        if (!(int)ob->query("jiaofei/join"))
        {
            message_vision(HIR"$N瞪大了眼睛喝道：无关人等，给我滚开！投名状是你能问的吗？\n"NOR,me,ob);
            return 1;
        } 
        if ((int)ob->query("jiaofei/on_job"))
        {
            message_vision(HIR"$N大声骂道：你是在消遣老子吗？上次的投名状你还没有完成呢！\n"NOR,me,ob);
            return 1;
        }        
        if ((int)ob->query("combat_exp") < 500000)
        {
            message_vision(HIR"$N用鄙夷的眼光看着$n道：就你这点功夫，打酱油都嫌不够! \n"NOR,me,ob);
            return 1;
        }
        //分配任务,可以随时调整
        if(jobscore>60)
        	jobtype=3+random(3);
        else if(jobscore>40)
        	jobtype=3+random(2);
        else 	
          jobtype=1+random(2);
        //根据分配的结果发放任务
        switch (jobtype)
        {
        	case 5: //劫镖任务
        		ob->set("jiaofei/jobtype",5);
        		where=TASK_D->random_place(); 
        		msg=TASK_D->place_belong(where);
        		short=where->query("short");
        		tanzi=new(__DIR__"tanzi");
        		tanzi->set("master",ob->query("id")); //在探子身上设置mark，3分钟内产生镖车，如果主人没赶到就会消失
        		if( !tanzi->move(where))
        			{
        				tanzi->move("/d/luoyang/center");
        				msg="洛阳";
        				short="中央广场";
        			}	
        		message_vision("$N对$n道：近期福威镖局生意极好，但是对寨中的孝敬不见增长，你去杀他们的威风。"
        		+"我已经派了一个探子名叫"+tanzi->name()+"在"+msg+"的"+short+"附近接应，你赶快过去吧。\n",me,ob);	
        		ob->set_temp("jiaofei/questmsg","你的投名状任务是劫回在"+msg+"出现的镖车。\n");
        		break;
        	case 4: //劫色任务
        		ob->set("jiaofei/jobtype",4);        		
        		where=TASK_D->random_place(); 
        		short=where->query("short");
        		msg=TASK_D->place_belong(where);
        		meinv=new(__DIR__"meinv");
        		meinv->set("master",ob->query("id")); //美女带个保镖玩10分钟，然后消失
        		if( !meinv->move(where))
        			{
        				tanzi->move("/d/suzhou/canlangting");
        				short="沧浪亭";
        				msg="苏州";
        			}	
        		message_vision("$N奸笑了几声对$n道：我们当家的想找一位压寨夫人。有探子探到最近经常有美女在"
        		+msg+"的"+where->query("short")+"附近游玩，你赶快去把她抢回来。\n",me,ob);	
        		ob->set_temp("jiaofei/questmsg","你的投名状任务是抢到在"+msg+"游玩的美女。\n");
        		break;      
        	case 3: //寻物任务
        		ob->set("jiaofei/jobtype",3);  
        		baowu=new(__DIR__"baowu");
        		baowu->set("owner",ob->query("id")); //宝物设置一个标记
        		baowu->set("no_get",1);
        		where=TASK_D->random_place(); 
						if(!TASK_D->place_belong(where))
							{
								baowu->move("/d/city/bingqiku");//藏在扬州的兵器库，嘿嘿
								msg="扬州";
							} 
						else
							{
								msg=TASK_D->place_belong(where);
								inv = all_inventory(where);
								baowu->move(where);
								if (sizeof(inv) > 0)
								if (random(2) && !baowu->move(inv[random(sizeof(inv))]))
								baowu->move(where);								        		     		
						  }
						 message_vision("$N拍了拍脑袋，说道：对了，前些日子有奸细混入寨中，偷走了一件宝物，经过"+
						 "寨中兄弟多方打探，探到宝物最近在"+msg+"出现，你去帮忙找回来吧。\n",me,ob);
						 message_vision("$N又补充道：盒子就不需要了，你把盒子里面的东西拿回来就可以了。"
						 +"$N在$n耳边告诉了开宝盒的方法。\n",me,ob); 	
						 ob->set_temp("jiaofei/questmsg","你的投名状任务是找回在"+msg+"出现的宝物。\n");
        		break;
        	case 2: //杀人任务
        		ob->set("jiaofei/jobtype",2);      
        		quest2=kill_quest[random(sizeof(kill_quest)]; 
        		ob->set("jiaofei/name",quest1[name]);
        		ob->set("jiaofei/id",quest1[id]);
        		message_vision("$N沉思了一下对$n说道：前些日子你表现不错，现在给你安排一点更难的任务，你去把"
        		+quest1[name]+"("+quest1[id]+")给我干掉，提他的脑袋来见我。\n",me,ob);    
        		ob->set_temp("jiaofei/questmsg","你的投名状任务是杀了"+quest2[name]+"。\n");    		  		
        		break;      
        	default: //取物任务
        	  ob->set("jiaofei/jobtype",1);   
        		quest1=find_quest[random(sizeof(find_quest)]; 
        		ob->set("jiaofei/name",quest1[name]);
        		ob->set("jiaofei/id",quest1[id]);
        		message_vision("$N想了一想对$n说道：目前尚不能对你委以重任，你就去给我找点"
        		+quest1[name]+"("+quest1[id]+")回来吧。记得要快哦。\n",me,ob);
        		ob->set_temp("jiaofei/questmsg","你的投名状任务是取回"+quest1[name]+"。\n");
        		break;   		  		
        }
        ob=>set("jiaofei/on_job",1); //设置一个已经在做任务的mark
        return 1;                	
}

int accept_object(object who, object ob)
{
				object me=this_object();
        if (!(int)ob->query("jiaofei/join"))
        {
            message_vision(HIR"$N疑惑道：我跟你非亲非故，你给我这个是干什么？\n"NOR,me,who);
            return 0;
        } 
        if (!(int)ob->query("jiaofei/on_job"))
        {
            message_vision(HIR"$N大声道：老子什么都不缺，谁要你的破烂 ！\n"NOR,me,who);
            return 0;
        }
        //收物和奖励的代码待添加
        return 1;
}
