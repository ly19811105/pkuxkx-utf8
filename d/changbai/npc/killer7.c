// File         : killer.c
// Created By   : whuan@pkuxkx, 2007-07-02
#include <ansi.h>
inherit QUEST_NPC;
#include <random_name.h>
int ask_rumors();
int ask_fight();
int do_copy(object me);
varargs void wield_weapon(string weapon);
void die();
void create()
{
        set_name(get_rndname(), ({get_rndid(), }));
        set("job_title","盗 宝 人");
        set("nickname",YEL"伏地龙"NOR);
        set("gender", "男性" );
        set("age", 22+random(22));
        set("combat_exp", 10000000);
        set("attitude", "heroism");
        add("inquiry", ([
                "name" : "大爷我有要事在身，别烦我！",
                "here" : "大爷我有要事在身，别烦我！",
                "rumors" : (:ask_rumors:),
                "fight" : (:ask_fight:),
        ]));
        set("uni_target", 1);
        set("jiali", 50);
        setup();
        carry_object("/clone/armor/bianfuxuejia")->wear();
        call_out("do_leave", 1800);
}

void delete_init_num(object me)
{
        me->delete("init_num");
        return;
}

void init()
{
        object stage,env,where;
        object me=this_player();
        string exit_place;
        if (this_object()->query("uni_target")==me)
        {
            switch (random(11-this_object()->query("hyd/step")))
                {
                    case 0:
                        break;
                    case 1:
                        message_vision("$N看见$n，阴笑一声：天堂有路你不走，地狱无门你来投！\n",this_object(), me);
                        kill_ob(me);
                        break;
                    default:
                        break;
                }
        }        
}

void do_leave()
{
        if(!this_object())
                return;
        message_vision("$N看了看天色，自言自语道：“天色不早了，得去干活了。”\n", this_object());
        destruct(this_object());
}

int ask_fight()
{
        if (this_object()->query("uni_target")==this_player()) {
        	if (environment(this_object())->query("no_fight")) 
        	{
        		command("say 此处比武多有不便，你且随我来！");
        		random_move();
        	}
        	else command("say 要打便打，不必多言！");
        } else command("say 就你也配跟我讨教功夫？！");
        return 1;
}

int ask_rumors()
{
        if (this_object()->query("uni_target")==this_player())
                command("say 听说有个叫"+this_player()->query("name")+"的会来找我麻烦，就是你么？");
        else
                command("say 听说闯王宝藏里面有不少好东西，嘿嘿～～嘿嘿～～");
        return 1;
}

int generate(object where)
{
    where = MAP_D->random_place();
    return 1;
}

void die()
{
        object map,killer,where;
        object me = query("uni_target"); 
      // object who = this_player();      
        object mykiller;//盗宝人的killer
        int newkiller,i,num;
        object thisroom;

        if(!me || this_object()->query("uni_target")!=me)
        {
                ::die();
                return;
        } 

        if( !objectp(mykiller = get_damage_origin_object()) || mykiller->query("id")!= me->query("id"))
        {
        	     message_vision(HIC"$N说道：“你...”，话没说完，两眼翻白，腿儿蹬了几下，脑袋一歪，死了。\n",this_object());
               ::die();
               return;
        }
        
        map=new("/d/changbai/npc/obj/map"+this_object()->query("hyd/step")+".c");
        num = ((int)this_object()->query("hyd/step"));
        me->set("yidao/done",num);
        me->add("yidao/hard", query_temp("advanced_quest") );
        map->set("owner",me->query("id"));
        map->move(this_object());

        if (random(2)) 
        	GEM_D->drop(this_object(),me);

        ::die();        
}

void unconcious()
{        
        object ob = this_object();
        if( ob->query("qi")>=100 )
          return;
        call_out("die",1);
}

int do_copy(object me)  
{                       
        int exp;
        int skill, str;
        int index;
        int factor, jl_fact, qx_fact, nl_fact;
        int tf_mi, tf_ma;
        if(!objectp(me)) return 0;
        exp=me->query("combat_exp");
        index=me->query("yidao/times")/250;
        
        if ( me->query("yidao/times") < 1000 )
        {
          jl_fact=20;
          qx_fact=100;
          nl_fact=50;
          tf_mi=10;
          tf_ma=30;
        }
        else if ( me->query("yidao/times") < 5000 )
        {
          jl_fact=50;
          qx_fact=200;
          nl_fact=100;
          tf_mi=15;
          tf_ma=35;
        }
        else if ( me->query("yidao/times")/25 <= 500 )
        {
          jl_fact=67;
          qx_fact=me->query("yidao/times")/25;
          nl_fact=me->query("yidao/times")/50;
          tf_mi=20;
          tf_ma=40;
        }
        else 
        {
          jl_fact=100;
          qx_fact=500;
          nl_fact=250;
          tf_mi=25;
          tf_ma=45;
        }
        
        //family_skill会set npc的chat_chance_combat为100，这个变态！
        //必须把family_skill放在最前面！ 
        if (this_object()->query("hyd/step") != 5)
        {
        		factor=(5+this_object()->query("hyd/step")+random(index));
        		if ( factor>20 )
        		  factor=20+(factor-20)/3;
        		if (factor > 30) factor = 30;

		        es_copy1( me, "shenlongjiao", factor*10, 100, jl_fact);
		        set("chat_chance_combat", 10+this_object()->query("hyd/step")*5);
		    }
        else
        {
		        es_copy1( me, "shenlongjiao", 125, 100, jl_fact);
        		set("chat_chance_combat", 40);
        }
        
        if ( query_temp("advanced_quest") )
          set("name", HIR+query("name")+NOR);
        set("level",me->query("level")+random(5));
        
        str=me->query_str();
        if ( str > 200 )
        	str=200;
        
        if ( str <= 50 )
          nl_fact=nl_fact*2;
        
        qx_copy2( str, qx_fact, nl_fact);
        tf_set( tf_mi, tf_ma );
        
        set("qi", me->query("max_qi") * 2);
        set("jing", me->query("max_jing") * 2);
        set("uni_target", me);
        set("killer",me->query("id"));
        wield_weapon();
}