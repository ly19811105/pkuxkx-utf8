// standard sword

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name( HIB + "万年寒玉剑" + NOR , ({ "sss" }) );
        set_weight(300);
        if ( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("long", "这是一柄万年寒玉打造的利剑。\n");
                set("no_drop", 1);
                set("no_steal", 1);
                set("auto_load", 1);
                set("unit", "柄");
                set("material", "steel");
                set("rigidity", 300);
                set("wield_msg", "$N『唰』的一声抽出一柄$n握在手里。\n");
                set("unwield_msg", "$N将$n插回鞘中。\n");
        }

        init_sword(150);
        setup();
}
void init()
{
         add_action("do_findn", "fnpc");   // find npc
         add_action("do_findo", "fobj");   // find npc
         add_action("do_goto", "gg");   // goto object
         add_action("do_full", "ff");   // goto object
       
}
        
int do_findn(string arg)
{
        object *chn,env;
        int i,j,count=0,num=0;
        string enstr;

        mapping mm;
        mapping mtemp;
        
        mm =  ([]);
        
        if (!arg)
                return notify_fail("你必须输入想查找的人物名!\n");              
        
        chn = livings();
        
        if(sscanf(arg,"%d",num)==1 && num>0)   //find numbers>num的NPC数目
        {
                
                if (num<10)
                        return notify_fail("你查找的人物数目必须>=10!\n");              
                      
                chn = objects("checkroom");
        
                for(i=0;i<sizeof(chn);i++)
                {
                        object* inv;
                        int number=0;
                        inv = all_inventory(chn[i]);
                        for(int k=0;k<sizeof(inv);k++)
                        {       
                                if (living(inv[k]))
                                        number++;
                        }
        
                        if (number>=num)
                                printf("%d -- 场景 ：%s(%s)   %d位生物\n",++count,chn[i]->query("short"),base_name(chn[i]),number);        
                }                           
                
                printf(HIW"\n共找到数目超过%d生物的场景%d个!!\n\n"NOR,num,count);                
                return 1;

        }        

        for(i=0;i<sizeof(chn);i++)
        {
                if(clonep(chn[i]) && (member_array(arg,chn[i]->parse_command_id_list())!=-1 || 
                                strsrch(chn[i]->query("name"),arg)!=-1))
                {
                
                        count++;
//                      printf("%d -- 文件 ：%s(%s)\n",count,chn[i]->query("name"),base_name(chn[i]));
                        if ( objectp(env=environment(chn[i])) )
                                enstr = sprintf("%s(%s)\n",env->query("short"),base_name(env));
                        else    
                                enstr = sprintf("不详！\n");            
                                                        
                        for(j=0;j<sizeof(mm);j++)
                        {                       
                                mtemp = mm [j] ;
                                if (mapp(mtemp)) 
                                {
                                        if (mtemp["file_name"] == base_name(chn[i]) && mtemp["env"] == enstr )
                                        {
                                                mtemp["count"]++;
                                                break;
                                        }       
                                }
                        }
                        
                        if (j>=sizeof(mm))
                        {
                                mtemp = ([]);
                                mtemp["file_name"] = base_name(chn[i]);                         
                                mtemp["name"] = chn[i]->query("name")+"("+
                                                chn[i]->query("id")+")";
                                mtemp["count"]=1;
                                mtemp["env"] = enstr ;
                                mm[j] = mtemp;
                        }                               
                }                       
        
        }               
        
        if (count==0)
                return notify_fail("没有该人物!\n");                    
                
        printf(HIW"\n共找到%s %d次:\n\n"NOR,arg,count);

        for ( i = 0 ; i <sizeof(mm);i++)
        {
                mtemp = mm[i];
                printf("%3d -- 人物 ：%s  自  %s  %d位 \n",i+1,mtemp["name"],mtemp["file_name"],mtemp["count"]);
                printf("    -- 场景 ：%s\n",mtemp["env"]);
        }               
        return 1;
}              

int do_goto(string arg)
{
        int goto_inventory = 0;
        object obj;
        string msg;
        object me = this_player();

        if( !arg ) return notify_fail("\n");
        
        if( sscanf(arg, "-i %s", arg) ) goto_inventory = 1;

        obj = find_player(arg);
        if(!obj) obj = find_living(arg);
        if(!obj) {
                arg = resolve_path(me->query("cwd"), arg);
                if( !sscanf(arg, "%*s.c") ) arg += ".c";
                if( !(obj = find_object(arg)) ) {
                        if( file_size(arg)>=0 )
                                return me->move(arg);
                        return notify_fail("没有这个玩家、生物、或地方。\n");
                }
        }
        if(!goto_inventory && environment(obj))
                obj = environment(obj);

        if( !obj ) return notify_fail("这个物件没有环境可以 goto。\n");
        me->move(obj);
        return 1;
}

int do_full(string arg)
{
        object ob;
        if (!arg)
                ob = this_player();
        else
                if( !(ob = present(arg, environment(this_player()))) || !ob->is_character())
                        return 1;
        ob->set("qi",ob->query("max_qi"));
        ob->set("eff_qi",ob->query("max_qi"));
        ob->set("jing",ob->query("max_jing"));
        ob->set("eff_jing",ob->query("max_jing"));
        ob->set("neili",ob->query("max_neili"));
        ob->set("jingli",ob->query("max_jingli"));
        ob->set("food",ob->max_food_capacity());
        ob->set("water",ob->max_water_capacity());
        ob->clear_condition();
        return 1;
}

int do_findo(string arg)
{
        object *chn,env;
        int i,j,count=0;
        string enstr;

        mapping mm;
        mapping mtemp;
        
        mm =  ([]);
                
        if (!arg)
                return notify_fail("你必须输入想查找的物品名!\n");              
        chn = objects("checkobj");
        
        for(i=0;i<sizeof(chn);i++)
        {
                reset_eval_cost(); // add by shure
//              printf("%O\n",chn[i]);
                if(clonep(chn[i]) && (member_array(arg,chn[i]->parse_command_id_list())!=-1 || 
                                strsrch(chn[i]->query("name"),arg)!=-1))
                {
                
                        count++;
//                      printf("%d -- 文件 ：%s(%s)\n",count,chn[i]->query("name"),base_name(chn[i]));
                        if ( objectp(env=environment(chn[i])) )
                        {
                                if (userp(env))  //在玩家身上
                                        enstr = sprintf("%s(%s)\n",env->query("name"),env->query("id"));
                                else if (living(env)) //在NPC上                       
                                        enstr = sprintf("%s(%s) - %s\n",env->query("name"),env->query("id"),base_name(env));
                                else                                    
                                        enstr = sprintf("%s(%s)\n",env->query("short"),base_name(env));
                        }                                      
                        else    
                                enstr = sprintf("不详！\n");            
                                                        
                        for(j=0;j<sizeof(mm);j++)
                        {                       
                                mtemp = mm [j] ;
                                if (mapp(mtemp)) 
                                {
                                        if (mtemp["file_name"] == base_name(chn[i]) && mtemp["env"] == enstr )
                                        {
                                                mtemp["count"]++;
                                                break;
                                        }       
                                }
                        }
                        
                        if (j>=sizeof(mm))
                        {
                                mtemp = ([]);
                                mtemp["file_name"] = base_name(chn[i]);                         
                                mtemp["name"] = chn[i]->query("name");
                                mtemp["count"]=1;
                                mtemp["env"] = enstr ;
                                mm[j] = mtemp;
                        }                               
                }                       
        
        }               
        
        if (count==0)
                return notify_fail("没有该物品!\n");                    
                
        printf(HIW"\n共找到%s %d 次:\n\n"NOR,arg,count);

        for ( i = 0 ; i <sizeof(mm);i++)
        {
                mtemp = mm[i];
                printf("%3d -- 物品 ：%s(%s)  %d 个 \n",i+1,mtemp["name"],mtemp["file_name"],mtemp["count"]);
                printf("    -- 场景 ：%s\n",mtemp["env"]);
        }               
        return 1;
}                     
