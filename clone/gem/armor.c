// by Vast@pkuxkx
// all comments added by Vast

#include <ansi.h>
#include <armor.h>

//advent
inherit F_GEMS;
inherit EQUIP;

void setup_armor();
void setup_surcoat();
varargs void gen_armor(int min, int max);
varargs void gen_surcoat(int min, int max);
void init_sockets();

void create()
{
int type;
        //只能在专门的地方进行买卖
              set("no_store",1);
        set("no_sell",1);
        set("no_pawn",1);
type=random(2);
        set("type",type);
        if (type==0)    gen_armor();
        else gen_surcoat();
        setup();
}

varargs void gen_armor(int min, int max)
{
        //盔甲的基本类型 相当于diablo中的灰色物品
        //皮甲，铁甲、青铜甲、锁子甲、连环甲、藤甲、白银铠甲、黄金铠甲
        int i, type;

        if(!min) min = 0;
        if(!max) max = 10000;

        if (min > max) return;
        if (min < 0) return;
        if (max > 10000) return;

        i = min + random(max - min);

        //此处还可做相应调整
        if (i < 2500) type = 1;         //(25%)
        else if (i < 4500) type = 2;    //(20%)
        else if (i < 6100) type = 3;    //(16%)
        else if (i < 7300) type = 4;    //(12%)
        else if (i < 8500) type = 5;    //(12%)
        else if (i < 9300) type = 6;    //(8%)
        else if (i < 9700) type = 7;    //(4%)
        else type = 8;  //(3%)

        switch(type)
        {
                case 1:
                set_name(YEL"皮甲"NOR, ({ "pi jia", "armor", "jia" }) );
                set("base_weight", 5000 + random(5000));
                set("armor/long", "这是一件普通的皮甲，可以作为一般的防身器具。\n");
                set("material", "leather");
                //set("rigidity", 50 + random(100));
                set("value", 50000);
                set("armor/min_def", 50);
                set("armor/max_def", 100);
                break;
                case 2:
                set_name(WHT"铁甲"NOR, ({ "tie jia", "armor", "jia" }) );
                set("base_weight", 15000 + random(10000));
                set("armor/long", "这是一件普通的铁甲，虽然防身的效果不错，不过过于沉重。\n");
                set("material", "iron");
                //set("rigidity", 80 + random(100));
                set("value", 80000);
                set("armor/min_def", 80);
                set("armor/max_def", 150);
                break;
                case 3:
                set_name(HIC"青铜甲"NOR, ({ "qingtong jia", "armor", "jia" }) );
                set("base_weight", 15000 + random(15000));
                set("armor/long", "青铜甲的韧性十足，防御力很不错。\n");
                set("material", "copper");
                //set("rigidity", 150 + random(50));
                set("value", 100000);
                set("armor/min_def", 100);
                set("armor/max_def", 200);
                break;
                case 4:
                set_name(CYN"锁子甲"NOR, ({ "suozi jia", "armor", "jia" }) );
                set("base_weight", 8000 + random(18000));
                set("armor/long", "精钢制成的极品盔甲，减轻重量的同时提高了防御力。\n");
                set("material", "steel");
                //set("rigidity", 20 + random(50));
                set("value", 120000);
                set("armor/min_def", 80);
                set("armor/max_def", 260);
                break;
                case 5:
                set_name(RED"连环甲"NOR, ({ "lianhuan jia", "armor", "jia",}) );
                set("base_weight", 8000 + random(18000));
                set("armor/long", "精钢制成的极品盔甲，减轻重量的同时提高了防御力。\n");
                set("material", "steel");
                //set("rigidity", 50 + random(200));
                set("value", 120000);
                set("armor/min_def", 120);
                set("armor/max_def", 220);
                break;
                case 6:
                set_name(BLU"藤甲"NOR, ({ "teng jia", "armor", "jia" }) );
                set("base_weight", 3000 + random(3000));
                set("armor/long", "这种浸过油的藤甲质地良莠不齐，不同品种防御力相差很大。\n");
                set("material", "wood");
                //set("rigidity", 250 + random(100));
                set("value", 90000);
                set("armor/min_def", 50);
                set("armor/max_def", 400);
                break;
                case 7:
                set_name(HIW"白银铠甲"NOR, ({ "baiyin kaijia", "armor", "jia", "kaijia" }) );
                set("base_weight", 10000 + random(15000));
                set("armor/long", "华丽又实用的铠甲，能够有效的抵御敌人猛烈的攻击。\n");
                set("material", "silver");
                //set("rigidity", 500 + random(500));
                set("value", 150000);
                set("armor/min_def", 150);
                set("armor/max_def", 350);
                break;
                case 8:
                set_name(HIY"黄金铠甲"NOR, ({ "huangjin kaijia", "armor", "jia", "kaijia" }) );
                set("base_weight", 15000 + random(25000));
                set("armor/long", "华丽的全身铠甲，极高的防御，完美之极。\n");
                set("material", "gold");
                //set("rigidity", 100000);
                set("value", 200000);
                set("armor/min_def", 250);
                set("armor/max_def", 500);
                break;
        }
        delete("armor_prop/armor");
        init_sockets();
}

varargs void gen_surcoat(int min, int max)
{
        //外套的基本类型 相当于diablo中的灰色物品
        int i, type;

        if(!min) min = 0;
        if(!max) max = 10000;

        if (min > max) return;
        if (min < 0) return;
        if (max > 10000) return;

        i = min + random(max - min);

        //此处还可做相应调整
        if (i < 2500) type = 1;         //(25%)
        else if (i < 4500) type = 2;    //(20%)
        else if (i < 6100) type = 3;    //(16%)
        else if (i < 7300) type = 4;    //(12%)
        else if (i < 8500) type = 5;    //(12%)
        else if (i < 9300) type = 6;    //(8%)
        else if (i < 9700) type = 7;    //(4%)
        else type = 8;  //(3%)

        switch(type)
        {
                case 1:
                set_name(YEL"羊皮袄子"NOR, ({ "yangpi aozi", "aozi", "ao" }) );
                set("base_weight", 5000 + random(5000));
                set("armor/long", "以羊皮制成的袄衣。相当的保暖，但清洗不易。\n");
                set("material", "leather");
                //set("rigidity", 50 + random(100));
                set("value", 50000);
                set("armor/min_def", 50);
                set("armor/max_def", 100);
                break;
                case 2:
                set_name(WHT"牛皮背心"NOR, ({ "niupi beixin", "beixin" }) );
                set("base_weight", 15000 + random(10000));
                set("armor/long", "牛皮制成的背心，可着于外衣底下，阻挡一般的兵刃。\n");
                set("material", "silk");
                //set("rigidity", 80 + random(100));
                set("value", 80000);
                set("armor/min_def", 80);
                set("armor/max_def", 150);
                break;
                case 3:
                set_name(HIC"金丝背心"NOR, ({ "jinsi beixin", "beixin"}) );
                set("base_weight", 15000 + random(15000));
                set("armor/long", "以金属丝线编织而成的背心，著于外衣之下，可以防一般的刀剑枪击。\n");
                set("material", "gold");
                //set("rigidity", 150 + random(50));
                set("value", 100000);
                set("armor/min_def", 100);
                set("armor/max_def", 200);
                break;
                case 4:
                set_name(CYN"乌蚕衣"NOR, ({ "wucan yi", "yi" }) );
                set("base_weight", 8000 + random(18000));
                set("armor/long", "以大雪山上的乌蚕丝所织成，分前后两片，刀枪不入。\n");
                set("material", "silk");
                //set("rigidity", 20 + random(50));
                set("value", 120000);
                set("armor/min_def", 80);
                set("armor/max_def", 260);
                break;
                case 5:
                set_name(RED"冰蚕衣"NOR, ({ "bingcan yi", "yi"}) );
                set("base_weight", 8000 + random(18000));
                set("armor/long", "以昆仑山上的冰蚕丝所织成，分前后两片，刀枪不入。\n");
                set("material", "silk");
                //set("rigidity", 50 + random(200));
                set("value", 120000);
                set("armor/min_def", 120);
                set("armor/max_def", 220);
                break;
                default:
                set_name(HIY"金缕玉衣"NOR, ({ "jinlv yuyi", "yi"}) );
                set("base_weight", 15000 + random(25000));
                set("armor/long", "以黄金丝线穿起和田玉片制成的无匹防具。\n");
                set("material", "gold");
                //set("rigidity", 100000);
                set("value", 200000);
                set("armor/min_def", 250);
                set("armor/max_def", 500);
                break;
        }
        delete("armor_prop/armor");
        init_sockets();
}

void init_sockets()
{
        int i, max;
        //1，2，3孔出现的几率为888:111:1
        if(!query("sockets/max"))
        {
                i = random(1000);

                if (i < 888)
                max = 1;
                else if (i < 999)
                max = 2;
                else
                max = 3;
                set("sockets/max", max);
        }
        //暂时不做复杂的分类，armor_type只设定盔甲(armor)一种
        //以后根据情况可增加 鞋(boots),帽子(head),衣物(cloth),手套(hands),外套(surcoat),腰带(waist),护腕(wrist)

        if (query("type")==0) set("armor_type", "armor");
             else
            set("armor_type", "surcoat");
        //set_armor_desc();
        setup_armor();
}

void setup_armor()
{
        int hole, i;
        string longdes;
        object ob = this_object();

        //基本信息
        if(stringp(ob->query("armor/name")))
        set_name(ob->query("armor/name"), ob->parse_command_id_list());

        ob->set("unit", "件");

        //set long_desc
        if (!stringp(ob->query("armor/long")))
        longdes = "这是一件普通的铁盔甲。\n";
        else
        longdes = ob->query("armor/long");

        longdes += set_armor_desc(ob);

        set("long", longdes);

        //材料
        if (!ob->query("material")) ob->set("material", "iron");

        //耐久度（armor暂未设置此值）
        //if (!ob->query("rigidity")) ob->set("rigidity", 300);
        //if (!ob->query("max_rigidity")) ob->set("max_rigidity", ob->query("rigidity"));

        //wear,unequip msg
        if (!stringp(ob->query("wear_msg")))
        set("wear_msg", "$N穿上一件$n。\n");
        else
        set("wear_msg", ob->query("wear_msg"));

        if (!stringp(ob->query("unequip_msg")))
        set("unequip_msg", "$N将$n脱下。\n");
        else
        set("unequip_msg", ob->query("unequip_msg"));

}

string spec_effect(object ob, object me, int damage, string act)
{
        int i, magic, kar, ratio, def = 0;
        string msg = "";

        //成功率(可能设定简单了一点)
        magic = me->query_temp("apply/magic");
        kar = me->query_kar();
        if (kar > 40) kar = 40;
        if (random(100) + kar / 5 + kar * magic / 1000 < 90) return msg;

        switch (act) {
        case "poison":
                msg = HIG"$n的盔甲上淬有剧毒！只见一道绿气迅速延伸到$N的手臂！\n"NOR;
				F_POISON->poison_attack(me,ob,"emerald_poison", ob->query_condition("emerald_poison") + query("armor_effect/poison"));
                //ob->apply_condition("emerald_poison", ob->query_condition("emerald_poison") + query("armor_effect/poison"));
                if (!ob->is_killing(me->query("id"))) ob->kill_ob(me);
                break;
        case "rebound":
                ratio = query("armor_effect/rebound");
                if(ratio > 100) ratio = 100;
                damage = damage * ratio / 100;
                msg = RED"$N这一击就像撞在了一堵墙上，攻击竟尽数反弹了回来！\n"NOR;
                ob->receive_damage("qi", damage, me);
                ob->receive_wound("qi", random(damage), me);
                if (wizardp(me))
                        tell_object(me, sprintf("反震伤害力： %d\n", damage));
                break;
        }
        return msg;
}

mixed ob_hit(object ob, object me, int damage)
{
        int i;
        mapping effect;
        string act, msg = "";

        //随机出现一种效果
        //weapon_effect/jing,poison,suck
        effect = query("armor_effect");
        if (mapp(effect))
        {
                i = sizeof(effect);
                act = keys(effect)[random(i)];
                msg += spec_effect(ob, me, damage, act);
        }

        return msg;
}

