// File         : feizei.c
// Created By   : iszt@pkuxkx, 2007-03-28
// Modified by  : kiden@pkuxkx

#include <ansi.h>

inherit FAMILY_NPC;

varargs void wield_weapon(string weapon);
void die();

void create()
{
        set_name("飞贼", ({ "fei zei", "zei"}) );
        set("gender", "男性" );
        set("title", HIR"胆大包天"NOR );
        set("age", 22+random(22));
        set("long", "这是一个武艺高强的飞贼，你还是离他远一点吧。\n"
                "他的背上有一个小小包裹，看样子是才偷了什么东西在手。\n");
        set("per",10+random(20));
        set("kar",30);
        set("str",30);
        set("con",30);
        set("dex",30);
        set("int",30);
        set("attitude", "heroism");
        set("rank_info/rude", "小毛贼");
        add("inquiry", ([
                "name" : "走开点，小心老子发飙！",
                "here" : "不知道！",
                "rumors" : "嘿嘿，想知道你的祭日么？",
        ]));
        set("chat_chance", 35);
        set("chat_msg", ({
                (: random_move :),
        }) );
        set("chat_chance_combat", 100);
        family_skill(this_object(), "xueshan", 500+random(150), 1);
        set("max_qi",  3000);
        set("eff_qi",  3000);
        set("qi",      3000);
        set("max_jing",3000);
        set("eff_jing",3000);
        set("jing",    3000);
        set("max_jingli",3000);
        set("jingli", 3000);
        set("max_neili", 3000);
        set("neili", 3000);
        set("jiali",300);
        set("combat_exp",5000000);
        setup();
        call_out("do_leave", 1200);
        carry_object("/clone/armor/bianfuxuejia")->wear();
        switch(random(28))
        {
        case 0: carry_object("/clone/weapon/feizei/blade.c"); break;
        case 1: carry_object("/clone/weapon/feizei/cloth.c"); break;
        case 2: carry_object("/clone/weapon/feizei/dagger.c"); break;
        case 3: carry_object("/clone/weapon/feizei/hands.c"); break;
        case 4: carry_object("/clone/weapon/feizei/spear.c"); break;
        case 5: carry_object("/clone/weapon/feizei/staff.c"); break;
        case 6: carry_object("/clone/weapon/feizei/sword.c"); break;
        case 7: carry_object("/clone/weapon/feizei/whip.c"); break;
        case 8: carry_object("/d/shaolin/obj/yijinjing.c"); break;//易筋经内功篇，读hunyuan-yiqi 101-301
        case 9: carry_object("/d/lingxiao/obj/iceblade"); break;
        case 10: carry_object("/d/shaolin/obj/puti-zi"); break;
        case 11: carry_object("/d/qilincun/obj/liquan"); break;
        case 12: carry_object("/d/qilincun/obj/liquan"); break;
        default : add_money("gold", 15+random(30)); break;
        }
        wield_weapon();
}

void init()
{
//        command("look "+this_player()->query("id"));
        if (environment(this_object())->query("no_fight"))
        ::random_move();
}

void start_busy(mixed new_busy, mixed new_interrupt)
{
        if(intp(new_busy) && new_busy > 15)

                ::start_busy(14+random(3));
}

void unconcious()
{
        die();
}

void die()
{
        object me = get_damage_origin_object();
        if(!objectp(me) || !present(me, environment()))
        {
                ::die();
                return;
        }
        CHANNEL_D->do_channel(this_object(), "jh", "听说"HIY+me->query("name")+"铲除了飞贼！", -1);
        message_vision("$N为民除害，感觉自己修为有所增进。\n", me);
        me->add("combat_exp",1000+random(1000));
        me->add("potential",500);
        me->add("repute",200);
        ::die();
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
                carry_object("/d/mingjiao/obj/shenghuo-ling")->wield();
         break;
        case "zhen":
                set("gender", "无性");
                carry_object("/d/city/obj/flower_shoe");
                carry_object("/d/city/obj/pink_cloth");
                carry_object("/d/city/obj/goldring");
                carry_object("/d/city/obj/necklace");
                carry_object("/d/quanzhou/obj/xiuhua")->wield();
                carry_object("/d/riyuejiao/obj/xiuhuajia");
                break;
        case "dagger":
                carry_object("/clone/weapon/bishou")->wield();
                break;
        case "hammer":
                carry_object("/d/dalunsi/npc/obj/iron-falun")->wield();
                break;
        default:
                break;
        }
        return;
}
void do_leave()
{
        if(!this_object())
                return;
        message_vision("$N转身钻进人群，霎那便不见影踪。\n", this_object());
        destruct(this_object());
}
