// by Vast@pkuxkx
// all comments added by Vast

#include <ansi.h>
#include <armor.h>

inherit F_GEMS;
inherit EQUIP;

void setup_armor(object ob);
void setup_surcoat(object ob);
string set_armor_desc(object ob);


varargs void init_sockets(int seed)
{
        int i, max, flag;
        string type;
        object ob = this_object();

        //1，2，3孔出现的几率为888:111:1
        //生成方式太简单，以后加强

        if(seed < 0)  error("S-weapon: 种子数不正确 .\n");
        if(seed > 3)  error("S-weapon: 种子数不正确 .\n");

        if(!query("sockets/max") && !seed)
        {
                i = random(1000);

                if (i < 888)
                max = 1;
                else if (i < 999)
                max = 2;
                else if (query("unqiue")) //非Unique盔甲最多两个孔
                max = 3;
                else
                max = 2;
                set("sockets/max", max);
        }
        else if(seed) set("sockets/max", seed);

        if( !stringp(type = ob->query("skill_type")) )
        {
                type = "armor";
                ob->set("armor_type", "armor");
        }
        switch(type)
        {
                case "armor":
                        setup_armor(ob);
                        break;
                //此处为新增防具类型做准备
                default:
                        error("S-weapon: undefined type " + type + ".\n");
        }
        //暂时不做复杂的分类，armor_type只设定盔甲(armor)一种
        //以后根据情况可增加 鞋(boots),帽子(head),衣物(cloth),手套(hands),外套(surcoat),腰带(waist),护腕(wrist)

}

void setup_armor(object ob)
{
        int hole, i, min_def, max_def, def;
        string longdes;

        ob->set_name(ob->query("name"), ob->query("armor_id"));

        longdes = ob->query("base_long");
        longdes += set_armor_desc(ob);

        set("long", longdes);

        //材料
        if (!ob->query("material")) ob->set("material", "silk");

        //耐久度
        if (!ob->query("rigidity")) ob->set("rigidity", 300);
        if (!ob->query("max_rigidity")) ob->set("max_rigidity", ob->query("rigidity"));

        //wear,unequip msg
        if (!stringp(ob->query("wear_msg")))
        set("wear_msg", "$N穿上一件$n。\n");
        else
        set("wear_msg", ob->query("wear_msg"));

        if (!stringp(ob->query("unequip_msg")))
        set("unequip_msg", "$N将$n脱下。\n");
        else
        set("unequip_msg", ob->query("unequip_msg"));

        if (!ob->query("armor_prop/armor"))
        {
                if (!(min_def = ob->query("armor/min_def"))) min_def = 1;
                if (!(max_def = ob->query("armor/max_def"))) max_def = min_def + 10;
                def = min_def + random(max_def - min_def + 1);
                ob->set("armor_prop/armor", def);
        }
}

void setup_surcoat(object ob)
{
        int hole, i, min_def, max_def, def;
        string longdes;

        ob->set_name(ob->query("name"), ob->query("armor_id"));

        longdes = ob->query("base_long");
        longdes += set_armor_desc(ob);

        set("long", longdes);

        //材料
        if (!ob->query("material")) ob->set("material", "silk");

        //耐久度
        if (!ob->query("rigidity")) ob->set("rigidity", 300);
        if (!ob->query("max_rigidity")) ob->set("max_rigidity", ob->query("rigidity"));

        //wear,unequip msg
        if (!stringp(ob->query("wear_msg")))
        set("wear_msg", "$N穿上一件$n。\n");
        else
        set("wear_msg", ob->query("wear_msg"));

        if (!stringp(ob->query("unequip_msg")))
        set("unequip_msg", "$N将$n脱下。\n");
        else
        set("unequip_msg", ob->query("unequip_msg"));

        if (!ob->query("armor_prop/armor"))
        {
                if (!(min_def = ob->query("armor/min_def"))) min_def = 1;
                if (!(max_def = ob->query("armor/max_def"))) max_def = min_def + 10;
                def = min_def + random(max_def - min_def + 1);
                ob->set("armor_prop/armor", def);
        }
}

string spec_effect(object victim, object me, int damage, string act)
{
        int i, magic, kar, ratio, dam, def = 0;
        string msg = "";

        //成功率(可能设定简单了一点)
        magic = me->query_temp("apply/magic");
        kar = me->query_kar();
        if (kar > 40) kar = 40;
        if ( ((kar / 10 )* ((magic + 100) / 100) + 40 )< random(100)) return msg;

        switch (act) {
/*      case "poison":
                msg = HIG"$n的盔甲上淬有剧毒！只见一道绿气迅速延伸到$N的手臂！\n"NOR;
                ob->apply_condition("emerald_poison", ob->query_condition("emerald_poison") + query("armor_effect/poison"));
                if (!ob->is_killing(me->query("id"))) ob->kill_ob(me);
                break;
*/
        case "rebound":
                ratio = query("armor_effect/rebound");
                if(ratio > 100) ratio = 100;
                dam = damage * ratio / 50;
                msg = RED"$N这一击就像撞在了一堵墙上，攻击竟尽数反弹了回来！\n"NOR;
                victim->receive_damage("qi", dam, me);
                victim->receive_wound("qi", dam/2 + random(dam/2), me);

                //是否加入反弹受伤后的描述
                if (wizardp(me))
                        tell_object(me, sprintf("反震伤害力： %d\n", dam));
                break;
        }
        return msg;
}

mixed ob_hit(object victim, object me, int damage)
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
                msg += spec_effect(victim, me, damage, act);
        }

        return msg;
}


