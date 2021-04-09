//create by unkown for pkuxkx
//沼泽地，主要特性:
//轻功不足者无法通行
//可能陷入沼泽，不能动，并且损血
//有野兽攻击，根据等级强度不同
//杀死野兽有奖励
inherit ROOM;

void create()
{
    set("no_die",1);
}

int sink()
{       
    object ob;
    object* allob = all_inventory(this_object());
    int dodgelevel = 0;
    string skill;
    int level = query("level");
        
    for(int i=0;i<sizeof(allob);i++)
    {    
        if(!objectp(allob[i])) continue;
        ob = allob[i];            
        if(ob->query("jiaofei/maze/monster")) continue;
        if(!living(ob)) continue;
                      
        if(ob->query_temp("jiaofei/maze/sinking"))
        {
            //已经陷入的
            if(random(5) > 3)
            {
                message_vision("$N痛苦的挣扎了一下，陷的更深了。\n",ob);
                ob->add_temp("jiaofei/maze/sinking",1);
                if(ob->query_temp("jiaofei/maze/sinking") > 50)
                {
                    ob->set_temp("jiaofei/maze/sinking",50);
                }
            }
        }
        else
        {
            //尚未陷入的
            //判断条件，轻功等级，是否带有大木板                        			
			dodgelevel = ob->query_skill("dodge");
			
            if(random(level*20) > random((dodgelevel - 100)))
            {
                if(present("da muban",ob) && random(3) == 2)
                {
                    //有木板，概率1/3
                    continue;
                }
                message_vision("$N突然觉得脚下一沉，身体不由自主地往下坠。\n",ob);
                ob->set_temp("jiaofei/maze/sinking",1);
            }             
        }
        if(ob->query_temp("jiaofei/maze/sinking"))
        {
            //消耗气血精神
            message_vision("$N被污泥中的瘴气熏得头昏眼花。\n",ob);
            ob->receive_damage("qi",level*100+ob->query_temp("jiaofei/maze/sinking")*10,"被瘴气熏");
            ob->add("neili",-level*100);   
            if(ob->query("neili") < 0)
            {
                ob->set("neili",0);
            }       
            if(ob->query("qi") < 0)
            {
                ob->die();
                ob->delete_temp("jiaofei/maze/sinking");
            }
        }
    }
    remove_call_out("sink");
    call_out("sink",10);    
    return 1;    
}

void create_monster()
{

    //数量为random(level)+1个
    int level = query("level");
    int number = random(level)+1;
    for(int i=0;i<number;i++)
    {
        object mon = new(__DIR__"npc/monster.c");
        mon->set("level",level);
        mon->init_me();        
        mon->move(this_object());
    }    
}

void init_maze()
{
    int x,y;
    //根据x,y坐标计算出强度，进而生成野兽
    x = query("maze/x")+1;
    y = query("maze/y")+1;
    //因为迷宫是从东向西的，所以x越大，等级越高，y无视
    set("level",random(x)+1);
    
    create_monster();
    
    set("max_user",random(10) + 1);
    
    //启动陷入沼泽的call_out
    remove_call_out("sink");
    call_out("sink",10);
    
}

int valid_leave(object me,string dir)
{
    if(me->query_temp("jiaofei/maze/sinking") != 0)
    {
        return notify_fail("你陷进了沼泽中，拔不出脚来。快找人来拉你一把吧！(pull)\n");
    }
    
    if(objectp(present("monster",this_object())))
    {
        tell_object(me,"你趁着眼前的野兽不注意，赶紧开溜，一不小心摔了一跤。\n");
		me->add_busy(3);
    }
    return ::valid_leave(me,dir);
}

int do_pull(string arg)
{
    object me = this_player();
        
    object target;
    
    int i = random(100);
    
    if(!arg) return 0;
        
    target = present(arg,this_object());        
    
    if(!objectp(target) || target->query_temp("jiaofei/maze/sinking") == 0 || me->query_temp("jiaofei/maze/sinking") != 0)
    {
        return notify_fail("照顾好自己吧，别人用不着你来救！\n");
    }
    if(target == me)
    {
        return notify_fail("拉你自己？你是项羽吗?\n");
    }
    
    if(i<88)
    {
        //救出来
        message_vision(sprintf("$N伸手把%s从沼泽里拉了上来。\n",target->query("name")),me);
        me->start_busy(1);
        target->start_busy(1);
        target->delete_temp("jiaofei/maze/sinking");
    }
    else if(i<93)
    {
        //救出来，但是自己进去            
        message_vision(sprintf("$N伸手把%s从沼泽里拉了上来，但是用力过猛，反而把自己陷进去了。\n",target->query("name")),me);            
        target->start_busy(1);
        target->delete_temp("jiaofei/maze/sinking");
        me->set_temp("jiaofei/maze/sinking",1);
    }           
    else if(i<98)
    {
        //失败，自己没事
        message_vision(sprintf("$N伸手想把%s从沼泽里拉上来，但是手一滑，没有成功。\n",target->query("name")),me);            
        me->start_busy(1);            
    }        
    else
    {
        message_vision(sprintf("$N伸手想把%s从沼泽里拉上来，但是手一滑，没有成功，自己反倒陷了进去。\n",target->query("name")),me);                        
        me->set_temp("jiaofei/maze/sinking",1);
    }         
         

    return 1;
}

void init()
{
    add_action("do_pull","pull");
}

