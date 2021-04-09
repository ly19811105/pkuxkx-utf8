//xytaskd.c
//Made by mudy
//#define NUMBER1 30
//#define NUMBER2 60
//2002.11.4
inherit F_DBASE;
#include <ansi.h>
object startroom;
int NUMBER1,NUMBER2;
nosave object *mgbing1=({});
nosave object *mgbing2=({});
nosave object *mgbing3=({});
nosave object *mgbing4=({});
string *mgb_file=({
     "/xytaskd/guojing.c",
     "/xytaskd/huangrong.c",
     "/xytaskd/lvwende.c",
"/d/xiangyang/npc/lvwende.c",
     "/xytaskd/mgbn2.c",
     "/xytaskd/mgbs1.c",
     "/xytaskd/mgbs2.c",
     "/xytaskd/mgbe1.c",
     "/xytaskd/mgbe2.c",
     "/xytaskd/mgbw1.c",
     "/xytaskd/mgbw2.c",
     "/xytaskd/qianhuzhangn.c",
     "/xytaskd/qianhuzhangs.c",
     "/xytaskd/qianhuzhangw.c",
     "/xytaskd/qianhuzhange.c",
     "/xytaskd/mgqbn1.c",
     "/xytaskd/mgqbn2.c",
     "/xytaskd/mgqbs1.c",
     "/xytaskd/mgqbs2.c",
     "/xytaskd/mgqbw1.c",
     "/xytaskd/mgqbw2.c",
     "/xytaskd/mgqbe1.c",
     "/xytaskd/mgqbe2.c",
     "/xytaskd/shoujun.c",
     "/xytaskd/mgbn1.c"
});
string *key_spot=({
     "/d/xiangyang/sgate.c",
     "/d/xiangyang/egate.c",
     "/d/xiangyang/wgate.c",
     "/d/xiangyang/sfdating.c",
     "/d/xiangyang/ngate.c"
     });
void start_task();
void task_done();
void pre_destruct();
void create()
{
        seteuid(getuid());
        set("channel_id",HIW"保卫襄阳"NOR);
      set("begin",0);
      set("victory",0);
remove_call_out("start_task");
call_out("start_task",1);
}
void start_task()
{
object *mgb_list=({});
object guojing;
object huangrong,lvwende,obj;
set("begin",1);
NUMBER1=30;
NUMBER2=60;
      set("victory",0);
      set("occupied",0);
      set("xyoccupied",0);
      set("east",0);
      set("south",0);
      set("west",0);
      set("north",0);
      set("east_qb",0);
      set("south_qb",0);
      set("west_qb",0);
      set("north_qb",0);
set("taskid",10+random(50));
for(int j=0;j<sizeof(key_spot);j++)
{
         (load_object(key_spot[j]))->set("no_reset",1);
         (load_object(key_spot[j]))->set("no_clean_up",1);
}
 if( objectp( guojing = present("guojing", load_object("/d/xiangyang/sfdating.c")) ))
{
destruct(guojing);
}
//task 前的描述
 message( "channel:" + "chat",HIY + "【公告天下】" + "保卫襄阳任务启动！\n"NOR,users());
for(int j=0;j<sizeof(mgb_file);j++)
{
 mgb_list = children(mgb_file[j]);
        for(int k=0; k<sizeof(mgb_list); k++)
                        destruct(mgb_list[k]);
}
lvwende=new("/xytaskd/lvwende");
lvwende->move("/d/xiangyang/sfdating.c");
guojing=new("/xytaskd/guojing.c");
guojing->move("/d/xiangyang/sfdating.c");
guojing->set("taskid",query("taskid"));
guojing->set("no_clean_up",1);
(load_object("/d/xiangyang/sfdating.c"))->set("shuaifu",1);
(load_object("/d/xiangyang/ngate.c"))->set("gate",1);
(load_object("/d/xiangyang/wgate.c"))->set("gate",1);
(load_object("/d/xiangyang/sgate.c"))->set("gate",1);
(load_object("/d/xiangyang/egate.c"))->set("gate",1);
huangrong=new("/xytaskd/huangrong.c");
huangrong->move("/d/xiangyang/sfdating.c");
for(int j=0;j<30;j++)
{
obj=new("/xytaskd/shoujun");
obj->move(load_object("/d/xiangyang/xycenter"));
}
//remove_call_out("init_data");
//call_out("init_data",1);
remove_call_out("pre_message1");
call_out("pre_message1",1);
set("begin_time",time());
remove_call_out("start_task");
call_out("start_task",14400);//更新时间四小时
return;
}
int init_data()
{
object obj;
int i;
string err;
        for(int j=0;j<sizeof(mgbing1);j++)
        {
                if(!undefinedp(mgbing1[j])&&objectp(mgbing1[j]))
                destruct(mgbing1[j]);
           }
        for(int j=0;j<sizeof(mgbing2);j++)
        {
                if(!undefinedp(mgbing2[j])&&objectp(mgbing2[j]))
                destruct(mgbing2[j]);
           }
        for(int j=0;j<sizeof(mgbing3);j++)
        {
                if(!undefinedp(mgbing3[j])&&objectp(mgbing3[j]))
                destruct(mgbing3[j]);
           }
        for(int j=0;j<sizeof(mgbing4);j++)
        {
                if(!undefinedp(mgbing4[j])&&objectp(mgbing4[j]))
                destruct(mgbing4[j]);
           }
mgbing1=({});
mgbing2=({});
mgbing3=({});
mgbing4=({});
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发兵攻打襄阳北门！\n"NOR,users());
for(i=0;i<NUMBER1;i++)
{
err=catch(obj=new("/xytaskd/mgbn1"));
if (err) {
message( "channel:" + "chat",HIY + "【程序调试】" + "创建失败！\n"NOR,users());
return 1;
}
mgbing1+=({obj});
mgbing1[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
for(i=NUMBER1;i<NUMBER2;i++)
{
obj=new("/xytaskd/mgbn2");
mgbing1+=({obj});
mgbing1[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
obj=new("/xytaskd/qianhuzhangn");
mgbing1+=({obj});
mgbing1[NUMBER2]->move(load_object("/d/xiangyang/caoyuan4.c"));
remove_call_out("pai_bing");
call_out("pai_bing",4);
return 1;
}
int pai_bing()
{
object obj;
int i;
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发兵攻打襄阳南门！\n"NOR,users());
for(i=0;i<NUMBER1;i++)
{
obj=new("/xytaskd/mgbs1");
mgbing2+=({obj});
mgbing2[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
for(i=NUMBER1;i<NUMBER2;i++)
{
obj=new("/xytaskd/mgbs2");
mgbing2+=({obj});
mgbing2[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
obj=new("/xytaskd/qianhuzhangs");
mgbing2+=({obj});
mgbing2[NUMBER2]->move(load_object("/d/xiangyang/caoyuan4.c"));
remove_call_out("pai_bing1");
call_out("pai_bing1",10);
return 1;
}
int pai_bing1()
{
object obj;
int i;
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发兵攻打襄阳西门！\n"NOR,users());
for(i=0;i<NUMBER1;i++)
{
obj=new("/xytaskd/mgbw1");
mgbing3+=({obj});
mgbing3[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
for(i=NUMBER1;i<NUMBER2;i++)
{
obj=new("/xytaskd/mgbw2");
mgbing3+=({obj});
mgbing3[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
obj=new("/xytaskd/qianhuzhangw");
mgbing3+=({obj});
mgbing3[NUMBER2]->move(load_object("/d/xiangyang/caoyuan4.c"));
remove_call_out("pai_bing2");
call_out("pai_bing2",4);
return 1;
}
int pai_bing2()
{
object obj;
int i;
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发兵攻打襄阳东门！\n"NOR,users());
for(i=0;i<NUMBER1;i++)
{
obj=new("/xytaskd/mgbe1");
mgbing4+=({obj});
mgbing4[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
for(i=NUMBER1;i<NUMBER2;i++)
{
obj=new("/xytaskd/mgbe2");
mgbing4+=({obj});
mgbing4[i]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
obj=new("/xytaskd/qianhuzhange");
mgbing4+=({obj});
mgbing4[NUMBER2]->move(load_object("/d/xiangyang/caoyuan4.c"));
remove_call_out("inspect_victory");
call_out("inspect_victory",1);
return 1;
}
int inspect_victory()
{
int i,sign;
object guojing,huangrong,obj;
if(!query("begin"))
{
for(i=0;i<sizeof(mgbing1);i++)
{
                if(!undefinedp(mgbing1[i])&&objectp(mgbing1[i]))
{
mgbing1[i]->set("victory",1);
mgbing1[i]->delete("no_clean_up");
}
}
for(i=0;i<sizeof(mgbing2);i++)
{
                if(!undefinedp(mgbing2[i])&&objectp(mgbing2[i]))
{
mgbing2[i]->set("victory",1);
mgbing2[i]->delete("no_clean_up");
}
}
for(i=0;i<sizeof(mgbing3);i++)
{
                if(!undefinedp(mgbing3[i])&&objectp(mgbing3[i]))
{
mgbing3[i]->set("victory",1);
mgbing3[i]->delete("no_clean_up");
}
}
for(i=0;i<sizeof(mgbing4);i++)
{
                if(!undefinedp(mgbing4[i])&&objectp(mgbing4[i]))
{
mgbing4[i]->set("victory",1);
mgbing4[i]->delete("no_clean_up");
}
}
for(int j=0;j<sizeof(key_spot);j++)
{
         (load_object(key_spot[j]))->delete("no_reset");
         (load_object(key_spot[j]))->delete("no_clean_up");
}
 if( objectp(huangrong= present("huang rong", load_object("/d/xiangyang/sfdating.c")) ))
huangrong->delete("no_clean_up");
 if( objectp( guojing = present("guojing", load_object("/d/xiangyang/sfdating.c")) ))
{
guojing->set("killed",1);
guojing->delete("no_clean_up");
}
task_done();
return 1;
}
sign=0;
for(i=0;i<sizeof(mgbing1);i++)
{
                if(!undefinedp(mgbing1[i])&&objectp(mgbing1[i]))
                     { sign=1;
                      break;
                     }
}
for(i=0;i<sizeof(mgbing2);i++)
{
                if(!undefinedp(mgbing2[i])&&objectp(mgbing2[i]))
                     { sign=1;
                      break;
                     }
}
for(i=0;i<sizeof(mgbing3);i++)
{
                if(!undefinedp(mgbing3[i])&&objectp(mgbing3[i]))
                     { sign=1;
                      break;
                     }
}
for(i=0;i<sizeof(mgbing4);i++)
{
                if(!undefinedp(mgbing4[i])&&objectp(mgbing4[i]))
                     { sign=1;
                      break;
                     }
}
if(!sign)
{
set("victory",1);
set("begin",0);
 message( "channel:" + "chat",HIR + "【襄阳战报】" + "来犯蒙古兵全军覆没，襄阳保卫战取得胜利!\n"NOR,users());
 message( "channel:" + "chat",HIR + "【襄阳战报】" + "襄阳共有"+chinese_number(query("occupied"))+"处城门被敌军攻破!\n"NOR,users());
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙哥仰天长叹：我有生之年再不踏足中原一步以告慰众将士在天之灵!\n"NOR,users());
 message( "channel:" + "chat",HIY + "【公告天下】" + "请保卫襄阳战斗中作出贡献的侠士，到郭靖处领取奖励!\n"NOR,users());
for(int j=0;j<sizeof(key_spot);j++)
{
         (load_object(key_spot[j]))->delete("no_reset");
         (load_object(key_spot[j]))->delete("no_clean_up");
}
if( objectp(huangrong= present("huang rong", load_object("/d/xiangyang/sfdating.c")) ))
huangrong->delete("no_clean_up");
 if( objectp( guojing = present("guojing", load_object("/d/xiangyang/sfdating.c")) ))
{
guojing->delete("no_clean_up");
guojing->set("killed",1);
}
task_done();
return 1;
}
else
{
//如果城门被破，加入骑兵入城！
if(query("north")&&!query("north_qb"))
{
set("north_qb",1);
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙哥大喜：襄阳北门已破，众将士再接再厉，骑兵从北门入城杀敌!\n"NOR,users());
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发骑兵从北面入城！\n"NOR,users());
for(int j=NUMBER2+1;j<NUMBER2+31;j++)
{
if(random(2)==0) obj=new("/xytaskd/mgqbn1");
else obj=new("/xytaskd/mgqbn2");
mgbing1+=({obj});
mgbing1[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
}
if(query("south")&&!query("south_qb"))
{
set("south_qb",1);
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙哥大喜：襄阳南门已破，众将士再接再厉，骑兵从南门入城杀敌!\n"NOR,users());
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发骑兵从南面入城！\n"NOR,users());
for(int j=NUMBER2+1;j<NUMBER2+31;j++)
{
if(random(2)==0) obj=new("/xytaskd/mgqbs1");
else obj=new("/xytaskd/mgqbs2");
mgbing2+=({obj});
mgbing2[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
}
if(query("west")&&!query("west_qb"))
{
set("west_qb",1);
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙哥大喜：襄阳西门已破，众将士再接再厉，骑兵从西门入城杀敌!\n"NOR,users());
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发骑兵从西面入城！\n"NOR,users());
for(int j=NUMBER2+1;j<NUMBER2+31;j++)
{
if(random(2)==0) obj=new("/xytaskd/mgqbw1");
else obj=new("/xytaskd/mgqbw2");
mgbing3+=({obj});
mgbing3[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
}
if(query("east")&&!query("east_qb"))
{
set("east_qb",1);
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙哥大喜：襄阳东门已破，众将士再接再厉，骑兵从东门入城杀敌!\n"NOR,users());
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古发骑兵从东面入城！\n"NOR,users());
for(int j=NUMBER2+1;j<NUMBER2+31;j++)
{
if(random(2)==0) obj=new("/xytaskd/mgqbe1");
else obj=new("/xytaskd/mgqbe2");
mgbing4+=({obj});
mgbing4[j]->move(load_object("/d/xiangyang/caoyuan4.c"));
}
}
remove_call_out("inspect_victory");
call_out("inspect_victory",5);
return 1;
}
}
//保卫襄阳之前交代历史背景
int pre_message1()
{
 message( "channel:" + "chat",HIM + "【 历史 】" + "公元1234年，蒙古取蔡州，金灭。同年，宋出兵收复汴京，败还.\n"NOR,users());
remove_call_out("pre_message2");
call_out("pre_message2",10);
return 1;
}

int pre_message2()
{
 message( "channel:" + "chat",HIM + "【 历史 】" + "公元1251年，蒙哥即大汗位，统军西征。\n"NOR,users());
remove_call_out("pre_message3");
call_out("pre_message3",6);
return 1;
}
int pre_message3()
{
 message( "channel:" + "chat",HIM + "【 历史 】" + "公元1257年，蒙哥亲征南宋。\n"NOR,users());
 message( "channel:" + "chat",HIM + "【 历史 】" + "........\n"NOR,users());
remove_call_out("pre_message4");
call_out("pre_message4",8);
return 1;
}
int pre_message4()
{
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙哥：襄阳乃南宋门户，取之,南宋可灭!\n"NOR,users());
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙哥：众将士听令，不日我军将兵分四路围攻襄阳!\n"NOR,users());
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古大军斗志昂扬....\n"NOR,users());
remove_call_out("pre_message5");
call_out("pre_message5",12);
return 1;
}
int pre_message5()
{
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "三日后......\n"NOR,users());
remove_call_out("pre_message6");
call_out("pre_message6",5);
return 1;
}
int pre_message6()
{
 message( "channel:" + "chat",HIR + "【襄阳战报】" + "探子：报～～～～～～～～蒙古率数万大军直逼襄阳，三日内即将攻城，十万火急!\n"NOR,users());
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "郭靖：全体将士，听令！从今天开始，全城戒备!\n"NOR,users());
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "郭靖：蓉儿，你马上广发英雄帖，让各路英雄聚集襄阳，共御强敌!\n"NOR,users());
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "黄蓉：嗯，靖哥哥。\n"NOR,users());
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "吕文徳：......\n"NOR,users());
 message( "channel:" + "chat",HIM + "【谣  言】" + "某人想溜了....\n"NOR,users());
remove_call_out("pre_message7");
call_out("pre_message7",12);
return 1;
}
int pre_message7()
{
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "吕文徳：蒙古兵有数万之众，我们不如早降......\n"NOR,users());
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "郭靖：襄阳乃南朝屏障，岂可言降？汝再多言.......\n"NOR,users());
 message( "channel:" + "chat",HIC + "【 闲　聊 】" + "郭靖非常确定的认为吕文徳就是一个大猪头!\n"NOR,users());
 message( "channel:" + "chat",HIY + "【保卫襄阳】" + "吕文徳：......\n"NOR,users());
remove_call_out("pre_message8");
call_out("pre_message8",20);
return 1;
}
int pre_message8()
{
 message( "channel:" + "chat",HIR + "【襄阳战报】" + "襄阳告急......\n"NOR,users());
remove_call_out("pre_message9");
call_out("pre_message9",20);
return 1;
}
int pre_message9()
{
 message( "channel:" + "chat",HIR + "【襄阳战报】" + "襄阳告急......\n"NOR,users());
remove_call_out("pre_message10");
call_out("pre_message10",20);
return 1;
}
int pre_message10()
{
 message( "channel:" + "chat",HIR + "【襄阳战报】" + "襄阳告急......\n"NOR,users());
remove_call_out("pre_message11");
call_out("pre_message11",20);
return 1;
}
int pre_message11()
{
 message( "channel:" + "chat",HIW + "【塞外军情】" + "蒙古开始发兵！\n"NOR,users());
remove_call_out("init_data");
call_out("init_data",1);
return 1;
}
//后记
void task_done()
{
if(query("victory"))
{
//call内容
 message( "channel:" + "chat",MAG + "【襄阳之战】" + "襄阳之战虽然胜利了，但是这一场屠戮却会很快在历史发展的长河中渐渐被人淡忘......\n"NOR,users());
 message( "channel:" + "chat",MAG + "【襄阳之战】" + "南宋的灭亡却是无法挽回......\n"NOR,users());
remove_call_out("post_message1");
call_out("post_message1",5);
return ;
}
else
{
 message( "channel:" + "chat",MAG + "【襄阳之战】" + "襄阳之战虽然失败了，但是这一场屠戮却会很快在历史发展的长河中渐渐被人们淡忘......\n"NOR,users());
remove_call_out("post_message3");
call_out("post_message3",5);
return ;
}
}
int post_message1()
{
 message( "channel:" + "chat",HIM + "【 后记 】" + "公元1259年，蒙古侵入叙利亚，蒙哥死于四川．忽必烈围鄂州，与南宋议和，北还。\n"NOR,users());
remove_call_out("post_message2");
call_out("post_message2",5);
return 1;
}
int post_message2()
{
 message( "channel:" + "chat",HIM + "【 后记 】" + "公元1273年，蒙古破樊城，襄阳降。\n"NOR,users());
remove_call_out("post_message3");
call_out("post_message3",5);
return 1;
}
int post_message3()
{
 message( "channel:" + "chat",HIM + "【 后记 】" + "公元1274年。蒙古发军二十万征南宋，同年十二月，下鄂州．\n"NOR,users());
remove_call_out("post_message4");
call_out("post_message4",5);
return 1;
}
int post_message4()
{
 message( "channel:" + "chat",HIM + "【 后记 】" + "公元1275年。元、宋丁家洲会战，宋大败．元连克建康、平江、常州诸地．\n"NOR,users());
remove_call_out("post_message5");
call_out("post_message5",5);
return 1;
}
int post_message5()
{
 message( "channel:" + "chat",HIM + "【 后记 】" + "公元1276年。南宋幼帝请降，临安破．\n"NOR,users());
remove_call_out("post_message6");
call_out("post_message6",5);
return 1;
}
int post_message6()
{
 message( "channel:" + "chat",HIM + "【 后记 】" + "公元1278年。宋瑞宗死．同年十二月，文天祥兵败被俘．\n"NOR,users());
remove_call_out("post_message7");
call_out("post_message7",5);
return 1;
}
int post_message7()
{
 message( "channel:" + "chat",HIM + "【 后记 】" + "公元1279年。正月，元军破崖山，宋帝溺死，宋亡．\n"NOR,users());
remove_call_out("post_message8");
call_out("post_message8",5);
return 1;
}
int post_message8()
{
 message( "channel:" + "chat",HIM + "【 再后记 】" + "公元1368年。朱元璋灭元，改国号大明.....\n"NOR,users());
 message( "channel:" + "chat",HIY+ "【公告天下】" + "保卫襄阳任务全部结束！\n"NOR,users());
//remove_call_out("start_task");
//call_out("start_task",14400);//更新时间四小时
return 1;
}
