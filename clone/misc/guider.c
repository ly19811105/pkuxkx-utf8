//新手精灵
//modified by Zine 2011-10-9 增加新地图的地点，增加城市简介功能。
//dating功能并入localmaps zine 2011-10-10
//建康到应天的修改。fix by yhzzyahoo
#include <ansi.h>
inherit ITEM;

mapping *cities = ({
            ([  "id":"yangzhou","name":"扬州","job_desc":"这里有慕容复、多尔衮和史可法正在找人帮忙做任务。","quest_desc":"这里的谜题极多，包含易容术、过劫难、捐福源、修兵器、宝石库等等。","family_desc":"这里的门派有丐帮（东门向北）、慕容（茶馆）。"]),
            });



void init()
{
          add_action ("do_fly", "travel");
          add_action ("do_view", "view");
          //add_action ("do_dating", "dating");
}

void create()
{
	set_name(CYN"路引"NOR, ({"lu yin","luyin","newbie guider", "guider"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
	else {
		set("long", HIC"这是官府发给新手的路引，\n你可以查看(view)一些最近基本的帮助，也可到处去逛逛(travel)。\n"NOR);
        set("unit", "张");
		set("no_give", 1);
		set("no_put", 1);
	    set("value", 10000);
        set("material", "steel");
        set("no_sell", 1);
        set("no_pawn", 1);
        set("no_store", 1);
		}
                 setup();
        call_out("pricing",1);
}

int pricing()
{
    set("value", 0);
    return 1;
}

int do_dating()
{
    object me=this_player();
    string city,msg;
    mapping query_city;
    int i,flag=0;
    if( me->query("jing") < 100 )
        return notify_fail("你精神不够旺盛，没力气打听了！\n");
    if( me->query_temp("pending/exercising"))
        return notify_fail("你打完坐在走吧！\n");
    if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

    if (me->is_fighting())
        return notify_fail("你正打的热闹着呢!\n");
    if (me->is_busy())
        return notify_fail("你正忙着呢!\n");
    if (!environment(me))
        return notify_fail("你身边没有人，怎么打听呢？\n");
    city=TASK_D->place_belong(environment(me));
    for (i=0;i<sizeof(cities);i++)
    {
        if (city==cities[i]["name"])
        {
            flag=1;
            query_city=cities[i];
        }
    }
    if (flag==0)
    {
        return notify_fail("暂无此区域信息。\n");
    }
    message_vision("$N随便拉过一个路人，像此人打听起，这里的风土人情。\n",me);
    msg="路人道：";
    msg+="这里是"+HIW+query_city["name"]+NOR+"。\n";
    if (query_city["job_desc"])
    {
        msg+=HIG+query_city["job_desc"]+NOR+"\n";
    }
    else
    {
        msg+=HIG+"这里没有人可以提供任务。\n"+NOR;
    }
    if (query_city["quest_desc"])
    {
        msg+=HIM+query_city["quest_desc"]+NOR+"\n";
    }
    else
    {
        msg+=HIM+"这里没有什么像样的谜题。\n"+NOR;
    }
    if (query_city["family_desc"])
    {
        msg+=HIR+query_city["family_desc"]+NOR+"\n";
    }
    else
    {
        msg+=HIR+"这里没有什么像样的谜题。\n"+NOR;
    }
    me->add_busy(2);
    me->add("jing",-10);
    tell_object(me,msg);
    return 1;
}

  int do_fly(string arg)
{

            object* inv;
	        string destin, destch, destmg;
	        int i;
            object me = this_player();

          if (!arg)
          {
          tell_object(me,HIY"\t\t@*@*@*@*@*@*@*@*你可以去(travel)以下地方：*@*@*@*@*@*@*@*@\n\n"NOR);
              tell_object(me,"\t\t＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 少林(sl)    华山(hs)    灵鹫(lj)    桃花岛(thd)  "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 武当(wd)    明教(mj)    扬州(yz)    天龙(tls)    "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 星宿(xx)    嘉兴(jx)    峨嵋(em)    泉州(quan)   "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 全真(qz)    白驼山(bt)  古墓(gm)    临安府(laf)  "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 苏州(sz)    归云庄(gy)  襄阳(xy)    平西王府(px) "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 泰山(ts)    灵州(lz)    丐帮(gb)    日月(ry)     "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 北京(bj)    凌霄城(lxc) 侠客岛(xkd) 杀手帮(pker) "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 镇江(zj)    钓鱼岛(dyd) 慕容(mr)    大轮寺(dls)  "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 江州(jz)    神龙岛(sld) 洛阳(ly)    大理城(dl)   "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 岳阳(yy)    昆明(km)    成都(cd)    应天府(ytf)  "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊"+HIW+" 晋阳(jy)    长安(ca)    信阳(xin)   张家口(zjk)  "+NOR+"＊＊\n");
              tell_object(me,"\t\t＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n"NOR);
              return 1;
        	}

if (me->query("age") > 14 && !wizardp(me))
{
  	tell_object(me, "只有小于15岁，才能使用路引搭乘官府的免费马车，现在你可以用路引打听(dating)下风土人情!!!\n");
    return 1;
}
if (me->query("combat_exp") > 5000 && !wizardp(me))
{
  	tell_object(me, "只有小于15岁，才能使用路引搭乘官府的免费马车，现在你可以用路引打听(dating)下风土人情!!!\n");
    return 1;
}
if( me->query("jing") < 10 )
        return notify_fail("你精神不够旺盛，没力气瞎逛了！\n");

if(!environment(me)->query("outdoors"))
        return notify_fail("请先到室外在使用此命令！所谓室外，就是能看到天气描述的地方啦。\n");

if( me->query_temp("pending/exercising"))
        return notify_fail("你打完坐在走吧！\n");
if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

if (me->is_fighting())
        return notify_fail("你正打的热闹着呢!\n");
if (me->is_busy())
        return notify_fail("你正忙着呢!\n");

inv = deep_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
        if(inv[i]->is_character() || userp(inv[i]))
        return notify_fail("你不能背着个活物到处逛！\n");
if(me->query_encumbrance()*100/me->query_max_encumbrance()>50)
             return notify_fail("你身上的东西太多了，把没用的东西都扔了吧!\n");
        if(arg=="凌霄城" || arg == "lxc")
	{
		destin = "/d/lingxiao/chengmen.c";
		destch = "雪山派";
		destmg = "此处就是雪山派所在地凌霄城的城门。";
	}
     else if(arg=="武当" || arg == "wd")
	{
		destin = "/d/wudang/sanqing.c";
		destch = "武当";
		destmg = "此处就是武当的三清殿，不是武当弟子到这就进不去了，武当弟子要下山需要向宋远桥打听“下山”的消息。";
	}
     else if(arg=="少林" || arg == "sl")
	{
		destin = "/d/shaolin/shanmen";
		destch = "少林";
		destmg = "这是少林山门，女客不能再上了，男香客可以去广场。进少林寺只有少林弟子和持有英雄令的客人们才行。";
	}
    else if(arg=="星宿" || arg == "xx")
        {
		destin = "/d/xingxiu/xxgate.c";
		destch = "星宿";
		destmg = "这星宿海人烟稀少，附近倒是有个维吾尔族小镇。可是您别乱走，小心碰到不讲理的星宿弟子，或是走到沙漠里迷了路。";
	}
    else if(arg=="明教" || arg == "mj")
        {
		destin = "/d/mingjiao/damen";
		destch = "明教";
		destmg = "这里就是明教山门，不是本派弟子就上不去了，如果硬闯进去要千万小心，青翼蝠王韦一笑可是见人就杀。";
	}
    else if(arg=="华山" || arg == "hs")
	{
		destin = "/d/huashan/path1";
		destch = "华山";
		destmg = "华山派就在南边，山上风景不错，您自己上去转转吧。";
	}
    else if(arg=="全真" || arg == "qz")
	{
		destin = "/d/quanzhen/gongmen.c";
		destch = "全真";
		destmg = "全真派可是个不错的门牌，有很多好东西，如果男弟子要拜尹志平需要发誓“忠于全真”。";
	}
    else if(arg=="归云庄" || arg == "gy")
	{
		destin = "/d/guiyunzhuang/gate";
		destch = "归云庄";
		destmg = "拜桃花岛需要先入归云庄，要注意桃花岛的弟子不要随意pk同时要注意自己的道德哦，否则会被师傅开除的。";
	}
    else if(arg=="桃花岛" || arg == "thd")
	{
		destin = "/d/taohuadao/haian";
		destch = "桃花岛";
		destmg = "只能到海港这里了，要坐船才能去桃花岛(enter boat)，你自己试试吧。";
	}
    else if(arg=="峨眉" || arg == "em")
	{
                destin = "/d/emei/shanmen";
		destch = "峨嵋";
		destmg = "这是峨嵋山脚啦，不是本门弟子就进不去啦。爬峨嵋山可累人了，您悠着点儿。";
	}
    else if(arg=="扬州" || arg == "yz")
	{
		destin = "/d/city/kedian";
		destch = "扬州";
		destmg = "这是扬州客店。这里人多事儿多，好玩儿的地方也多着呐。";
	}
    else if(arg=="天龙" || arg == "tls")
	{
		destin = "/d/tianlong/foothill.c";
		destch = "天龙";
		destmg = "这里就是天龙寺了。据说大理王子段誉在琅缳福地，不知道是个什么地方。";
	}
    else if(arg=="嘉兴" || arg == "jx")
	{
		destin = "/d/quanzhou/nanhu.c";
		destch = "嘉兴";
		destmg = "这里是嘉兴南湖。江湖谣传西毒欧阳锋曾经在这附近出现过，不知道是真是假。";
	}
    else if(arg=="泉州" || arg == "quan")
	{
		destin = "/d/quanzhou2/zhongxin.c";
		destch = "泉州";
		destmg = "这里是泉州城中心。附近有一幢向阳老宅，听说闹鬼，你还是不要过去的好。";
	}
    else if(arg=="古墓" || arg == "gm")
	{
		destin = "/d/gumu/caodi";
		destch = "古墓";
		destmg = "这里就是杨过与小龙女双宿双栖的古墓了，要拜师的话，你去向杨女打听“进墓”吧。";
	}
    else if(arg=="襄阳" || arg == "xy")
	{
		destin = "/d/xiangyang/sgate";
		destch = "襄阳";
		destmg = "这里是北方重镇襄阳城，目前正受到蒙古军队的攻击，如果你想加入襄阳保卫战，就向守将打听“投军”的消息吧。";
	}
    else if(arg=="泰山" || arg == "ts")
	{
		destin = "/d/taishan/daizong";
		destch = "泰山";
		destmg = "您自己上去吧。轻功如果太低上山小心别摔着。山上有当今武林盟主，赏善罚恶使者。";
	}
    else if(arg=="灵州" || arg == "lz")
	{
		destin = "/d/lingzhou/center.c";
		destch = "灵州";
		destmg = "您自己到处逛逛吧，不过别乱闯西夏皇宫啊。";
	}
    else if(arg=="平西王府" || arg == "px")
	{
		destin = "/d/pingxiwangfu/wangfugate";
		destch = "平西王府";
		destmg = "要进去就向亲兵头打听“自立为王”的消息，据说平西王的宝库里面有很多好东西。";
	}
    else if(arg=="灵鹫" || arg == "lj")
	{
		destin = "/d/lingjiu/jian";
		destch = "灵鹫宫";
		destmg = "要上山必须余婆婆带你去了，向她打听一下“上山”的消息吧，不过灵鹫宫只收女弟子哦。";
	}
    else if(arg=="杀手帮" || arg == "pker")
	{
		destin = "/d/pker/guangchang.c";
		destch = "杀手帮";
		destmg = "杀手帮是江湖中的一个秘密门牌，据说帮助楚云飞杀人会得到意想不到的奖励。";
	}
    else if(arg=="侠客岛" || arg == "xkd")
	{
		destin = "/d/xiakedao/nanhaibin";
		destch = "侠客岛";
		destmg = "侠客岛是无数武林人事梦寐以求想去的地方，不过只有得到赏善罚恶令的人才有资格去，你可以问问这里的黄衣大汉(wave dahan)。";
	}
    else if(arg=="丐帮" || arg == "gb")
	{
		destin = "/d/city/gbxiaowu.c";
		destch = "丐帮小屋";
		destmg = "新手加入丐帮应该算是成长最快的了，升袋会有很多经验奖励，而且丐帮弟子可以随地睡觉，真是爽啊！";
	}
    else if(arg=="临安府" || arg == "laf")
	{
		destin = "/d/hangzhou/bazi";
		destch = "临安府";
		destmg = "临安府是大宋的都城。";
	}
    else if(arg=="日月" || arg == "ry")
	{
		destin = "/d/riyuejiao/rukou.c";
		destch = "日月教";
		destmg = "日月教有很多秘密，如果自己实在摸索不出，也可以问问高手。";
	}
    else if(arg=="钓鱼岛" || arg == "dyd")
	{
		destin = "/d/diaoyudao/matou0";
		destch = "泉州港";
		destmg = "只能到这里了，要去钓鱼岛也要自己解开秘密才行，听说要有罗盘才不会在海上迷路。";
	}
    else if(arg=="姑苏慕容" || arg == "mr")
	{
		destin = "/d/murong/hubian1";
		destch = "太湖";
		destmg = "姑苏慕容在太湖之上，必须要坐船才能过去，你向绿衣女郎打听一下“拜庄”的消息吧。";
	}
    else if(arg=="苏州" || arg == "sz")
	{
		destin = "/d/suzhou/kedian.c";
		destch = "苏州";
		destmg = "要去姑苏慕容必须要经过苏州，你最好熟悉一下这里的地图。";
	}
    else if(arg=="白驼山" || arg == "bt")
	{
		destin = "/d/baituo/gebi";
		destch = "白驼山";
		destmg = "去白驼山的路上有一片大沙漠很危险，以后你来此地最好是骑上骆驼。";
	}
    else if(arg=="北京" || arg == "bj")
	{
                destin = "/d/beijing/yonganmen";
                destch = "北京城";
                destmg = "北京城晚上要关城门，要进城可要赶白天啊，晚上翻墙小心被官兵发现，被通缉了可不好办。";
	}
    else if(arg=="大轮寺" || arg == "dls")
	{
                destin = "/d/dalunsi/guangchang";
                destch = "大轮寺";
                destmg = "大轮寺终年积雪，没有一定轻功很难直接爬上来，可以做缆车，不过最好还是走丐帮密道啦。";
	}
    else if(arg=="神龙岛" || arg == "sld")
	{
                destin = "/d/shenlongdao/matou";
                destch = "神龙岛";
                destmg = "神龙岛要走塘沽坐船过来，岛上神龙（其实就是蛇啦）众多，如果不想被蛇咬就跟沐姑娘讨杯雄黄酒喝。";
	}
    else if(arg=="洛阳" || arg == "ly")
	{
                destin = "/d/luoyang/center";
                destch = "洛阳";
                destmg = "洛阳可是一个好地方，听说天地会搬到这里来了，对了，萧峰帮主也在这里。";
	}
    else if(arg=="大理" || arg == "dl")
	{
                destin = "/d/dalicheng/northgate";
                destch = "大理";
                destmg = "大理山清水秀，景色怡人，还有很多美食。大理王府就在这大理城中。";
	}
    else if(arg=="江州" || arg == "jz")
	{
                destin = "/d/jiangzhou/eastgate";
                destch = "江州";
                destmg = "江州据说有隐居的高手韩员外坐镇，宵小之辈不得作祟。";
	}
    else if(arg=="镇江" || arg == "zj")
	{
                destin = "/d/zhenjiang/southgate";
                destch = "镇江";
                destmg = "镇江扼守长江之滨，地势险要，金山寺里有个老和尚。";
	}
    else if(arg=="岳阳" || arg == "yy")
	{
                destin = "/d/yueyang/southgate";
                destch = "岳阳";
                destmg = "岳阳是一座古城，城内有岳阳楼等古迹。";
	}
    else if(arg=="昆明" || arg == "km")
	{
                destin = "/d/kunming/westgate";
                destch = "昆明";
                destmg = "昆明地处西南边陲，平西王府就在城北。";
	}
    else if(arg=="成都" || arg == "cd")
	{
                destin = "/d/chengdu/eastgate";
                destch = "成都";
                destmg = "成都是西南第一大城，天府之国，四通八达，交通便利。";
	}
    else if(arg=="晋阳" || arg == "jy")
	{
                destin = "/d/jinyang/jinsumen";
                destch = "晋阳";
                destmg = "晋阳城内有家药铺，据说隐藏着一些秘密。";
	}
    else if(arg=="长安" || arg == "ca")
	{
                destin = "/d/changan/southgate";
                destch = "长安";
                destmg = "长安十朝古都，是一座雄城，据八百里秦川形胜之地。";
	}
    else if(arg=="信阳" || arg == "xin")
	{
                destin = "/d/xinyang/southgate";
                destch = "信阳";
                destmg = "信阳是扬州和襄阳之间一座重要的城市，城南的汤泉池据说可以泡泡温泉。";
	}
    else if(arg=="张家口" || arg == "zjk")
	{
                destin = "/d/saiwai/southgate";
                destch = "张家口";
                destmg = "张家口是连接蒙古草原的关隘。";
	}
    else if(arg=="应天府" || arg == "ytf")
	{
                destin = "/d/yingtiannorth/machehang";
                destch = "应天府";
                destmg = "应天府是大宋的重要城市，只能先送到城外。";
	}
	else
   	{
 	return notify_fail("没有这个地方吧？？？\n");
	}

    message_vision(HIW"$N"+HIW+"拿出路引，拦下一辆大车，上了车去。\n"NOR, me);
    message_vision(HIW"大车载着$N向" + HIW+destch + HIW"方向离开...\n"NOR, me);
    me->move(__DIR__"dache");
    call_out("traveling",6+random(4),me,destch,destin,destmg);
    return 1;
}

int traveling(object me,string destch,string destin,string destmg)
{
    object pla=load_object(destin);
    if (pla)
    {
        me->move(pla);
        message_vision(HIW"$N从大车上下来了。\n", me);
	    tell_object(me, "车夫告诉你：“到啦，这里就是" + destch + "。”\n");
	    tell_object(me, CYN "车夫又说：“再免费告诉你点东西，" + destmg + "”\n" NOR);
        me->add("jing", -5);
    }
    return 1;
}

int do_view()
{
        write ("        你翻开《北大侠客行玩家守则》，只见上面写着：\n");
        write ("        当你进入本游戏，已成为本游戏一个正式的玩家，请你遵守以下玩家守则
        如果你无法同意以下守则，你可以用suicide -f命令消除自己的档案离开本mud，
        本mud将不会对你进行挽留。
        1.首先你应用"HIW"help rules"NOR"来参看通用的mud守则，这是几乎所有mud公认的玩家守
        则，本mud不再重申这些守则，只是对这些守则作一些补充。
        2．本mud不禁止使用机器人练功，因为打坐读书等事情不用机器人也实在是很难
        用人手来完成，但是本游戏不提倡使用机器人，请不要用XX任务不方便编机器人
        这类的理由对wiz进行提议修改。因被别人破坏机器人害死的id也不可以向wiz请
        求恢复。\n");
        write("        3．关于刷屏，不论因何种理由，任何人不得刷屏，如果出现刷屏现象，一次警告
        不听，立即踢出游戏，如果再次进入游戏刷屏，立即封ip。
        4．不得向wiz要求任何物品，金钱，武功，经验值等等，如果发现bug上报wiz，将
        对你发现的bug价值作出评估，对你作出相应奖励。
        5．不得向wiz询问有关解迷的任何事件，也不可要求恢复叛师和死亡等意外损失的
        数据。
        请各位玩家自重，如果你不能遵守上述守则，请立即suicide -f离开，本游戏将不
        对你作任何挽留。\n");
        write("        6．"HIR"关于成长"NOR"：  新手刚进入游戏，可以先看看"HIW"help intro，help newbie"NOR"看看关
        于游戏的一些基本知识，然后可以去扬州的中央广场的礼品树pick一个果子吃，可以
        得到1000点经验的奖励，要注意有些门派只收经验小于200的玩家，所以如果要拜这
        些门派必须在吃果子之前哦。还可以到广场上方的赏月台向绿萼打听“月饼”的消息，
        answer 甜月饼或者answer 咸月饼还可以吃一块月饼^_^。如果要钱可以到广场下方
        的发呆室，ask budong about 赚钱，如果满不懂身上有钱他就会给你的，满不懂还
        知道很多和游戏相关的秘密，有什么问题都可以问他，比如ask budong about 经验
        ask budong about 一灯大师等等。还有什么问题可以chat出来问问这里的玩家，大
        家都是很热心的，有什么问题一定可以得到解答。
		祝大家玩得开心！\n");
        return 1;
}

