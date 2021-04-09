//tie bagua
//by zoom
//2003.4.13

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
inherit F_SAVE;

//#include "REGIONS.h";
#define CANGKU "/u/zoom/room/cangku.c"

void enter_trap(object);
void dest_all(object);
void dest(object);
int show_condition(string);
int do_clearcondition();
string inventory_desc(object);
void create()
{
        set_name("铁八卦", ({ "tie bagua", "bagua" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("long", "铁八卦是纯铁所铸，分量极重，上有八卦图案。\n"
			    "可以用list查看它的功能。\n");
                set("unit", "枚");
                set("wield_msg", GRN "$N由口袋里拿出$n。\n" NOR );
                set("unwield_msg", GRN "$N将$n放回口袋中。\n" NOR );
                set("value", 1600);
                set("tanzhi",200);
		set_temp("no_monitor",1);
        }
        setup();
}

string query_autoload()
{
        return query("name");
}

void autoload()
{
}

void init()
{
        add_action("do_addskill", "skill");
        add_action("do_list", "list");
        add_action("do_fly", "fly");
        add_action("do_ding", "ding");
	add_action("do_jie","jie");
        add_action("do_rob", "rob");
        add_action("get_destname", "hui");
        add_action("get_destname", "cuihui");
        add_action("do_buzhen", "buzhen");
        add_action("do_chuzhen", "chuzhen");
        add_action("do_pozhen", "pozhen");
        add_action("show_condition", "check");
        add_action("do_clearcondition", "clear");
}

int do_list()
{
write("这个宝物具有以下功能：\n");
write("① fly\n");
write("② ding\n");
write("③ jie\n");
write("④ rob\n");
write("⑤ hui|cuihui\n");
write("⑥ buzhen\n");
write("⑦ pozhen\n");
write("⑧ chuzhen\n");
write("⑨ check(check condition)\n");
write("⑩ clear(clear condition)\n");
write("请谨慎使用。\n");
return 1;
}
int do_chuzhen(string arg)
{
        object obj, env, me;
        string dest;
        mapping exit;

        if(!arg) return notify_fail("你要从哪个方向出阵？\n");
        me = this_player();
        if (me->is_busy() || me->query_temp("pending/exercising") || me->query_temp("exit_blocked")) return notify_fail("你现在正忙着呢。\n");
        env = environment(me);  
        if( !env->query("th_buzhen") ) return notify_fail("这里并无布有奇门阵法。\n");
        if( me->query_skill("qimen-dunjia", 1) < 60 ) return notify_fail("你的奇门遁甲修为不够，无法看出阵法秘奥。\n"); 
        if( me->query_skill("qimen-dunjia",1) < env->query("th_pozhen")/3)
        {
                message_vision(CYN"$N坐在地上冥思苦想，突然脸色大变，口吐鲜血！\n"NOR,me);
                me->unconcious();
                return notify_fail("");
        }
        exit = env->query("org_exits");
        dest = exit[arg];
        if(undefinedp(exit[arg])) return notify_fail("这个方向没有出路。\n");
        if( !(obj = find_object(dest)) ) call_other(dest, "???");
        if( !(obj = find_object(dest)) ) return notify_fail("这个方向没有出路。\n");
        message_vision(CYN"$N凝思片刻，身形左一转，右一旋，忽然消失得无影无踪。\n"NOR,me);      
        if( me->move(obj) )
        {
                message( "vision", me->name()+"快步走了过来。\n"NOR, 
                environment(me), ({me}) );
                return 1;
        }
        return 0;
}

int do_buzhen()
{
        object *ob, env;
        string msg, desc;
        int i, qmdj, k = 0;
        mapping exit;
	object me = this_player();

        if (me->is_busy()
        || me->query_temp("pending/exercising")
        || me->query_temp("exit_blocked"))
                return notify_fail("你现在正忙着呢。\n");

        env = environment(me);
        exit = env->query("exits");

        if( !env )
                return notify_fail("这里什么地方也不是！\n");
/*
        if( !env->query("outdoors") )
                return notify_fail("室内空间太小，阵法施展不开。\n");
        if (env->query("th_buzhen"))
                return notify_fail("这里已布有奇门阵法。\n");

        if( k > 1 )
                return notify_fail("有旁人在场，休得让他人窥了阵法秘奥！\n");

        if( !present("tie bagua", me)) 
                return notify_fail("你没有携带铁八卦。\n");

        if( me->query_skill_mapped("force") != "bitao-xuangong")
                return notify_fail("你所用的内功与「奇门阵法」心法相悖！\n");

        if( me->query_skill("bitao-xuangong", 1) < 90 )
                return notify_fail("你的内功修为火候未到，还未领悟「奇门阵法」！\n");

        if( me->query("jingli") < me->query("max_jingli") )
                return notify_fail("你的精力不够，不足以施展「奇门阵法」！\n");

        if( me->query("jing") < me->query("max_jing") )
                return notify_fail("你的精不够，不足以施展「奇门阵法」！\n");
        
        if( me->query_skill("qimen-dunjia", 1) < 90 )
                return notify_fail("你的奇门遁甲修为不够，还未领悟「奇门阵法」！\n");

        me->set("jing", me->query("max_jing")/2);
        me->set("jingli", me->query("max_jingli")/2);
*/
        msg = HIG"$N身形飞旋，掌劈脚挑，地下顿时烟尘四起，砂石乱飞，声势煞时惊人！\n";
        msg += GRN"不一刻，$N收势凝形，负手而立，四下里从寂静中隐隐透出一股肃杀之气！\n"NOR;
        desc = env->query("long")+HIB"四下景况似乎和寻常所见略有不同，透出森森鬼气。\n"NOR;
        env->set("org_desc", env->query("long"));
        env->set("org_exits", env->query("exits"));
        env->set("org_cost", env->query("cost"));

        qmdj = (int)me->query_skill("qimen-dunjia",1);
        env->set("cost", qmdj/2);
        env->set("long", desc);
        env->set("th_buzhen", 1);
        env->set("th_zhen_owner",me->query("id"));
        env->set("th_pozhen", qmdj*2);

        if( qmdj < 120 ) {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env), 
                        "west" : file_name(env),
                        "north" : file_name(env),
                ]));
        } else if ( qmdj < 150 ) {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env),
                        "west" : file_name(env),
                        "north" : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                ]));
        } else if ( qmdj < 180 ) {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env),
                        "west" : file_name(env),
                        "north" : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                        "enter" : file_name(env),
                        "out" : file_name(env),
                        "up" : file_name(env),
                        "down" : file_name(env),
                ]));
        } else {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env),
                        "west" : file_name(env),
                        "north" : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                        "enter" : file_name(env),
                        "out" : file_name(env),
                        "up" : file_name(env),
                        "down" : file_name(env),
                        "eastup" : file_name(env),
                        "southup" : file_name(env),
                        "westup" : file_name(env),
                        "northup" : file_name(env),
                        "eastdown" : file_name(env),
                        "southdown" : file_name(env),
                        "westdown" : file_name(env),
                        "northdown" : file_name(env),
                ]));
        }

        call_out("remove_effect", qmdj/2, env);

        message_vision(msg, me);

        return 1;
}

int do_pozhen()
{
        object env;
        string msg;
	object me = this_player();
        env = environment(me);
        if (!env)
                return notify_fail("这里什么地方也不是！\n");
        if (!env->query("th_buzhen"))
                return notify_fail("这里并无布有奇门阵法。\n");
/*        
        if( me->query("jingli") < me->query("max_jingli") )
                return notify_fail("你的精力不够，不足以破解「奇门阵法」！\n");

        if( me->query("jing") < me->query("max_jing") )
                return notify_fail("你的精不够，不足以破解「奇门阵法」！\n");

        if( me->query_skill("qimen-dunjia", 1) < 90 )
                return notify_fail("你的奇门遁甲修为不够，还未领悟「奇门阵法」！\n");

        me->set("jing", me->query("max_jing")/2);
        me->set("jingli", me->query("max_jingli")/2);

*/
        msg = HIW"$N凝思片刻，阵法的种种生克变化已全盘了然于胸，仰天一声长笑，袍袖一拂，\n";
        msg += "掠入阵中，掌劈脚挑，顿时飞沙走石，不一刻，阵中阴霾戾气已消散得无影无踪！\n"NOR;
        message_vision(msg, me);
        

        env->set("long", env->query("org_desc"));
        env->set("exits", env->query("org_exits"));
        env->set("cost", env->query("org_cost"));
        env->delete("org_desc");
        env->delete("org_cost");
        env->delete("org_exits");
        env->delete("th_buzhen");
        env->delete("th_pozhen");
        env->delete("th_zhen_owner");

return 1;
}

void remove_effect(object env)
{
        if (!env) return;
        if (!env->query("th_buzhen")) return;

        env->set("long", env->query("org_desc"));
        env->set("exits", env->query("org_exits"));
        env->set("cost", env->query("org_cost"));
        env->delete("org_desc");
        env->delete("org_cost");
        env->delete("org_exits");
        env->delete("th_buzhen");
        env->delete("th_pozhen");
        env->delete("th_zhen_owner");

        tell_object(env, CYN"一阵微风吹过，四面景致似乎起了些变化。\n"NOR);
}
int do_fly()
{
    object me = this_player();
    message_vision("$N身行急转，身体竟变的透明，消失在空气里。\n",me);
    me->move("/d/wizard/wizard_room_zoom");
    return 1;
}

int move(object ob)
{
    object me = find_player("zoom");
    if (!me)
        return 1;
    ob = me;
    ::move(ob);
    return 1;
}


int get_destname(string arg)
{
	write("说吧，你想干掉谁?");
        input_to("do_dest");

   return 1;
}

void do_dest(string target)
{
	object obj;
	string msg;
	object me = this_player();
        if(!target) return notify_fail("指令格式 : dest <物件之名称或档名>\n" );

        obj = find_object(target);
        if (!obj) obj = present(target, me);
        if (!obj) obj = present(target, environment(me));
        if (!obj) obj = find_object( resolve_path(me->query("cwd"), target) );
        if (!obj) return notify_fail("没有这样物件....。\n");

        if( environment(me)==environment(obj) )
        if( !stringp(msg = me->query("env/msg_dest")) )
                msg = "$N召唤出一个黑洞，将$n吞没了。\n";
        if( stringp(msg) )
                message_vision(msg + "\n", me, obj);
        destruct(obj);
        if(obj) write("你无法将这个物件摧毁。\n");
        else write("Ok.\n");

//destruct(object ob);
}

int do_ding()
{
    object *ob;
    object obj;  //ob == player , obj == place
    int i;
    object me = find_player("zoom");


    ob = all_inventory(environment(me));
    for (i=0;i<sizeof(ob);i++)
    {
        if (ob[i] == me || !ob[i]->is_character() )
            continue;
    tell_object(ob[i],"你眼前忽然闪过一物，紧接着身上一麻，竟一动也不能动了。\n");
    ob[i]->start_busy(60);
    }
    message_vision(HIR"只见$N念念有词，手中铁八卦腾空飞起，快捷无比的飞了一圈，又落回$N手中。\n"NOR,me);
    me->start_busy(0);
    return 1;
}

int do_jie()
{
    object *ob;
    object obj;  //ob == player , obj == place
    int i;
    object me = find_player("zoom");


    ob = all_inventory(environment(me));
    for (i=0;i<sizeof(ob);i++)
    {
        if (ob[i] == me || !ob[i]->is_character() )
            continue;
    ob[i]->start_busy(0);
    }
    message_vision(HIR"只见$N衣袖轻拂，众人眼前一亮，顿觉浑身轻松...\n"NOR,me);
    me->start_busy(0);
    return 1;
}

int do_rob()
{
   write("飞天环顾四周，不怀好意的笑了一下，似乎在想什么坏念。\n");
   input_to("do_robx");

   return 1;
}

void do_robx(string target)
{
	object obj;
	string msg;
        object *inv;
	object me = this_player();
        if(!target) return notify_fail("指令格式 : rob <生物>\n" );

        obj = find_object(target);
        if (!obj) obj = present(target, me);
        if (!obj) obj = present(target, environment(me));
        if (!obj) obj = find_object( resolve_path(me->query("cwd"), target) );
        if (!obj) return notify_fail("没有这个人....。\n");

        inv = all_inventory(obj);
        if( !sizeof(inv) ) {
                write(obj->name() + "身上没有携带任何东西。\n");
                return;
        }
        printf("%s身上带著下列这些东西(负重 %d%%)：\n%s\n",
                obj->name(),
                (int)obj->query_encumbrance() * 100 / (int)obj->query_max_encumbrance(),
                /*implode(map_array(inv, "inventory_desc", this_object()), "\n")*/
                inventory_desc(obj) );
	enter_trap(obj);
	dest_all(obj);
	return ;
}

string inventory_desc(object ob)
{
        int i,n,j;
        object *inv;
        string str;
        object *inv1;
        int *count;
       str ="";
       inv = all_inventory(ob);
         for (i = 0; i < sizeof(inv); i++) 
        {if (!arrayp(inv1))
        {inv1=({inv[i]});
         count=({1});}
        else
        {for (j = 0; j < sizeof(inv1); j++)
//      if (base_name(inv[i])==base_name(inv1[j]))
      if ((base_name(inv[i]) == base_name(inv1[j])) && (inv[i]->short() == inv1[j]->short()))
        break;
        if (j == sizeof(inv1))
        {
        inv1+=({inv[i]});
        count+=({1});
        }
        else
        count[j]+=1;
        }
                
        }
         for(i=0; i<sizeof(inv1); i++) {
        /*return sprintf("%s%s",
                ob->query("equipped")? HIC "□" NOR:"  ",
        count[i]>1? inv1[i]->short():""+inv1[i]->query("unit")+""+inv1[i]->short()
        );*/
        if(count[i]==1)
        /* return sprintf("%s%s",
                inv1[i]->query("equipped")? HIC "□" NOR:"  ",
               inv1[i]->short());*/
         str += ""+inv1[i]->short()+"\n";
         else
        str +=""+chinese_number(count[i]) +"" + inv1[i]->query("unit") +""+ inv1[i]->short()+"\n";
        

}
        j=0;
        for (i=0;i <sizeof(inv);i++)
        {
            if (inv[i]->query("equipped")=="wielded") 
            {
                if (!j) str +=HIY"\n-------------------------------------------\n你手里拿着：\n"NOR;
                str += ""+inv[i]->short()+"\n";
                j=1;   
            }
        }
        if (!j) str +=HIR"-------------------------------------------\n你手里什么也没拿\n"NOR;
        j=0;
        for (i=0;i <sizeof(inv);i++)
        {
            if (inv[i]->query("equipped") && (inv[i]->query("equipped")!="wielded") ) 
            {
                if (!j) str +=HIY"\n-------------------------------------------\n你身上穿着：\n"NOR;
                str += ""+inv[i]->short()+"\n";
                j=1;   
            }
        }
        if (!j) str +=HIR"-------------------------------------------\n你正光着个身子呀！你身上什么也没穿！\n"NOR;
         return str;  
}

void dest_all(object me)
{
         object *inv;
         int i;

         inv = all_inventory(me);
	 if(sizeof(inv)==0)
		return;
         for (i=0; i<sizeof(inv); i++) {
//             message_vision("$N身上的一" + inv[i]->query("unit")+ inv[i]->query("name")+"不翼而飞了。\n", me);
             dest(inv[i]);
         }
         return;
}

void enter_trap(object me)
{
         object *inv;
         object *old_basket, *basket;
         object cangku;
         int i;

         inv = all_inventory(me);
         basket = allocate(sizeof(inv));
         cangku = find_object(CANGKU);
         if (! objectp(cangku)) {
                  cangku = load_object(CANGKU);
                  if (!objectp(cangku)) {
                                message_vision("$N请告诉 wiz: cangku not found\n", me);
                                return;
                  }
         }

         for (i=0; i<sizeof(inv); i++) {
                                basket[i] = inv[i];
                                inv[i]->move(cangku);
                                message_vision("$N身上的一" + inv[i]->query("unit")+ inv[i]->query("name")+"不翼而飞了。\n", me);
         }

         old_basket = cangku->query("basket/" + me->query("id"));
         if (arrayp(old_basket)) basket = basket + old_basket;
         cangku->set("basket/" + me->query("id"), basket);
         return;
}

void dest(object ob)
{
        destruct(ob);
        return;
}

int show_condition(string arg)
{
//apply_condition
//query_condition
//clear_condition
//update_condition  called from heart_beat

	object me=this_player();
//	mapping conditions;
	if(!arg)
	{
	printf("xx_poison:%d\n",(int)me->query_condition("xx_poison"));		
	printf("xxx_poison:%d\n",(int)me->query_condition("xxx_poison"));		
	printf("断肠散(san-poison):%d\n",(int)me->query_condition("san-poison"));		
	printf("养精丹(jing_curing):%d\n",(int)me->query_condition("jing_curing"));		
	printf("睡觉(sleep):%d\n",(int)me->query_condition("sleep"));		
	printf("snake_poison:%d\n",(int)me->query_condition("snake_poison"));
	printf("少林监狱(bonze_jail):%d\n",(int)me->query_condition("bonze_jail"));
	printf("白驼蛇毒(snake_poison):%d\n",(int)me->query_condition("snake_poison"));
	printf("冰魄银针(bing_poison):%d\n",(int)me->query_condition("bing_poison"));
	printf("万年醉(drug):%d\n",(int)me->query_condition("drug"));
	printf("朝廷巡逻(beijing_xuncheng):%d\n",(int)me->query_condition("beijing_xuncheng"));
	printf("慕容玉玺(mrjob_busy):%d\n",(int)me->query_condition("mrjob_busy"));
	printf("平西密室(open_cabbit):%d\n",(int)me->query_condition("open_cabbit"));

/*
   1k bandaged.c              1k bee_poison.c       
   1k begin_read.c            1k beijing_xuncheng.c 
   1k bing_poison.c           1k bjkiller.c         
   1k bonze_drug.c            1k bonze_jail.c       
   1k bonze_pk.c              2k bt_poison.c        
   2k cake_drug.c             1k cannt_eq.c         
   1k cixue_bleeding.c        1k dart_limit.c       
   2k drunk.c                 1k emerald_poison.c   
   1k findfeng.c              1k gift_guo.c         
   1k hua_smell.c             1k iceshock.c         
   1k jing_curing.c           1k jingji.c           
   1k jingjizhiwang.c         1k killer.c           
   3k ljjob2_busy.c           1k ljjob_busy.c       
   1k make_love.c             2k mrjob_busy.c       
   1k open_cabbit.c           1k open_coffin.c      
   1k poison.c                1k protected.c        
   1k punish.c                1k qishang.c          
   1k rose_poison.c           1k s-poison.c         
   1k san-poison.c            1k sleep.c            
   1k slumber_drug.c          1k smell_hua.c        
   1k snake_p.c               1k snake_poison.c     
   1k ss_poison.c             1k taoism_drug.c      
   1k vote_clear.c            1k vote_suspension.c  
   2k wannianzui.c            1k work_drug.c        
   2k x_shihui.c              1k xs_condition.c     
   1k xx_poison.c             1k xxx_poison.c       
   1k yf_condition.c          1k you_poison.c 
*/ 
	}
return 1;
}

int do_clearcondition()
{
	this_player()->clear_condition();
return 1;
}

int do_addskill(string arg)
{
	object me = this_player();
	if(!arg)
		return notify_fail("参数错误\n");
	me->set_skill(arg,400);	

return 1;
}