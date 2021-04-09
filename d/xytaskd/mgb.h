#include "xytaskd.h"
int des();
void create()
{
    
    int bts=join_bts(0), hour=now_hour();
    
    if ( bts>=5 )
    set_name(HIM"蒙古兵"NOR, ({
        "menggu bing", "bing"
    }
    ));
    else
    set_name("蒙古兵", ({
        "menggu bing", "bing"
    }
    ));
    
    set("age", 22);
    set("no_clean_up", 1);
    set("max_qi", 3500);
    set("eff_qi",3500);
    set("qi",3500+random(1500));
    set("max_jing", 800);
    set("menggu", 1);
    set("gender", "男性");
    set("long", "一个身穿铁甲的蒙古兵。\n");
    set("attitude", "aggressive");
    
    set("str", 24);
    set("dex", 16);
    set("shen_type", -1);
    //当有5个以上BT参与保卫的时候蒙古兵难度变高
    if ( bts>=5 )
    {
        
        set("combat_exp", (5000+random(2000))*10000);
        set_skill("unarmed", 600);
        set_skill("dodge", 700);
        set_skill("parry", 700);
        set_skill("blade", 650);
        set_skill("force", 650);
        set_temp("apply/attack", 350);
        set_temp("apply/defense", 680);
        set_temp("apply/damage", 250);
        set_temp("apply/armor", 680);
        
    }
    
    else
    {
        
        set("combat_exp", 100000+random(300000));
        set_skill("unarmed", 40);
        set_skill("dodge", 140);
        set_skill("parry", 140);
        set_skill("blade", 60);
        set_skill("force", 60);
        set_temp("apply/attack", 120);
        set_temp("apply/defense", 340);
        set_temp("apply/damage", 120);
        set_temp("apply/armor",240);
        
    }
    
    
    set("chat_chance_combat", 10);
    set("chat_msg_combat", ({
        
        "冲啊.......\n",
        "杀啊.......\n",
        
    }));
	//不能搬运，以免引起mgb_number的错误
	set("no_get",1);
    setup();
    carry_object("/clone/weapon/gangdao")->wield();
    remove_call_out("start_move");
    call_out("start_move",1);
    carry_object("/clone/armor/tiejia")->wear();
    set("index",0);
    remove_call_out("des");
    call_out("des",1800);
    
}


void init()
{
    
    add_action("do_yun","yun");
    add_action("do_kill","kill");
    add_action("do_yun","exert");
    
    return ;
    
}

int start_move()
{
    
    remove_call_out("do_move");
    call_out("do_move", 1);
    return 1;
    
}

int do_move()
{
    
    object room,me,obj,bing,*inv;
    int i,menggu_number;
    me=this_player();
    bing=this_object();
    if(query("victory"))
    {
        des();
        return 1;
        
    }
    
    if(spot[query("index")]=="HALT")
    {
        
        if (query("victory"))
        des();
        remove_call_out("do_move");
        call_out("do_move", 3);
        return 1;
        
    }
    
    if(bing->is_fighting())
    {
        
        if (random(3) == 0)
        {
            
            bing->remove_all_killer();
            bing->remove_all_enemy();
            
        }
        
        remove_call_out("do_move");
        call_out("do_move", 3);
        return 1;
        
    }
    
    if(!living(bing))
    {
        
        remove_call_out("do_move");
        call_out("do_move", 3);
        return 1;
        
    }
    
    if (!environment(bing)) return 1;
    if (environment(bing)->query("xytaskd/gongshi"))
    {
        
        message("vision",HIG+ query("name") + "被工事阻挡，进攻的速度缓了一缓。\n"+NOR,environment(bing));
        environment(bing)->add("xytaskd/gongshi",-1);
        if (environment(bing)->query("xytaskd/gongshi") == 0)
        message("vision",HIR"修筑的工事在" + query("name") + "的再三冲击下『轰隆』一声垮掉了！\n"NOR,environment(bing));
        remove_call_out("do_move");
        call_out("do_move", 3);
        return 1;
        
    }
    
    message("vision",HIR"杀呀，冲啊....."+query("name")+HIR"往前冲去！\n"NOR,environment(bing));
    room=load_object(spot[query("index")]);
	environment()->add("mgb_number",-1);
	if(environment()->query("mgb_number") < 0)
	{
		environment()->set("mgb_number",0);
	}
    bing->move(room);
	//以防房间的标记有以前的残留，确保从0开始.因为所有的mgb一定会调用destruct，所以不存在残留>0的mgb_number的情况
	if(room->query("mgb_number") < 0)
	{
		room->set("mgb_number",0);
	}

	room->add("mgb_number",1);
    message("vision",HIR"杀呀，冲啊.....一个"+query("name")+HIR"冲了过来！\n"NOR,environment(bing));
    if(room->query("shuaifu"))
    {
        menggu_number = query("mgb_number");
		menggu_number += room->query("destroy");

        
        if(menggu_number>40)  //失败判据
        {
            
            object xytaskd;
            xytaskd=load_object("/adm/daemons/xytaskd.c");
            xytaskd->set("begin",0);
            xytaskd->set("victory",0);
            //任务失败
            room->set("shuaifu",0);

            
            CHANNEL_D->do_channel(this_object(), "bd", HIR + "郭靖夫妇由于寡不敌众战死杀场！帅府被占，襄阳沦陷！" NOR, -1);
            if(!room->query("occupied"))
            {
                
                object task;
                room->set("long",@LONG
这里遭受蒙古兵的洗劫后，已经惨不忍睹。尸横遍野，往日的景象已经荡然无存....
LONG);
                (task=load_object("/adm/daemons/xytaskd.c"))->add("xyoccupied",1);
                if (task->query("xyoccupied")>30)
                CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳岌岌可危！" NOR, -1);
                else if(task->query("xyoccupied")>20)
                CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳现在已尸横遍野！" NOR, -1);
                else if(task->query("xyoccupied")>10)
                CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳大乱！" NOR, -1);
                else if(task->query("xyoccupied")>5)
                CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳军情堪忧！" NOR, -1);
                else
                {
                    
                }
                
                switch (random(5)){
                    
                    case 0:
                    CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳某处陷入一片火海之中......" NOR, -1);
                    break;
                    case 1:
                    CHANNEL_D->do_channel(this_object(), "bd", MAG + "蒙古兵在襄阳某处烧杀抢掠无恶不作......" NOR, -1);
                    break;
                    case 2:
                    CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳的"+room->query("short")+MAG+"被鞑子夷为平地....." NOR, -1);
                    break;
                    case 3:
                    CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳某处死伤严重......" NOR, -1);
                    break ;
                    case 4:
                    CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳某处已成一片废墟......" NOR, -1);
                    break ;
                    
                }
                
                
            }
            
            room->set("occupied",1);
            
        }
        
        return 1;
        
    }
    
    if(!room->query("occupied"))
    {
        
        object task;
        room->set("long",@LONG
这里遭受蒙古兵的洗劫后，已经惨不忍睹。尸横遍野，往日的景象已经荡然无存....
LONG
        );
        (task=load_object("/adm/daemons/xytaskd.c"))->add("xyoccupied",1);
        if (task->query("xyoccupied")>30)
        CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳岌岌可危！" NOR, -1);
        else if(task->query("xyoccupied")>20)
        CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳现在已尸横遍野！" NOR, -1);
        else if(task->query("xyoccupied")>10)
        CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳大乱！" NOR, -1);
        else if(task->query("xyoccupied")>5)
        CHANNEL_D->do_channel(this_object(), "bd", HIR + "襄阳军情堪忧！" NOR, -1);
        else
        {
            
        }
        
        switch (random(5)){
            
            case 0:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳某处陷入一片火海之中......" NOR, -1);
            break;
            case 1:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "蒙古兵在襄阳某处烧杀抢掠无恶不作......" NOR, -1);
            break;
            case 2:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳的"+room->query("short")+MAG+"被鞑子夷为平地....." NOR, -1);
            break;
            case 3:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳某处死伤严重......" NOR, -1);
            break ;
            case 4:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "襄阳某处已成一片废墟......" NOR, -1);
            break ;
            
        }
        
        
    }
    
    room->set("occupied",1);
    add("index",1);
    
    if(!room->query("gate"))
    {
        
        remove_call_out("do_move");
        call_out("do_move", random(SPEED)); 
    }
    
    else
    {
        
        remove_call_out("do_judge");
        call_out("do_judge",1,room);
        
    }
    
    return 1;
    
}

int do_judge(object room)
{
    
    int menggu_number;
    object obj,*inv;
    int i;
    if (!room->query("gate"))
    {
        
        remove_call_out("do_move");
        call_out("do_move", random(10));
        return 1;
        
    }
    
	menggu_number = room->query("mgb_number");
    menggu_number+=room->query("destroy");
    if(menggu_number<GATE_BREAK)
    {
        
        remove_call_out("do_judge");
        call_out("do_judge",1,room);
        return 1;
        
    }
    
    else
    {
        
        room->set("gate",0);
        remove_call_out("do_move");
        call_out("do_move", 1);
        message_vision(HIR"蒙古兵破门而入！\n"NOR,this_object());
        // 沦陷
        switch (random(5)){
            
            case 0:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "只听“轰～～～～”的一声，蒙古兵用圆木将"+room->query("short")+"的城门顶开！" NOR, -1);
            break;
            case 1:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "蒙古兵登上云梯将"+room->query("short")+"的守军杀退！" NOR, -1);
            break;
            case 2:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + "蒙古兵越战越勇，终于强攻下"+room->query("short")+"！" NOR, -1);
            break;
            case 3:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + room->query("short")+"的守军终于抵挡不住蒙古兵如潮水般的攻势，被蒙古攻城兵击溃！" NOR, -1);
            break;
            case 4:
            CHANNEL_D->do_channel(this_object(), "bd", MAG + room->query("short")+"漫天都是蒙古如雨般的火箭！襄阳守军死伤者众！" NOR, -1);
            break;
            
        }
        
        
        
        CHANNEL_D->do_channel(this_object(), "bd", HIR + room->query("short") + "沦陷！" NOR, -1);
        (load_object("/adm/daemons/xytaskd.c"))->add("occupied",1);
        (load_object("/adm/daemons/xytaskd.c"))->set(GATE,1);
        return 1;
        
    }
    
    
}

int do_kill(string arg)
{
    
    if(sizeof(this_player()->query_enemy())>10)
    {
        
        tell_object(this_player(),HIW"你对付的人够多了！\n"NOR);
        return 1;
        
    }
    
    return 0;
    
}

int do_yun()
{
    
    tell_object(this_player(),"你想运用内功御敌，怎奈蒙古兵实在太多，你竟然无法使出!!\n");
    return 1;
    
}


int die()
{
    
    object me,xytaskd;
    if(query("victory"))
    {
        
        message_vision(this_object()->query("name")+"死了\n",this_object());
        des();
        return 1;
        
    }
    
    me=this_object()->get_damage_origin_object();
    //if(!me) me=offensive_target(this_object());
    if(!me) me=this_player();
    xytaskd=load_object("/adm/daemons/xytaskd.c");

    if(query("taskid")!=me->query_temp("xytaskd/taskid"))
    {
        
        //    me->delete_temp("xytaskd");
        me->set_temp("xytaskd/taskid",xytaskd->query("taskid"));
        
    }
    
    me->add_temp("xytaskd/number",1);
    //::die();
    message_vision(this_object()->query("name")+"死了\n",this_object());
    if(random(10)==0&&me)
    {
        
        if(me->query("qi")>=me->query("max_qi"))
        {
            
            switch(random(6)){
                
                case 0:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳杀敌让敌人闻风丧胆!" NOR, -1);
                break;
                case 1:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳取敌首级如探囊取物!" NOR, -1);
                break;
                case 2:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳中战功赫赫!" NOR, -1);
                break;
                case 3:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳中独当一面!" NOR, -1);
                break;
                case 4:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳杀敌锐不可当!" NOR, -1);
                break;
                case 5:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳杀敌数以万计!" NOR, -1);
                break;
                default :
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳有万夫不当之勇!" NOR, -1);
                
            }
            
            
        }
        
        else if(me->query("qi")>=me->query("max_qi")/4*3)
        {
            
            switch(random(3)){
                
                case 0:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳杀敌勇猛无比!" NOR, -1);
                break;
                case 1:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳以一敌十!" NOR, -1);
                break;
                default :
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳打败敌军!" NOR, -1);
                
            }
            
            
        }
        
        else if(me->query("qi")>=me->query("max_qi")/2)
        {
            
            switch(random(3)){
                
                case 0:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳杀敌战袍都染红了!" NOR, -1);
                break;
                case 1:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳杀敌无数!" NOR, -1);
                break;
                default:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳誓死卫国，力拒敌兵!" NOR, -1);
                
            }
            
            
        }
        
        else
        {
            
            switch(random(3)){
                
                case 0:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳带伤杀敌，令人敬佩!" NOR, -1);
                break;
                case 1:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说"+me->query("name")+HIM"在襄阳置生死于度外，杀敌无数!" NOR, -1);
                break;
                default:
                CHANNEL_D->do_channel(this_object(), "bd", HIM + "据说已经分不清楚"+me->query("name")+HIM"脸上那些血是自己的，那些血是敌人的了!" NOR, -1);
                
            }
            
            
        }
        
        
    }
    
    des();
    return 1;
    
}

int des()
{
    destruct(this_object());
    return 1;
    
}

void pre_destruct()
{
    if(objectp(environment()))
	{
		environment()->add("mgb_number",-1);
	}
	return ::pre_destruct();
}