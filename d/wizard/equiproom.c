#define MAX_SIZE_WEAPON 20
inherit ROOM;
#include <ansi.h>

string check_blank_slot(object me);
void create()
{
        set ("short",  HIW "装备库" NOR );
         set ("long", @LONG

这里是装备总管无欢免费给各位玩家提供的装备库，墙上(wall)挂满了各式各样的装备。

LONG);  
        set("exits", 
        ([ //sizeof() == 1
                "east" : "/d/city/rbz",
        ]));
        set("no_fight",1);
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_pick", "pick");
        add_action("do_put",  "put");
        add_action("do_look","look");

}

int do_look(string arg)
{
        object  me;
        mapping diablo,obj;
        string  msg,name,*slot;
        int     i;
        me = this_player();
        if(!arg)
                return 0;
        if(arg!="wall")
                return 0;
        
        
        if(!mapp(diablo=me->query("diablo_weapon_slot")))
                  {
                        tell_object(me,"你的装备库里空空荡荡，用"+HIY"put <物品id> "NOR+"将放入其中！\n");
                        return 1;
                }
        if(!me->query("diablo_weapon_number"))
                  {
                        tell_object(me,"你的装备库里空空荡荡，用"+HIY"put <物品id> "NOR+"将放入其中！\n");
                        return 1;
                }
        if(sizeof(diablo)!=me->query("diablo_weapon_number"))
        {
                 tell_object(me,HIR "\n你的装备库遭劫了，请和巫师联系。\n" NOR);
                return 1;
        }
        
       if(!sizeof(diablo)) 
         {
                        tell_object(me,"你的装备库里空空荡荡，用"+HIY"put <物品id> "NOR+"将放入其中！\n");
                        return 1;
        }
        slot = keys(diablo);    
        
        msg = CYN"\n★★★★★★★★★★★★★★★★★★★★★★★\n" NOR;

        for(i = 0; i < sizeof(slot); i++) {
                
                obj = diablo[slot[i]];
                msg = sprintf("%s" HIG "%3d、" NOR "%20s  %s \n",
                                msg,
                                i+1,
                                " ",
                                obj["name"]);
        }
        msg += CYN"★★★★★★★★★★★★★★★★★★★★★★★\n"NOR;
        msg+="\n用"+HIY"put <物品id>"NOR+"将放入其中，用"+HIC"pick <序号>"NOR+"取出其中的某一。\n"NOR;     
        me->start_more(msg);
        return 1;


}

int do_pick(string arg)
{
        object  me,ob;
        int   i,num,  index,amount;
        string files,slot;
        mapping diablo_ob,dbase;
        string *list,*prop;

        me = this_player();
        
        if( !arg ) return notify_fail("你要取回哪样物品？\n");
        
        i=atoi(arg);
        if(!i) return notify_fail("你要取回哪样物品？\n");
        if(!mapp(diablo_ob=me->query("diablo_weapon_slot")))
                return notify_fail("你的装备库里空空荡荡！\n");
                
      if(sizeof(all_inventory(me))>50)
              return notify_fail("你身上的东西太多了，拿不下了！\n");
       if(!me->query("diablo_weapon_number"))
                return notify_fail("你的装备库里空空荡荡！\n");
        num = me->query("diablo_weapon_number");
        if(sizeof(diablo_ob)!=num)
          return notify_fail(HIR "\n你的装备库遭劫了，请和巫师联系。\n" NOR);
        
        list=keys(diablo_ob);
        if(i < 1)
                return notify_fail("你的装备库里没有这杨东西！\n");
        if(num < i)
                return notify_fail("你的装备库里没有这样东西！\n");
        slot = list[i-1];
        dbase=diablo_ob[list[i-1]];
        files=dbase["files"];
        prop=keys(dbase);
        prop-=({"actions"});
        
        if(!ob=new(files))
        {
              destruct(ob);
              return notify_fail("装备取得失败，请联系巫师。\n");
        }
        
        else{
                ob=new(files);
                for(int z=0;z<sizeof(prop);z++)
                        ob->set(prop[z],dbase[prop[z]]);
                if(!ob->move(me))
                        ob->move(environment(me));
                
        
        }
        
                message_vision("$N从墙上取下" + ob->name() + "。\n", me);
                me->add("diablo_weapon_number",-1);
                me->delete("diablo_weapon_slot/"+slot);
                return 1;
     
}

int do_put(string arg)
{
        object  me, ob;
        int   amount;
        string files,slot;
        mapping num,ob_dbase;
        string *list;
        me = this_player();
        if( !arg ) return notify_fail("你要把什么东西放进库？\n");
        if( !objectp(ob = present(arg, me) ) )
                {tell_object(me,"你要把什么东西放进库？\n");
                 return 1;
                }
        if(!me->query("ludingshan"))
        {
                tell_object(me,"你还没解开鹿鼎山的秘密，暂时无法在这里典当物品。\n");   
                return 1;             
        }
        if(me->query("level")<=10)
        {
                tell_object(me,"级别至少需要10级才可以在这里免费保存装备。\n");   
                return 1;             
        }        
        if(!ob->is_gems())
        {
                tell_object(me,"这样东西不能放进库。\n");
                return 1;
        }
/*        
        if(!ob->query("weapon_prop"))
        {
                 tell_object(me,"这样东西不能放进库，你或许可以去盔甲库看看。\n");
                return 1;       
                
        }
*/
       if(ob->query("gem_ob_autoloaded"))
         {
                 tell_object(me,"这样东西不能放进库。\n");
                return 1;       
                
        }
/*   if(!ob->query("have_set_name"))
        {
               tell_object(me,"先替它取个名字(rename)吧^_^\n");
                return 1;                
        }
*/
        if(ob->is_character())
        {
                        tell_object(me,"活物可不能放进去^_^\n");
                return 1;
        }
     
        
         if(me->query("diablo_weapon_number")>MAX_SIZE_WEAPON-1)
        {
                tell_object(me,"库已经堆放满兵器了。\n");
                 return 1;
        }
        slot = check_blank_slot(me);
        if(slot == "none")
        {
                 tell_object(me,"你的库可能有点问题，请联系巫师。\n");
                 return 1;      
        }
//        ob->delete("actions");
//        ob->delete("skill_type");
        ob_dbase=ob->query_entire_dbase();
        files=base_name(ob)+".c";
        ob_dbase+=(["files":files]);
   
        me->set("diablo_weapon_slot/"+slot,ob_dbase);
        me->add("diablo_weapon_number",1);
        message_vision("$N将"+ob->query("name")+"放入到库中。\n",me);
        ob->move("/obj/void");
        destruct(ob);
        return 1;
}
string check_blank_slot(object me)
{        
        if(!me->query("diablo_weapon_slot/A"))  
                return "A";
        else if(!me->query("diablo_weapon_slot/B"))     
                return "B";
        else if(!me->query("diablo_weapon_slot/C"))     
                return "C";
        else if(!me->query("diablo_weapon_slot/D"))     
                return "D";
        else if(!me->query("diablo_weapon_slot/E"))     
                return "E";
        else if(!me->query("diablo_weapon_slot/F"))     
                return "F";
        else if(!me->query("diablo_weapon_slot/G"))     
                return "G";
        else if(!me->query("diablo_weapon_slot/H"))     
                return "H";
        else if(!me->query("diablo_weapon_slot/I"))     
                return "I";
        else if(!me->query("diablo_weapon_slot/J"))     
                return "J";
        else if(!me->query("diablo_weapon_slot/K"))  
                return "K";
        else if(!me->query("diablo_weapon_slot/L"))     
                return "L";
        else if(!me->query("diablo_weapon_slot/M"))     
                return "M";
        else if(!me->query("diablo_weapon_slot/N"))     
                return "N";
        else if(!me->query("diablo_weapon_slot/O"))     
                return "O";
        else if(!me->query("diablo_weapon_slot/P"))     
                return "P";
        else if(!me->query("diablo_weapon_slot/Q"))     
                return "Q";
        else if(!me->query("diablo_weapon_slot/R"))     
                return "R";
        else if(!me->query("diablo_weapon_slot/S"))     
                return "S";
        else if(!me->query("diablo_weapon_slot/T"))     
                return "T";
        else return "none";
}
