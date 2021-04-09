// File         : killer.c
// Created By   : whuan@pkuxkx, 2007-07-02

#include <ansi.h>

inherit FAMILY_NPC;
int ask_rumors();
int do_copy(object me);
varargs void wield_weapon(string weapon);
void die();
void create()
{
        set_name("盗宝人", ({ "daobao ren", "ren" }) );
        set("gender", "男性" );
        set("age", 22+random(22));
        set("combat_exp", 10000000);
        set("attitude", "heroism");
        add("inquiry", ([
                "name" : "大爷我有要事在身，别烦我！",
                "here" : "大爷我有要事在身，别烦我！",
                "rumors" : (:ask_rumors:),
        ]));
        set("chat_chance", 30);
        set("chat_msg", ({
                (: random_move :),
        }) );
        set("uni_target", 1);
        set("jiali", 50);
        setup();
        call_out("do_leave", 1800);
}

void init()
{
        if (environment(this_object())->query("no_fight"))
        ::random_move();
        if (this_object()->query("uni_target")==this_player()){
        switch (random(4)){
        	case 0:
        		message_vision("$N看见$n，心里打着小鼓，一声不吭的就溜走了！\n",this_object(), this_player());
        		::random_move();
        		break;
        	case 1:
        	  message_vision("$N看见$n，阴笑一声：天堂有路你不走，地狱无门你来投！\n",this_object(), this_player());
        	  kill_ob(this_player());
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
        message_vision("$看了看天色，自言自语道：“天色不早了，得去干活了。”\n", this_object());
        destruct(this_object());
}
int ask_rumors()
{
        if (this_object()->query("uni_target")==this_player())
        	command("say 听说有个叫"+this_player()->query("name")+"的会来找我麻烦，就是你么？");
        else
        	command("say 听说闯王宝藏里面有不少好东西，嘿嘿～～嘿嘿～～");
        return 1;
}
varargs void wield_weapon(string weapon)
{
        if(!weapon && query("use_weapon1"))
                wield_weapon(query("use_weapon1"));
        if(!weapon && query("use_weapon2"))
                wield_weapon(query("use_weapon2"));
        if(!weapon)
                return;
        switch(weapon)
        {
        case "sword":
                carry_object("/clone/weapon/changjian")->wield();
                break;
        case "blade":
                carry_object("/clone/weapon/gangdao")->wield();
                break;
        case "staff":
                carry_object("/clone/weapon/gangzhang")->wield();
                break;
        case "whip":
                carry_object("/clone/weapon/changbian")->wield();
                break;
        case "zhen":
                set("gender", "无性");
                carry_object("/d/city/obj/flower_shoe")->wear();
                carry_object("/d/city/obj/pink_cloth")->wear();
                carry_object("/d/city/obj/goldring")->wear();
                carry_object("/d/city/obj/necklace")->wear();
                carry_object("/d/quanzhou/obj/xiuhua")->wield();
                carry_object("/d/riyuejiao/obj/xiuhuajia");
                break;
        case "dagger":
                carry_object("/clone/weapon/bishou")->wield();
                break;
        case "xiao":
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/obj/shizi");
                carry_object("/d/taohuadao/npc/obj/yuxiao")->wield();
         break;
         case "ling":
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/npc/obj/jinhua");
                carry_object("/d/mingjiao/obj/shenghuo-ling")->wield();
         break;
        case "hammer":
                carry_object("/d/dalunsi/npc/obj/iron-falun")->wield();
                break;
        default:
        }
        return;
}
void unconcious()
{        
	die();
}

void die()
{
	      object map,killer,where;
        object me = query("uni_target");
        if(!objectp(query_temp("last_damage_from")) || query_temp("last_damage_from") != me)
        {
               map=new("/d/changbai/npc/obj/map1.c");
               map->set("owner",me->query("id"));
               map->move(this_object());
               killer=new("/d/changbai/npc/killer.c");
               killer->do_copy(me);
               where = TASK_D->random_place();
               killer->move("where");
               killer->random_move();
               killer->random_move();
               killer->random_move();
               message_vision(this_object()->name()+"说道：“你有种去"+TASK_D->place_belong(where)+"找我兄弟，他会给我报仇的！”");
               ::die();
               return;
        }
        message_vision(this_object()->name()+"说道：“你...你...。”");
        ::die();
}

int do_copy(object me)  
{                       
        int exp;
        int skill;
        if(!objectp(me)) return 0;
        exp=me->query("combat_exp");
        skill=pow(me->query("combat_exp")/100*4/5, 0.333);                        
        family_skill(this_object(), "shenlong", skill, 1);
        set("chat_chance_combat", 60);
        set("max_qi", me->query("max_qi") * 2);
        set("qi", me->query("max_qi") * 2);
        set("max_jing", me->query("max_jing") * 2);
        set("jing", me->query("max_jing") * 2);
        set("max_neili", me->query("max_neili") * 3/2);
        set("neili", me->query("max_neili") * 3/2);
        set("max_jingli", me->query("max_jingli") * 3/2);
        set("jingli", me->query("max_jingli") * 3/2);
        set("jiali",skill+random(skill));
        set("uni_target", me);
        wield_weapon();
}
