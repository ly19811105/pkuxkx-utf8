//惩罚恶意说脏话的玩家的NPC。 
//这个程序是我从其他地方下载的，并非原创，不过原来的 
//功能很弱（几乎没有用处），经过修改后效果还可以。 

#include <ansi.h>
inherit NPC; 
//受惩罚的玩家被送往的地点，为了避免玩家利用此NPC作弊，比如死后说脏话 
//被送到阳间从而达到隐身的目的，所以，此地点最好在地狱。 
#define BS "/d/wizard/punish_room.c" 
//此NPC平时呆的地方，为了防止他心跳停止，丧失功能，此地点最好是经常有 
//玩家经过的地方，中心广场最合适。 
#define CT "/d/city/guangchang" 
//以下是禁止使用的脏话。 
//优点是扩充方便，但玩家也很容易钻空子，比如“他吗的”，嘿嘿。 
string *msg_d = ({ 
"他妈的","你妈的","傻B","我操","操你","和你妈睡", 
"操！","操!","fuck","FUCK","Fuck","婊子","f~u~c~k", 
"你奶奶的","和你妈做爱","她妈的","你爷爷的" 
"小屁孩","放屁","滚蛋","放狗屁","放你妈的屁","tmd", 
"TMD","tmmd","TMMD","tnnd","TNND","wokao", 
"wo kao","操你妈","日死你","干你娘","他妈妈的", 
"操你姐","狗屁wiz","狗wiz","破巫师","日死你", 

}); 

void punish(object); 

void create() 
{ 
        set_name(HIW"巡捕"NOR, ({"xun bu", "xunbu"})); 
        set("gender", "男性" ); 
        set("age", 30); 
        set("per", 10);//no rongmao description. 

        set("long", "无人不知的巡捕，你碰上他准是你说了不该说的话。\n"); 
        set("class", "taoist"); 
        set("combat_exp", 30000000);
        set("attitude", "friendly");
        set("shen_type", 1);
	set("str",100);
	set("con",100);
	set("dex",100);
	set("int",100);
	set("food",10000);
	set("water",10000);
        set_skill("unarmed", 1000); 
        set_skill("dodge", 1000); 
        set_skill("parry", 1000); 
        set_skill("blade", 1000); 
        set_skill("force", 1000); 
        set_skill("literate", 1000);
        set_skill("xiake-quanjiao", 1000);
        set_skill("xiake-shenfa", 1000);

        map_skill("unarmed","xiake-quanjiao");
        map_skill("parry","xiake-quanjiao");
        map_skill("dodge","xiake-shenfa");

        set("max_qi", 10000);
        set("max_jing", 10000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jiali", 100);

        setup(); 
        //以下是被监控的频道，各MUD不同。 
        if( clonep() ) CHANNEL_D->register_relay_channel("rumor"); 
        if( clonep() ) CHANNEL_D->register_relay_channel("chat"); 
        if( clonep() ) CHANNEL_D->register_relay_channel("new"); 
        if( clonep() ) CHANNEL_D->register_relay_channel("hslj"); 
        if( clonep() ) CHANNEL_D->register_relay_channel("mp"); 
        if( clonep() ) CHANNEL_D->register_relay_channel("baowei"); 
} 
void init()
{
        ::init();
        if(!query_heart_beat())
                set_heart_beat(1);
 }

void relay_channel(object ob, string channel, string msg) 
{ 
        int i;
        if( !userp(ob) || (channel == "sys") || this_object()->query("isemote") ) return; 
        for(i=0; i<sizeof(msg_d);i++)
         { 
        if( strsrch(msg, msg_d[i]) >= 0) 
                { 
        call_out("punish",1,ob); 
        return; 
                } 
        } 
} 

void punish(object ob) 
{ 
        object *inv; 
        object place; 
        int i; 
        CHANNEL_D->do_channel(this_object(),"rumor",sprintf("忽听巡捕一声怒喝：%s这次你可跑不了了。",ob->query("name")));
        message_vision(HIC"冒出一个"+HIW"巡捕"+HIC"拿出一条铁链，一下就套住$N的脖子。\n"NOR+CYN"$N伸长舌头、翻着白眼地被拖走了。\n"NOR, ob); 
        //this_object()->move(BS); 
        place = environment(ob);
        ob->move(environment(this_object())); 
        command("say 敢口出污言秽语?在此地老老实实给我蹲着."); 
        message_vision(CYN"说着，绳子一松，$N被扔在地上。\n"NOR, ob); 
        inv = all_inventory(ob); 
        for(i=0; i<sizeof(inv);i++)
        {
        destruct(inv[i]);
        } 
        ob->add("gab_word",1); 
        //第一次说脏话只是警告。 
        if(ob->query("gab_word")==1){ 
        message_vision(HIC"$N说道：念在$n是初犯，这次就算了，下次给我记着！\n"NOR,this_object(), ob); 
        ob->start_busy(7); 
        //this_object()->move(CT); 
        ob->move(place);
        return; 
        } 
        //第二次最高功夫减一级。 
        //注意，这里是调用skill.c里的函数，此函数内容各MUD不同，请斟酌。 
        if(ob->query("gab_word")==2){ 
        message_vision(HIB"$N对$n喝道：你竞敢再次污言秽语，不给你点厉害是不记得了！\n"NOR,this_object(), ob); 
        ob->skill_death_penalty(); 
        ob->start_busy(9); 
        //this_object()->move(CT); 
        ob->move(place);
        return; 
        } 
        //超过三次吗？嘿嘿，死去吧。 
        message_vision(HIY"$N高喊一声：$n这厮满嘴污言秽语，来人啊，把他的舌头割下来拿去喂狗！\n"NOR,this_object(), ob); 
        message_vision(HIR"只见两个狱卒过来，抓住$N挤破$N的肚皮把$N的肠子扯出来再用$N的肠子勒住 
        $N的脖子用力一拉，呵－－！整条舌头都伸出来啦！狱卒再手起刀落哗－－！ 
        整个世界清净了。\n"NOR,ob); 
        //ob->unconcious(); 
        ob->skill_death_penalty(); 
        ob->skill_death_penalty(); 
        ob->skill_death_penalty(); 
        ob->skill_death_penalty(); 
        ob->skill_death_penalty(); 
        //this_object()->move(CT); 
        ob->move(place);
        return; 
} 
void unconcious()
{
        die();
}

void die()
{
        return 0;
}
int heal_up()
{
        return ::heal_up() + 1;
}
