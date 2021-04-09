#pragma save_binary
#include <ansi.h>

inherit ROOM;
//这个值以后看情况调整
//根据最新的当铺修改，以防当东西的bug
//advent 2006-8-5
#define MAX_PAWN 50

string *sell_msg = ({
  "破破烂烂，一文不值",
  "质地低劣，难看之极",
  "又脏又破，臭气熏天",
});

object shop_box;

int query_max_items() {return 50;}

void create()
{
    set("short", HIC"荣宝斋"NOR);
    set("long",
CYN"这里是京城里最有名的珠宝店。店主人刘老板见多识广，收藏的宝物也颇不
少，除了当世的名家珍品，还时常有些宝石兵器之类的，墙上挂着一块牌子（sign）。\n"NOR
        );

    set("exits", ([
        "north" : "/d/beijing/changanjie_e2",
    ]));

    set("objects", ([
                "/d/city/npc/bookseller" : 1,
        ]));
    set("item_desc", ([
                "sign" : "公平交易，童叟无欺\n

本店主营业务已迁至扬州，本店不再营业！
",
    ]));
    set("no_beg",1);
    set("no_steal", 1);
    set("no_fight", 1);
    set("no_perform", 1);
    setup();
}

void init()
{
/*
    add_action("do_value", "guji");
    add_action("do_value", "value");
    add_action("do_pawn", "pawn");
    add_action("do_pawn", "dang");
    add_action("do_sell", "sell");
    add_action("do_retrieve", "shu");
    add_action("do_buy", "buy");
    add_action("do_list", "list");
    add_action("do_quit", "quit");
*/
}

// find the shopbox object for this shop to hold sold items.
object findbox()
{
    if(shop_box && environment(shop_box)==this_object())
        return shop_box;

    shop_box=new("/feature/shopbox");
    shop_box->move(this_object());
    return shop_box;
}

string value_string(int value)
{
    if( value < 1 ) value = 1;
    else if( value < 100 )
        return chinese_number(value) + "文钱";
    else if( value < 10000)
        return chinese_number(value/100) + "两白银"
        + (value%100? "又" + chinese_number(value%100) + "文钱": "");
    else
        return chinese_number(value/10000) + "两黄金" + (value%10000?chinese_number((value%10000)/100) + "两白银":"")
        + (value%100? "又" + chinese_number(value%100) + "文钱": "");
}

void pay_player(object who, int amount)
{
    object ob;

    if( amount < 1 ) amount = 1;
    if( amount/100000 ) {
                ob = new("/clone/money/thousand-cash");
                ob->set_amount(amount/100000);
                        if(!ob->move(who))
                                ob->move(environment(who));
                amount %= 100000;
     }
    if( amount/10000) {
        ob = new(GOLD_OB);
        ob->set_amount(amount/10000);
        if(!ob->move(who))
            ob->move(environment(who));
        amount %= 10000;
    }
    if( amount/100 ) {
        ob = new(SILVER_OB);
        ob->set_amount(amount/100);
        if(!ob->move(who))
            ob->move(environment(who));
        amount %= 100;
    }
    if( amount ) {
        ob = new(COIN_OB);
        ob->set_amount(amount);
        if(!ob->move(who))
            ob->move(environment(who));
    }
}

int do_value(string arg)
{
    object ob;
    int value, sale;

    if( !arg || !(ob = present(arg, this_player())) )
        return notify_fail("你要拿什么物品给当铺估价？\n");

    if( ob->query("money_id") )
        return notify_fail("这是「钱」，你没见过吗？\n");

    if( !ob->is_gems())
        return notify_fail("本店不买卖普通物品！\n");

    value = ob->query("value");
    sale = ob->query_temp("sale_price");
    if(sale>0 && sale<value) value=sale;

    if( !value) printf("%s一文不值。\n", ob->query("name"));
    else
        printf("%s价值%s。\n如果你要卖断(sell)，可以拿到%s。\n如果你要典当(pawn)，得付手续费%s。\n",
          ob->query("name"), value_string(value),
          value_string(value * 60 / 100), value_string(value * 20 / 100));

    return 1;
}

int do_pawn(string arg)
{
        object ob, me;
        int value, sale_price, pawn_count, time;
        string obj_file, file_name, data;
        int i, pawn_num, clone_number, totalnum;
        mapping pawn, vpawn;
        string term, *terms;
        totalnum=0;

        me = this_player();
        if(!me->query("ludingshan"))
        return notify_fail("你还没解开鹿鼎山的秘密，暂时无法在这里典当物品。\n");

        pawn = me->query("pawns");//物品名字
        vpawn = me->query("vpawns");//物品价值

        if( me->is_busy() )
        return notify_fail("你现在正忙着呢。\n");

        //玩家可以典当的物品的数量
        pawn_num=to_int(me->query("combat_exp")/1000000 + me->query("mud_age")/(3600*24))+1;
        if (pawn_num < 0)
                pawn_num=0;

        if (pawn_num > MAX_PAWN)
                pawn_num = MAX_PAWN;//不能超过最大限制

        if ( mapp(pawn) && sizeof(pawn) )
        {
                terms = keys(pawn);
                totalnum = sizeof(terms);//总数
        }
        if( !arg || !(ob = present(arg, me)))
        {

                if( !mapp(pawn) || !sizeof(pawn) )
                {
                        write("你并没有典当任何物品。\n");
                        printf("\t你一共可以典当%d件物品。\n",pawn_num);
                }
                else
                {
                        write("你目前典当的物品有：\n");
                        terms = keys(pawn);
                        for (i=0 ;i<sizeof(terms) ;i++ )
                        {
                                printf("%-3s：  %-20s     手续费：%s\n", terms[i], pawn[terms[i]], value_string(vpawn[terms[i]]* 1/5));
                        }
                        printf("\t你还可以典当%d件物品。\n", pawn_num-i);
                }
                return 1;
        }

    if (!ob->is_gems())
        return notify_fail("这种普普通通的东西，我可不要！\n");


    if( ob->query("money_id") ) return notify_fail("你要当「钱」？\n");

    if( ob->query("material") == "ice" )
        return notify_fail("掌柜的说：冰的东西我们这里没法存放。\n");
    //cuz ice melts, will cause problem, so disabled...weiqi, 970930.

    value = ob->query("value");
    sale_price=ob->query_temp("sale_price");

    if (sale_price>0)
                sale_price= sale_price>value?value:sale_price;
    else
                sale_price=value;

        if( !(sale_price*6/10) ) return notify_fail("这样东西并不值很多钱。\n");
    if( !value || value < 10) return notify_fail("这样东西不值钱。\n");

        if(ob->query("no_drop"))
            return notify_fail("这样东西不能离开你。\n");

            if (totalnum >= pawn_num)
                       return notify_fail("你典当物品数量太多，小店没有地方存了。\n");
    if( mapp(pawn) && sizeof(pawn))
    {
                terms = keys(pawn);

                for(i=0; i<sizeof(terms); i++)
                {
                        pawn_count = i;
                        if(!((int) me->query("vpawns/" + sprintf("%d", i))))
                                break;
                        else pawn_count = i+1;
                }
                if (sizeof(terms) >= pawn_num)
                        return notify_fail("你已典当太多物品了。\n");
        }
        else
                pawn_count=0;

                time = time();
                if(ob->query("equipped"))
                ob->unequip();
                ob->set("owner_id", me->query("id"));
                ob->set("savetime", time);
                ob->save();
//              write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
//              ob->query("name") + "一" + ob->query("unit") + "，押"+
//                      value_string(sale_price*60/100)+ "。\n");
    write("掌柜的说道:您暂时将"+ob->query("name") +"寄存在我这里，等赎出来的时候我们加收20％寄存费用。\n");
//              message_vision("$N把身上的" + ob->query("name") + "拿出来典当了"
//                      + value_string(sale_price * 60 / 100) + "。\n", me);
            me->start_busy(1);
                term = ob->query("name");
                data = base_name(ob)+ ".c";
                me->set("pawns/"  + sprintf("%d",pawn_count),  term);
                me->set("vpawns/" + sprintf("%d",pawn_count), ob->query("value"));
                me->set("tpawns/" + sprintf("%d",pawn_count), time);
                me->set("fpawns/" + sprintf("%d",pawn_count), data);
                me->set("ipawns/" + sprintf("%d",pawn_count), ob->parse_command_id_list());
                me->save();
//          pay_player(me, sale_price * 60 / 100);

        destruct(ob);

    return 1;
}

int do_sell(string arg)
{
    object ob, *obj;
    int value, sale, allvalue, sum;
    string obj_file, goods = "";
    int i, j, oldnum;
    string index;

    if( this_player()->is_busy() )
        return notify_fail("你现在正忙着呢。\n");

    sum = sizeof(findbox()->query("goods"));

    if(arg == "all") //全卖，嘿嘿
    {
        j = 0;
        obj = all_inventory(this_player());
        for(i = sizeof(obj); i > 0; i--)
        {
                if(obj[i - 1]->is_gems())
                {
                        j++;
                        value = obj[i - 1]->query("value");
                        sale = obj[i - 1]->query_temp("sale_price");
                        if(sale > 0 && sale < value) value = sale;
                        allvalue += value;
                        goods += obj[i - 1]->query("name") + "、\n";
                        obj[i - 1]->move(findbox());
                        findbox()->set("goods/" + (sum + 1), obj[i - 1]);
                        sum++;
                }
        }
        if(j)
        {
                allvalue = allvalue * 70/ 100;
                this_player()->start_busy(1);
                message_vision("$N把身上的" + goods + "一共" + chinese_number(j) + "件物品卖掉，当"
                + value_string(allvalue) + "。\n", this_player());
                pay_player(this_player(), allvalue);
        }
        else
        tell_object(this_player(), "你身上没有什么特殊的物品可以出售。\n");
        return 1;
    }

    if( !arg || !(ob = present(arg, this_player())) )
        return notify_fail("指令格式：sell <物品名|all>\n");
    if (ob->query("shaolin"))
        return notify_fail("少林的宝物小的可不敢要呀！\n");

    if (ob->query("mingjiao"))
        return notify_fail("魔教的财产小的可不敢要呀！\n");

    if( !ob->is_gems())
        return notify_fail("本店不买卖普通物品！\n");

    if( ob->query("money_id") ) return notify_fail("你要卖「钱」？\n");
    value = ob->query("value");
    sale = ob->query_temp("sale_price");
    if(sale>0 && sale<value) value=sale;
    if( !value ) return notify_fail("这样东西不值钱。\n");

        if(ob->query("no_drop"))
            return notify_fail("这样东西不能离开你。\n");

    if( ob->query("material") == "ice" )
        return notify_fail("掌柜的说：冰的东西我们这里没法存放。\n");
    //cuz ice melts, will cause problem, so disabled...weiqi, 970930.

    write("掌柜的唱道："+ sell_msg[random(sizeof(sell_msg))] +
      ob->query("name") + "一" + ob->query("unit") + "，当"+
      value_string(value*60/100)+ "。\n");
    message_vision("$N把身上的" + ob->query("name") + "卖掉。\n",
      this_player());

        ob->move(findbox());
        findbox()->set("goods/" + (sum + 1), ob);
        sum++;

        this_player()->start_busy(1);
        pay_player(this_player(), value * 70 / 100);

        return 1;
}
int affordable(object me, int amount)
{
        int total;
        object cash, tencash, gold, silver, coin;

                tencash = present("tenthousand-cash_money", me);
        cash = present("thousand-cash_money", me);
        gold = present("gold_money",me);
        silver = present("silver_money",me);
        coin = present("coin_money",me);

        total = 0;
        if( tencash) total += tencash->value();
        if( cash) total += cash->value();
        if( gold ) total += gold->value();
        if( silver ) total += silver->value();
        if( coin ) total += coin->value();

        if( total < amount ) return 0;

        return total;
}
int do_retrieve(string arg)
{
        int num;
        int amount;
        string ob_file, save_file, *id;
        object ob;
        object me;
        int afford;
        if( !arg || sscanf(arg, "%d", num)!=1 )
                return notify_fail("指令格式：redeem <物品标号>\n");
        me = this_player();
        amount = (int) me->query("vpawns/" + sprintf("%d", num));
        if( !amount )
                return notify_fail("有这个物品标号吗？\n");
        amount = amount * 1 /5;
         if( !(afford = this_player()->can_afford(amount)) )  {
            return notify_fail("你没有足够的钱来赎回。\n");
        }
        else if( afford == 2 )
        return notify_fail("你没有足够的零钱，而银票又没人找得开。\n");
        if( afford = affordable(me, amount) ) {
                                me->start_busy(1);
                me->pay_money(amount);
                ob_file = me->query("fpawns/"+sprintf("%d",num));
                ob = new(ob_file);
                ob->set("owner_id", me->query("id"));
                ob->set("savetime", me->query("tpawns/"+sprintf("%d",num)));
                save_file = ob->query_save_file();
                if(ob->restore())
                rm(save_file + ".o");
                id = me->query("ipawns/" + sprintf("%d",num));
                ob->set_name(ob->query("name"), id);
                ob->set_weight(ob->query("base_weight") + ob->query("item/weight"));
                ob->move(me);

                me->delete("tpawns/" + sprintf("%d",num));
                me->delete("pawns/" + sprintf("%d",num));
                me->delete("vpawns/" + sprintf("%d",num));
                me->delete("fpawns/" + sprintf("%d",num));
                me->delete("ipawns/" + sprintf("%d",num));

                me->save();
                message_vision("$N赎回了$n。\n", me, ob);
                return 1;
        } else
                        return notify_fail("你的钱不够。\n");

}

int do_list()
{
        object goods;
        string list, name;
        int i, j;
        object me=this_player();

        if( (i = sizeof( goods = findbox()->query("goods") )) == 0 )
        return notify_fail("当铺目前没有任何货物可卖。\n");

        list = "你可以购买下列这些东西：(请使用命令 buy <物品编号> 来购买)\n\n";
        write(list);
        for(j = 1; j <= i; j++)
        {
                goods = findbox()->query("goods/" + j);
                name = goods->query("name") + "(" + goods->query("id") + ")";
                list = sprintf("%4d：%-52s：%-24s\n", j, name,
                value_string(goods->query("value")) );
                write(list);
        }

    return 1;
}

int do_buy(string arg)
{
    object *goods;
    object ob;
    int value, afford;
    int i, j, num;
    string arg1, arg2;

    if( this_player()->is_busy() )
        return notify_fail("你现在正忙着呢。\n");

    if( !arg )  {
        write("指令格式：buy <物品编号>\n");
        return 1;
    }

    // players are used to the "buy sth from sb" format.
    if( sscanf(arg, "%s from %s", arg1, arg2) == 2 )   {
        arg = arg1;
    }

    if( (i = sizeof( goods = all_inventory(findbox()) )) == 0  )
        return notify_fail("当铺目前没有任何货物可卖。\n");

    num = atoi(arg);

    if(num && objectp(ob = findbox()->query("goods/" + num)))
    {
            value = ob->query("value");
            if( !(afford=this_player()->can_afford(value)) )  {
                write("你没有足够的钱。\n");
                return 1;
            }
            else if( afford == 2 )  {
                write("你没有足够的零钱，而银票又没人找得开。\n");
                return 1;
            }

            this_player()->pay_money(value);

            message_vision("$N向当铺买下一" +
              ob->query("unit") + ob->query("name") + "。\n", this_player() );

            this_player()->start_busy(1);
            this_player()->save();

            //so that the bought item would be the
            //same as the one on sale.

            if(!ob->move(this_player()))
            {
                //pay back player the money he payed
                pay_player(this_player(),value);
                return 0;
            }
            else
            {
                //偷懒了:P，这里只是简单的交换了一下物品的顺序，如果有必要可以重新排序
                findbox()->set("goods/" + num, findbox()->query("goods/" + i));
                findbox()->delete("goods/" + i);
            }

            return 1;
    }
    else
    write("指令格式：buy <物品编号>。\n");

    return 1;
}

int do_quit()
{
          this_player()->move("/adm/room/quitroom");
    return 1;
}

// no clean up at hockshop to prevent items lose.
int clean_up()
{
    return 0;
}


string do_buy1(string arg)
{
      return "本店只收购宝石，并不提供售出服务！\n";
}
