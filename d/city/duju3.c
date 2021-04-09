//  Room:  duju3
//  by  hubo 2008.5.16 

#include <ansi.h>
#include <localtime.h>
inherit  ROOM;

int  room_status  =  0;
int  *res  =  allocate(5);

mapping  bets  =  ([
    "1"  :  "德国",
    "2"  :  "西班牙",
    "3"  :  "葡萄牙",
    "4"  :  "荷兰",
    "5"  :  "法国",
    "6"  :  "意大利",
    "7"  :  "克罗地亚",
    "8"  :  "捷克",
    "9"  :  "瑞典",
    "10"  :  "俄罗斯",
    "11"  :  "罗马尼亚",
    "12"  :  "瑞士",
    "13"  :  "土耳其",
    "14"  :  "希腊",
    "15"  :  "波兰",
    "16"  :  "奥地利",
]);

void  create()
{
    set  ("short",  HIC"赌球室三"NOR);
    set  ("long",
HIW"这是博彩公司后面的一间赌球室，一个操盘手用警惕的眼光打量着你，在墙上挂着一个大屏幕
电视，即将放映本场竞猜足球比赛。

柜台上有个大牌子写着：
    本房间的赌局：（为了方便携带，赌球单位一律是cash）
    欧洲杯冠军竟猜：
    代码        国家        赔率
     1          德國         4.3  
     2          西班牙       5.0
     3          葡萄牙       5.5  
     4          荷蘭         5.8
     5          法國         11.0
     6          意大利       11.0
     7          克羅地亞     16.0
     8          捷克         20.0  
     9          瑞典         25.0
     10         俄羅斯       50.0
     11         羅馬尼亞     50.0
     12         瑞士         70.0
     13         土耳其       90.0
     14         希臘         110.0
     15         波蘭         130.0
     16         奧地利       450.0  
   （截止投注时间：2008.6.15 24:00）
\n"NOR
);
   
    set("exits",  ([  /*  sizeof()  ==  1  */
        "out"  :  "/d/city/dating",
    ]));
    set("objects",  ([  /*  sizeof()  ==  1  */
        __DIR__"npc/caopan3"  :  1,
    ]));
    set("light_up",  1);
    set("no_fight",  1);
    set("no_beg",  1);
    set("no_task",1);
    setup();
}

void  init  ()
{
    add_action  ("do_bet","bet");
    add_action  ("do_betlist","betlist");
}

int  do_bet  (string  arg)
{
    object  me  =  this_player();
    int  amount;
    string  code;
    object cash;
    object  ob;
    mixed *t;

    t = localtime( time() );
    if( t[LT_MON] >= 5 )  //  && t[LT_MDAY] > 15 )
          return  notify_fail("对不起，投注时限已经过了，下次请早点来。\n");

    if  (!arg  ||
            sscanf(arg,"%s %d",code,amount)  !=  2)
        return notify_fail("请使用：  bet <赔率代码> <数目> \n");

    if  (code  !=  "1"  &&
         code  !=  "2"  &&
         code  !=  "3"  &&
         code  !=  "4"  &&
         code  !=  "5"  &&
         code  !=  "6"  &&
         code  !=  "7"  &&
         code  !=  "8"  &&
         code  !=  "9"  &&
         code  !=  "10"  &&
         code  !=  "11"  &&
         code  !=  "12"  &&
         code  !=  "13"  &&
         code  !=  "14"  &&
         code  !=  "15"  &&
         code  !=  "16" )
        return  notify_fail("你要押哪种赔率代码？\n");
    
    cash = present("cash", me);
    if(!cash) 
       return notify_fail("你身上没有银票。\n");
        
    if((int) cash->query_amount() < amount)
        return notify_fail("你身上没有那麽多银票。\n"); 

    if  (amount  <  1)
        return  notify_fail("请多押一些钱。\n");
    
    if  (me->query("level") == 0)
        
        {
                if  (amount  >  10)
                        return notify_fail("你超出了你的赌球上限。\n"); 
        }
    
    if  (me->query("level")  > 0)
        
        {
                if  (amount  >  me->query("level")*10)
                        return notify_fail("你超出了你的赌球上限。\n"); 
        }
                        
    if  (me->query("duqiu/amount3") > 0)
        return  notify_fail("你已经赌过这场了，再玩其他场次吧。\n");

    if  (room_status  >  1)
        return  notify_fail("现在正在赌呢，稍等片刻。\n");

//    me->set("duqiu/what2",1);  //确定本场赌局序号，以后赌局依次排序，防止bug
    me->set("duqiu/code3",code);
    me->set("duqiu/amount3",amount);
    message_vision  (sprintf("$N拿出%s张银票，买了冠军是%s。\n",
                                                    chinese_number(amount),
                                                    bets[code]),
                                    me);
   
    if  (amount  ==  cash->query_amount())
        destruct  (cash);
    else
        cash->add_amount(-amount);
    
    log_file("static/xiazhu",sprintf("%s(%s) 于%s在冠军竟猜中下注%d张cash，赔率代码为%s！\n",
    me->query("name"),me->query("id"),ctime(time()),me->query("duqiu/amount3"),me->query("duqiu/code3"))); 

    return  1;
}

int  do_betlist  (string  arg)
{
    object me; 
    me = this_player();
    if( !me->query("duqiu") )
    {
       write("你应该先下注这场球! \n");
       return 1;
    }
    if( !me->query("duqiu/amount3") )
       write("你没有下注这场球! \n");       
    else 
       write("你在本赌场买了"+me->query("duqiu/amount3")+" 张银票，赔率代码是"+me->query("duqiu/code3")+"。\n"); 

    return 1;
}

