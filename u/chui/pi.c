//mianao.c 破棉袄
//超级物件
// appear:隐形巫师显形  xing:使某人苏醒   yao:变钱    tou:偷东西  
// pretend:假扮某人  cui:催眠在场所有人  

#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>
#include <net/daemons.h>
inherit ARMOR;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;

string inputstr,verb;
int dest(object what);

void create()
{
    seteuid(getuid());
    set("long",@LONG
这是流氓猪的一件魔法披风，具有无法想象的能力。
LONG    );
    set("unit","件");
    set_name(HIC + "魔法披风" + NOR , ({"pi feng","pi"}));
    set("no_get",1);
    set("no_drop",1);
    set("no_steal",1);
    set("no_give",1);
    set("value",0);
    set("material", "cloth");
    set("armor_prop/armor", 3000);
    set("armor_type","cloth");
    set("wear_msg", HIY + "$N展开了魔法披风，立刻感觉神秘的力量漫天扑来!\n"NOR);
    set("unequip_msg",HIY + "$N从身上扯下了魔法披风。\n" NOR);
    set_weight(17);
    setup();
}

void init()
{   object ob;
    seteuid(geteuid());
    add_action("do_appear","appear");
    add_action("do_po","po");
    add_action("hun","nofill");
    add_action("wave","yao");
    add_action("steal","tou");
    add_action ("whereis", "whereis");
    add_action ("do_wakeup", "xing");
    add_action ("do_hun","hun");
    add_action ("do_sheng","sheng");
    add_action ("do_jiang","jiang");
    add_action ("do_pretend","pretend");
    add_action ("do_cui","cui");        
    add_action ("do_set","setas");
    add_action ("do_dest","deststh");
    add_action ("do_shout","st");
    add_action ("do_store","storesth");
    add_action ("do_ding","ding");
    add_action ("do_forceall","forceall");
    add_action ("do_recover","rec");
    add_action ("do_block","bb");
}

int do_appear()
{
        object *all, me = this_player();
        int i;
        message_vision(HIR"$N忽然双目圆睁,似乎看到周围隐藏着什么.\n"
                       HIY"$N用手向天空一指,忽然一道电光照澈了大地,所有隐藏在黑暗中的妖魔都现行了.\n"NOR, me);
                all = all_inventory(environment(me));
                for (i=0; i<sizeof(all); i++) {
                        if (all[i] == me) continue;
                        if (all[i]->query("env/invisibility") > 0) {
                                all[i]->delete("env/invisibility");
                                message_vision(YEL"$N现形了！\n"NOR, all[i]);
                        }
                        if (all[i]->is_ghost()) {
                                message_vision(YEL"$N的魂魄在这里！\n"NOR, all[i]);
                                                                all[i]->reincarnate();
            }
                }
        return 1;
}

int do_block (string str)
{  
    object npc,me;
    me = this_player();
	if (!str) return notify_fail ("[提示]: block <someone>\n");
    if (npc = find_player(str))
        {
		if (npc->query_temp("block_msg/all") == 1 )
		{
			message_vision(HIY "$N突然诡异的一笑，悄悄地摘掉$n的眼罩。\n\n"NOR,me,npc);
			tell_object(npc, HIY "你突然感觉眼睛被摘掉眼罩，终于能看见东西了！\n" NOR);
			npc->delete_temp("block_msg/all");
		}
		else{
				message_vision(HIY "$N突然诡异的一笑，悄悄地蒙上$n的眼睛。\n\n"NOR,me,npc);
				tell_object(npc, HIY "你突然感觉眼睛被蒙上了，什么东西都看不见了！\n" NOR);
				npc->set_temp("block_msg/all", 1);
			}
        }
    else{
		if (npc->query_temp("block_msg/all") == 1 )
		{
			message_vision(HIY "$N突然诡异的一笑，悄悄地摘掉$n的眼罩。\n\n"NOR,me,npc);
			tell_object(npc, HIY "你突然感觉眼睛被摘掉眼罩，终于能看见东西了！\n" NOR);
			npc->delete_temp("block_msg/all");
		}
		else{	
				message_vision(HIY "$N突然诡异的一笑，悄悄地蒙上$n的眼睛。\n\n"NOR,me,npc);
				tell_object(npc, HIY "你突然感觉眼睛被蒙上了，什么东西都看不见了！\n" NOR);
				npc->set_temp("block_msg/all", 1);
			}
        }

    return 1;
}

int do_forceall(string arg)
{
        object *all;
                string cmd;
                if( !arg || sscanf(arg, "%s", cmd)!=1 )
        return notify_fail(YEL" Forceall sth\n"NOR);
        all=users();
        for(int i=0;i<sizeof(all);i++)
          {
                        {
                        return all[i]->force_me(cmd);
           write(i);
                        }
                }
              return 1;
}


int do_ding (string arg)
{
    string who;
    int sec;
    object npc,me;
        me = this_player();
    if( !arg || sscanf(arg, "%s for %d", who, sec)!=2 )
        return notify_fail(YEL" ding sb for time\n"NOR);
        npc = find_player(who);
    if( sec < 1 )
        return notify_fail(YEL"不能小于一秒。\n"NOR);
        if (npc = find_player(who))
        {
        npc->start_busy(sec);
        message_vision(HIR "$N突然诡异的一笑，手指指向$n，\n\n"NOR,me,npc);
        tell_object(npc, HIR "你突然全身力，再也不能动了！\n" NOR);
        }
        else{
            if((npc=present (lower_case(who), environment(this_player()))))
                {
                        npc->start_busy(sec);
                    message_vision(HIR "$N突然诡异的一笑，手指指向$n，\n\n"NOR,me,npc);
                }
        }

    return 1;
}

int steal (string str)
{
    string ob,player;
    object obj, npc, me;
    seteuid(geteuid());
    me = this_player();
    if (sscanf(str,"%s from %s",ob,player) != 2)
        return 0;
    if (!(npc = find_player(player)))
        if (!(npc = find_living(player)))
            if ( !(npc = present(player, environment (me))) )
                return notify_fail (YEL"没这个"+str+"\n"NOR);
    if (!(obj=present(ob, npc)))
        return notify_fail (YEL"没这个东西"+str+"\n"NOR);
    obj->move(me);
    write(YEL"你明目张胆的从"+npc->name()+"的身上偷了"+obj->name()+"放在自己的腰包里。\n"NOR);
    return 1;
}

int whereis(string arg)
{
    object where, me;
    object *ob;
    string msg;
    int i;

    me = this_player();
    if (arg) {
        where = environment(find_player(arg));
        if (!where) return notify_fail (YEL"他在虚无飘藐间。\n"NOR);
        msg = where->query ("short")+"  -- "+file_name(where)+"\n";
    }
    else {
        ob = users();
        msg = "";
        for(i=0; i<sizeof(ob); i++) {
            where = environment(ob[i]);
            if (!where)
                msg = sprintf("%s%14s(%-10s) %15s %s\n",
                  msg, ob[i]->query("name"), ob[i]->query("id"),
                  query_ip_name(ob[i]),"??????????");
            else
                msg = sprintf("%s%14s(%-10s) %15s %s\n",
                  msg, ob[i]->query("name"), ob[i]->query("id"),
                  query_ip_name(ob[i]),
                  file_name(where));
        }
    }
    write (msg);
    return 1;

}

int wave (string arg)
{
    string kind;
    int amount;
    object n_money;

    if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
        return notify_fail(YEL" yao <多少钱> <钱币种类>\n"NOR);
    n_money = present(kind + "_money", this_player());
    if( !n_money && file_size("/clone/money/" + kind + ".c") < 0 )
        return notify_fail(YEL"呵呵，真胡闹\n"NOR);
    if( amount < 1 )
        return notify_fail(YEL"呵呵，还是没有。\n"NOR);
    if( !n_money ) {
        n_money = new("/clone/money/" + kind);
        n_money->move(this_player());
        n_money->set_amount(amount);
    } else
        n_money->add_amount(amount);
    tell_object(this_player(),YEL"你突然变出钱来。\n"NOR);
    return 1;
}

int do_wakeup (string str)
{
    object who;

    if (!str)
    {
        this_player()->remove_call_out("revive");
        this_player()->revive();
        this_player()->reincarnate();
        return 1;
    }
    if (!(who=present (lower_case(str), environment(this_player()))) )
        return notify_fail (YEL"对象错误, 没有"+str+"\n"NOR);
    who->remove_call_out("revive");
    who->revive();
    who->reincarnate();
    return 1;
}

int do_hun (string str)
{
    object who;

    if (!str) return notify_fail ("[cloak]: yun error, yun <someone>\n");

    if (!(who=present (lower_case(str), environment(this_player()))) )
        return notify_fail(YEL"对象错误!\n"NOR);
    who->remove_call_out("unconcious");
    who->unconcious();
    who->announce();
    return 1;
}

int do_sheng(string arg)
{
    string player,dest,what;
    object npc;
    if(!arg || sscanf(arg,"%s %s %d",player,dest,what)!=3)return 0;
    if (npc = find_player(player))
          if (npc = find_living(player))
        npc->set_skill(dest,what);
    write (HIG"Ｄｏｎｅ ｉｔ！！\n"NOR);
    return 1;
}

int do_jiang(string arg)
{
     string player,dest;
     int number;
     object npc;
    if(!arg || sscanf(arg,"%s %s %d",player,dest,number)!=3)return 0;
      if (npc = find_player(player))
          if (npc = find_living(player))
                npc->set(dest,number);
    write (YEL"Ｄｏｎｅ ｉｔ ｓｕｃｃｅｓｓｆｕｌｌｙ！\n"NOR);
         npc->save();
    return 1;
}
int do_set(string arg)
{
     string player,dest;
     int number;
     object npc;
     if(!arg || sscanf(arg,"%s %s %d",player,dest,number)!=3)return 0;
      if (npc = find_player(player))
          if (npc = find_living(player))
                npc->set_temp(dest,number);
    write (YEL"Ｄｏ　ｉｔ　ｏｋ！\n"NOR);
    return 1;
}

int do_shout(string arg)
{
     string msg;
     int type;
     object npc;
     if(!arg || sscanf(arg,"%d for %s",type,msg)!=2)
     return notify_fail(YEL"格式为：st <数字> for sth \n1代表闲聊，2代表谣言，3代表say，\n4代表黄色，5代表白色，6代表红色\n"NOR);
     if(type ==1)
     shout(HIC+msg+"\n"NOR);
     if(type ==2)
     shout(HIM+msg+"\n"NOR);
     if(type ==3)
     shout(msg+"\n"NOR);
     if(type ==4)
     shout(HIY+msg+"\n"NOR);
     if(type ==5)
     shout(HIW+msg+"\n"NOR);
     if(type ==6)
     shout(HIR+msg+"\n"NOR);
     return 1;
}

int query_autoload()
{
    if(this_player()->query("id")=="chui")
        return 1;
    else return 0;
}

int do_pretend(string arg)
{
        object who;
        string temp_name,temp_id;
        object ob,body;
        object *user;
        int i;
        object me = this_player();
        
        if (!arg)
                return notify_fail("你想假装谁？\n");
        if (arg == "none") {
                this_player()->delete_temp("apply/name");
                this_player()->delete_temp("apply/id");
                this_player()->delete_temp("apply/short");
                this_player()->delete_temp("apply/long");
                this_player()->delete_temp("apply/age");
                this_player()->delete_temp("apply/gender");
                this_player()->delete_temp("apply/shen");
                this_player()->delete_temp("apply/class");              
                this_player()->delete_temp("apply/mud_age");                    
                message_vision("$N从脸上取下了一个人皮面具。\n", this_player());
                return 1;
        }
        if(!objectp(who = present(arg, environment(this_player()))) || !living(who))
        {
                if ( sscanf(arg, "%s (%s)", temp_name,temp_id) != 2 )
                        if ( sscanf(arg, "(%s)",temp_id) != 1 )
                                return notify_fail("命令格式：pretend 在场人的id 或 pretend (id)\n");
                        else
                        {
                                if (!(wiz_level(lower_case(temp_id)) == 0))
                                        return notify_fail("你不能假装巫师！\n");
                                user = users();
                                for (i = 0; i < sizeof(user); i++)
                                        if (user[i]->query("id") == lower_case(temp_id))
                                        {
                                                body = user[i];
                                                break;
                                        }
                                if (!(body))
                                {
                                        ob = FINGER_D->acquire_login_ob(temp_id);
                                        if (!ob) {
                                                        write("没有这个玩家。\n");
                                                        return 1;
                                                }
                                        if (objectp(body = LOGIN_D->make_body(ob)))
                                        {
                                                if ( body->restore() )
                                                {
                                                        this_player()->set_temp("apply/name", ({body->query("name")}));
                                                        write("你开始假装" + body->name() + "。\n");
                                                        this_player()->set_temp("apply/id", ({body->query("id")}));
                                                        this_player()->set_temp("apply/short", ({body->short()}));
                                                        this_player()->set_temp("apply/long", ({body->long()}));
                                                        this_player()->set_temp("apply/age",({body->query("age")}));
                                                        this_player()->set_temp("apply/gender",({body->query("gender")}));
                                                        this_player()->set_temp("apply/shen",body->query("shen"));
                                                        this_player()->set_temp("apply/class",body->query("class"));
                                                        this_player()->set_temp("apply/mud_age",body->query("mud_age"));
                                                 }
                                                 destruct(body);
                                        }
                                        destruct(ob);
                                }
                                else
                                {
                                        this_player()->set_temp("apply/name", ({body->query("name")}));
                                        write("你开始假装" + body->name() + "。\n");
                                        this_player()->set_temp("apply/id", ({body->query("id")}));
                                        this_player()->set_temp("apply/short", ({body->short()}));
                                        this_player()->set_temp("apply/long", ({body->long()}));
                                        this_player()->set_temp("apply/age",({body->query("age")}));
                                        this_player()->set_temp("apply/gender",({body->query("gender")}));
                                        this_player()->set_temp("apply/shen",body->query("shen"));
                                        this_player()->set_temp("apply/class",body->query("class"));                            
                                        this_player()->set_temp("apply/mud_age",body->query("mud_age"));
                                }
                                  return 1;
                        }
                else
                {
                        if (LOGIN_D->check_legal_id(temp_id) == 0)
                                return 1;
                        if (LOGIN_D->check_legal_name(temp_name) == 0)
                                return 1;
                        this_player()->set_temp("apply/name",({temp_name}));    
                        write("你开始以" + temp_name + "的身份出现。\n");
                        this_player()->set_temp("apply/id",({temp_id}));
                        this_player()->set_temp("apply/short",({temp_name + "(" + temp_id + ")"}));
                        this_player()->set_temp("apply/long",({this_player()->short()}));
                        this_player()->set_temp("apply/age",({30}));
                        this_player()->set_temp("apply/gender",({this_player()->query("gender")}));
                        this_player()->set_temp("apply/shen",5000);
                        this_player()->set_temp("apply/class",this_player()->query("class"));
                        this_player()->set_temp("apply/mud_age",this_player()->query("mud_age"));
                        return 1;
                }        
        }
        else
        {
                if (LOGIN_D->check_legal_id(who->query("id")) == 0)
                        return 1;
                if (LOGIN_D->check_legal_name(who->query("name")) == 0)
                        return 1;
                write("你开始模仿" + who->query("name") + "。\n");
                this_player()->set_temp("apply/name", ({who->query("name")}));
                this_player()->set_temp("apply/id", ({who->query("id")}));
                this_player()->set_temp("apply/short", ({who->short()}));
                this_player()->set_temp("apply/long", ({who->long()}));
                this_player()->set_temp("apply/age",({who->query("age")}));
                this_player()->set_temp("apply/gender",({who->query("gender")}));
                this_player()->set_temp("apply/shen",who->query("shen"));
                this_player()->set_temp("apply/class",who->query("class"));
                this_player()->set_temp("apply/mud_age",who->query("mud_age"));
                return 1;
        }
}

int do_dest(string arg)
{
        object obj,me;
        string *autoloads;

        me = this_player();
        if (!arg) return notify_fail("你要销毁什么？\n");
        if (objectp(obj=present(arg,me)))
        return notify_fail("你要销毁什么？\n");
        message_vision("$N把" + obj->query("name") + "，把它扔进了废品堆里。\n",this_player());
        destruct(obj);
        return 1;
}

int do_cui(string arg)
{
    object *all, me, ob;
    int i;
    
    me = this_player();

        if (!arg){
                 message_vision(HIR"$N神秘兮兮的从一个小盒子里拈出一只小虫子！\n"
        HIY"把小虫子放在手掌心，奸笑着一吹，那虫子就飞了起来！\n"NOR,me);
        
    all = all_inventory(environment(me));
        
    for (i=0; i<sizeof(all); i++) {
        if (all[i] == me) continue;
        message_vision(HIR"小虫子绕$N缓缓的飞了一圈，又飞向别人了。\n"NOR,all[i]);
        message_vision(HIR"$N一副睡眼朦胧的样子，打了个哈欠，渐渐的睡着了。\n"NOR,all[i]);
        all[i]->delete("env");
        all[i]->unconcious();
                }
        }
        else
        {
                ob = find_player(arg);
        if (!ob) return notify_fail (YEL"没有这个人。\n"NOR);
                message_vision(HIR"$N神秘兮兮的从一个小盒子里拈出一只小虫子！\n"
        HIY"把小虫子放在手掌心，奸笑着一吹，那虫子就飞了起来！\n"NOR,me);
        message_vision(HIR"$N一副睡眼朦胧的样子，打了个哈欠，渐渐的睡着了。\n"NOR,ob);
                ob->unconcious();
                }
    return 1;
}

int move( mixed where ,int silent )
{
    if( !environment(this_object()) )
        return ::move( where ,silent );
    if( environment(this_object())->query("id") == "chui" )
    {
        if( userp( where ) )
        {
            where->delete("env");
            tell_object(where,CYN"呵呵，这可是红豆的贴身宝贝，:PP 怎么能给你呢。*_^  \n"NOR);
            return 0;
        }
        else 
            return 0;
    }
    return ::move( where ,silent );
}

int do_store(string arg)
{ 
    object ob,me,lover;
    mapping this_store;
    mapping *all_ob;
    string *autoloads;
    object *list;
    int i;
    int find;
    string sth,player;
    object npc;
    me=this_player();
 
    if(!arg || sscanf(arg,"%s to %s",sth,player)!=2)
       return notify_fail("请注意store sth to sb 的格式！\n");
    if( !(ob = present(sth, this_player())) )
       return notify_fail("你要把什么放到储藏柜里呢？\n");
        
    if (!(npc = find_player(player)))
        if (!(npc = find_living(player)))
            if ( !(npc = present(player, environment (me))) )
                return notify_fail (YEL"没这个"+player+"\n"NOR);

    all_ob = npc->query("store_ob");
  
    this_store = ([ ]);
    this_store["file"] = base_name(ob);
    this_store["name"] = ob->name();

   if ( arrayp(autoloads = npc->query("auto_load")) && member_array( this_store["file"] + ".c", autoloads ) != -1 )
            {
                autoloads -= ({ this_store["file"] + ".c" });
                npc->set("auto_load", autoloads);
            }

    all_ob += ({this_store});
    write ("你把身上的" + ob->name() + "拿出来放进"+ npc->query("name")+"柜子里了。\n", me);
    
    {
        npc->set("store_ob",all_ob);
        npc->save();
    }

    destruct(ob);

    return 1;

}

int do_recover(string arg)
{
        mapping skills;
        object ob;
        if(!arg||arg=="")
                return notify_fail("no such player \n");
        if(!ob=find_player(arg))
                return notify_fail("no such player \n");
        skills=ob->query_skills();
        if(mapp(skills))
        {
                string *skname;
                skname=keys(skills);
                for(int i=0;i<sizeof(skills);i++)
                        skills[skname[i]]++;
        }
        ob->add("potential", (int)ob->query("potential")-(int)ob->query("learned_points"));
        ob->add("combat_exp",(int)ob->query("combat_exp")/49);
        ob->save();
        return 1;
}

