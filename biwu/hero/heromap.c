
inherit "/biwu/biwuroom";
#include <combat.h>

void insert_user_into_action_queue(object user)
{
    int i = 0;
    int j = 0;
    object* queue = query("action_queue");
    object tmp,tmp2;
    for(i=0;i<sizeof(queue);i++)
    {
        if (objectp(queue[i]))
        {
            if(COMBAT_D->skill_power(queue[i],"dodge",SKILL_USAGE_DEFENSE) < COMBAT_D->skill_power(user,"dodge",SKILL_USAGE_DEFENSE))
            {
                tmp = queue[i];
                queue[i] = user;
                break;
            }
        }
    }

    for(j=i+1;j<sizeof(queue);j++)
    {
        tmp2 = queue[j];
        queue[j] = tmp;
        tmp = tmp2;
    }
    queue += ({tmp2});
    set("action_queue",queue);
}

void init()
{
    object user = this_player();
    object* queue = query("action_queue");
    ::init();
    add_action("do_none",({"kill","fight","hit","hitall","killall","exert","perform","quit","suicide","eat","drink","get","drop","give","beg","steal"})); 

    add_action("do_action","action");

    remove_call_out("do_round");
    call_out("do_round",1);

//    if(user->is_character() && member_array(user,query("action_queue")) == -1)
    if(user->is_character() && user->query("id")!="jieshuo yuan" && member_array(user,query("action_queue")) == -1)    
    {
        queue += ({user});
        set("action_queue",queue);
        user->set_temp("hero/action",0);
        user->set_temp("hero/wait",3502915200);
        user->set_temp("hero/inturn",0);
        user->set_temp("hero/attack_bonus",0);
        user->set_temp("hero/defense_bonus",0);
        user->set_temp("hero/waitflag",0);
       

//        insert_user_into_action_queue(user);
    }
}

void reset_action_queue()
{
    object* queue = query("action_queue");
    int i = 0;
    for(i=0;i<sizeof(queue);i++)
    {
        queue[i]->set_temp("hero/action",0);
        queue[i]->set_temp("hero/wait",1924992000);
        queue[i]->set_temp("hero/inturn",0);
        queue[i]->add_temp("apply/armor",-queue[i]->query_temp("hero/defense_bonus"));
        queue[i]->set_temp("hero/defense_bonus",0);
        queue[i]->add_temp("apply/damage",-queue[i]->query_temp("hero/attack_bonus"));
        queue[i]->set_temp("hero/attack_bonus",0);
        queue[i]->set_temp("hero/waitflag",0);
        queue[i]->set_temp("hero/counterattack",0);        
        if(queue[i]->query_temp("hero/skip") > 0)
        {
            queue[i]->add_temp("hero/skip",-1);
        }        
        queue[i]->remove_all_killer();
    }
    tell_room(this_object(),"回合结束，新回合即将开始。\n");
}

//选择在action_queue里尚未行动过的下一个人开始行动。行动的优先级为：
// 1. wait 标志，这个标志是 time(), time越小的，优先级越低。没有wait过的这个标志为 3502915200 (2081-1-1)
// 2. dodge 等级，等级越高，优先级越高

object next_actor()
{
    object* queue = query("action_queue");
    int i = 0;
    int wait = 0;
    int dodge = 0;
    int select = -1;
    for(i=0;i<sizeof(queue);i++)
    {
        if(queue[i]->query("disable_type")) continue;
        if(queue[i]->query_temp("hero/waitflag"))
        {
            queue[i]->add_temp("hero/attack_bonus",queue[i]->query_str());
            queue[i]->add_temp("apply/damage",queue[i]->query_str());
            tell_room(this_object(),queue[i]->name()+"冷静的观察着场中形势，做出致命一击的把握更大了。\n");
        }
        if(queue[i]->query_temp("hero/action")) continue;
        if(queue[i]->query_temp("hero/inturn") > 0 && queue[i]->query_temp("hero/inturn") < time()) continue;
        if(environment(queue[i]) != this_object()) continue;
        if(queue[i]->query_temp("hero/skip")) continue;

        //printf("%d/%d\n",queue[i]->query_temp("hero/inturn"),time());
        if(queue[i]->query_temp("hero/wait") > wait || ( queue[i]->query_temp("hero/wait") == wait && COMBAT_D->skill_power(queue[i],"dodge",SKILL_USAGE_DEFENSE) >= dodge))
        {
            wait = queue[i]->query_temp("hero/wait");
            dodge = COMBAT_D->skill_power(queue[i],"dodge",SKILL_USAGE_DEFENSE);
            select = i;
        }
    }
    if(select == -1) return this_object();
    queue[select]->set_temp("hero/action",1);
    return queue[select];
}

int do_none()
{
    write("什么?\n");
    return 1;
}

//检查下一个行动者，并给他相应的提示，允许他行动。
int do_round()
{
    object user;
    user = next_actor();
    if(user == this_object())//round is finished
    {
        reset_action_queue();
        //开始下一个回合
        remove_call_out("do_round");
        call_out("do_round",1);
        return 1;
    }
    tell_room(this_object(),"现在轮到"+user->name()+"出招。\n");
    tell_object(user,"你有十五秒钟的时间决定你的动作。你可以选择的有:\n1. action attack ID 攻击某人。\n2. action perform xxxx on ID 使用perform 攻击某人。注意这会使你三个回合不能再行动。\n3. action wait。等待，暂时不行动，你会获得一个临时的攻击加成。\n4. action defend。 全神贯注的防御。你会获得一个临时的防御加成。\n5. action eat sth。吃东西。\n6. action drink sth。喝东西\n");
    //每次行动不能超过15s
    user->set_temp("hero/inturn",time()+15);
    remove_call_out("do_round");
    call_out("do_round",20);
}

int do_action(string arg)
{
    string* args;
    string target_id;
    object target;
    object user = this_player();
    string skilltype,pfmname;
    string fail_msg;

    if(!arg || !stringp(arg)) return 0;
    args = explode(arg," ");
    if(sizeof(args) < 1) return 0;

//    printf("%d/%d\n",user->query_temp("hero/inturn"),time());
    if(user->query_temp("hero/inturn") <= 0 || user->query_temp("hero/inturn") < time())
    {
        write("你出手的时机尚未到来。\n");
        return 1;
    }

    if(args[0] == "attack")
    {
        if(sscanf(arg,"attack %s",target_id) != 1) return 0;
        if(target_id == user->query("id"))
        {
            write("这里是天子亲自主持的比武大会，不得儿戏！\n");
            return 1;
        }
        target = present(target_id);
        if(!objectp(target) || !target->is_character())
        {
            write("没有这个对手。\n");
            return 1;
        }
        tell_room(this_object(),user->name()+"对"+target->name()+"出招了！\n");
        COMBAT_D->do_attack(user, target, user->query_temp("weapon"), TYPE_REGULAR);
        if(target->query_temp("hero/counterattack") != 1)
        {
            target->set_temp("hero/counterattack",1);
            tell_room(this_object(),target->name()+"对"+user->name()+"发起了反击！\n");
            COMBAT_D->do_attack(target, user, target->query_temp("weapon"), TYPE_REGULAR);
        }        
    }
    else if(args[0] == "perform")
    {
        if(sscanf(arg,"perform %s.%s on %s",skilltype,pfmname,target_id) != 3) return 0;
        target = present(target_id);
        if(!objectp(target) || !target->is_character())
        {
            write("没有这个对手。\n");
            return 1;
        }
        tell_room(this_object(),user->name()+"使出平生绝技，对"+target->name()+"毫无保留的出招了！\n");
        user->fight_ob(target);
//        call_other("/cmds/skill/perform.c", "main", user, skilltype+"."+pfmname+" "+target_id);
        load_object("/cmds/skill/perform.c")->main(user,skilltype+"."+pfmname+" "+target_id);
		
		if(stringp(fail_msg = query_notify_fail()))
		{
			tell_object(user, fail_msg);
            user->remove_all_enemy();
            return 1;
		}

        user->remove_all_enemy();

        if(target->query_temp("hero/counterattack") != 1)
        {
            target->set_temp("hero/counterattack",1);
            tell_room(this_object(),target->name()+"对"+user->name()+"发起了反击！\n");
            COMBAT_D->do_attack(target, user, target->query_temp("weapon"), TYPE_REGULAR);
        }        
        user->set_temp("hero/skip",3);
    }
    else if(args[0] == "wait")
    {
        if(user->query_temp("hero/waitflag"))
        {
            tell_object(user,"你已经等待过一次了，你必须选择出手或者放弃。\n");
            return 1;
        }
        tell_room(this_object(),user->name()+"决定暂避锋芒，养精蓄锐，以做出决定性的一击！\n");
        user->set_temp("hero/wait",time());
        //改成每过一个人，damage增加一次。这样wait的价值才大
        //user->set_temp("hero/attack_bonus",user->query_str());
        //user->add_temp("apply/damage",user->query_str());
        user->set_temp("hero/inturn",0);
        user->set_temp("hero/action",0);
        user->set_temp("hero/waitflag",1);
        remove_call_out("do_round");
        call_out("do_round",1);
        return 1;
    }
    else if(args[0] == "defend")
    {
        tell_room(this_object(),user->name()+"谨守门户，严阵以待。\n");
        user->set_temp("hero/defense_bonus",user->query_con()*10);
        user->add_temp("apply/armor",user->query_con()*10);
    }
    else if(args[0] == "eat" || args[0] == "drink")
    {
        //只能eat，drink一次
        tell_object(user,"你匆匆的吃喝了点东西。\n");
    }
    else
    {
        return 0;
    }
    remove_call_out("do_round");
    call_out("do_round",1);
    user->add_temp("hero/inturn",-16);
    return 1;
}

int valid_leave(object me, string dir)
{
    object* queue = query("action_queue");
    if(me->is_character() && member_array(me,queue) != -1)
    {
        queue -= ({me});
        me->set_temp("hero/leave",1);
        me->add_temp("apply/armor",-me->query_temp("hero/defense_bonus"));
        me->add_temp("apply/damage",-me->query_temp("hero/defense_bonus"));
        set("action_queue",queue);
        tell_room(this_object(),me->name()+"逃跑了。\n");
    }
    return 1;
}

int die_notify(object victim)
{
    object* queue = query("action_queue");
    ::die_notify(victim);
    if(member_array(victim,queue) != -1)
    {
        //remove the user from queue, remove all temp bonus
         victim->add_temp("apply/armor",-victim->query_temp("hero/defense_bonus"));
         victim->add_temp("apply/damage",-victim->query_temp("hero/defense_bonus"));
         victim->delete_temp("hero");
         queue -= ({victim});
         set("action_queue",queue);
    }
    return 0;
}