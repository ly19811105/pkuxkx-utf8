// /adm/daemons/newsd.c
// build for news system
// zoom added for sending help info to newbie
// daemon for controling the news
// first written by akuma@pkuxk
// ver 2.0
// date 2001/05/22
// zoom 2003.4.13 modify
// Zine 2010.12.20 add 滚动新闻，有人长期不看news

#include <ansi.h>

#define NAME "北大侠客行新闻系统"
#define HEADER HIG"┏━━━━━━━━━━━━━"+NAME+"━━━━━━━━━━━━━┓\n"NOR
#define TAIL   HIG"┗━━━━━━━━━━━━━"+NAME+"━━━━━━━━━━━━━┛\n"NOR
#define LINE   HIG"┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n"NOR

inherit ITEM;
inherit F_SAVE;

mapping *news;
//data added by zoom
string *data;
string *msg = ({

        });
void create()
{
//------for sending help to newbie
        string lines;
        string *line;
        int i, j;
//used for news
        restore();
        remove_call_out("realtimenews");
        call_out("realtimenews",1);
/*
                lines = read_file("/adm/etc/newbie_help");
        if (lines)
        {
                line = explode(lines,"@@@");
                data = line;
                for(i=0, j=0; i<sizeof(line); i++) 
                {
                        if( line[i]=="" || line[i][0]=='#' ) continue;
                        data[j++] = line[i]; 
                }
        }
        set("channel_id", "帮助精灵");
        remove_call_out("do_warn");
        call_out("do_warn",28);
        remove_call_out("do_sendhelp");
        call_out("do_sendhelp",30); */
//---------the end
//      remove_call_out("pkuxmsg");
//      call_out("pkuxmsg",1);
}
//---------for sending help to newbie

int postrealtimenews(int current)
{
    string msg,msg1,msg2,*msgs;
    int n=current+1;
    msg=news[current]["title"];
    msgs=explode(news[current]["msg"],"\n");
    msg1=msgs[0];
    if (strwidth(msg1)<56) msg1=msg1;
    else
    {
        if (CHINESE_D->is_whole_words(msg1[0..55])) msg1=msg1[0..55]+"……";
        else msg1=msg1[0..54]+"……";
    }
    msg2=msg1+"\t"+HIW+"[详情请参阅"+HIG+"news "+n+HIW+"]\n"+NOR;
    CHANNEL_D->do_channel(this_object(), "jh", "以下是近期游戏更新----『"+HBBLU+msg+NOR"』，请各位玩家注意查看。"+NOR, -1);
    CHANNEL_D->do_channel(this_object(), "jh", msg2, -1);   
}

void realtimenews()  
{
    string msg;
    object ob=this_object();
    int max=sizeof(news)-1;
    int maximum=max;
    int current,min=-1;
    if (!sizeof(news))
    {
        remove_call_out("realtimenews");
        call_out("realtimenews",600);
        return;
    }
    while(time()-news[max]["time"]<259200)  //3天NEWS滚动播报，by Zine，可调整
    {
        max=max-1;
        min=max;
    }
    if (min==-1)
    {
        min=maximum;
    }
    current=random(maximum-min+1)+min+1;
    if (current>maximum)
    {
        current=maximum;
    }
    if (current<1)
    {
        current=1;
    }
    remove_call_out("postrealtimenews");
    call_out("postrealtimenews",1,current);
    remove_call_out("realtimenews");
    call_out("realtimenews",600);
}

void do_sendhelp()
{
//随即选择，每次发一条
    string msg;
    object *ob;
    int a,b;
    a = random(sizeof(data));
    b = (a + 1) % sizeof(data);
    msg = data[a];
    ob = filter_array(users(), "filter_listener", this_object() );
    CHANNEL_D->do_channel(this_object(), "helpme", HIW +"下面是新手帮助提示，请新手注意查看。" NOR, -1);
    CHANNEL_D->do_channel(this_object(), "helpme", HIW + msg + NOR, -1);
    remove_call_out("do_sendhelp");
    call_out("do_sendhelp",600);
}

int filter_listener(object ppl)
{
//if set env var noreceivehelp don't sent the info
    if( ppl->query("env/noreceivehelp") )
        return 0;
    else
        return 1;
}
//------the end

string query_save_file()
{
        return DATA_DIR + "news/newsd";
}

int news_list(object reader)
{
        int i, last_time_read, tab;
        string msg="",tmp,author="北侠巫师组",author_id="pkuxkx Wizards Group";

        if( !news || !sizeof(news) )
        {
                msg+=(sprintf(HIG"┃%-70s┃\n"NOR,"没有任何新闻存在"));
                msg+=TAIL;
                reader->start_more(msg);
                return 1;
        }

        last_time_read = this_player()->query("news_last_read/xkxnews");
        for (i=sizeof(news)-1;i>=0;i--)
        {
				if(news[i]["time"] < 1343529568) break;
				if (wizardp(reader))
				{
					author=news[i]["author"];
					author_id=news[i]["author_id"];
				}
                tmp= sprintf("[%s][%d]%-34s ",
                        ( news[i]["time"] > last_time_read ? "未读": "已读"),
                        i+1, news[i]["title"]);
                msg+=sprintf("%-70s\n",tmp);

                tmp=sprintf("---"+NOR+"%s(%s)"+HIG+"发布于%s",author,author_id,ctime(news[i]["time"])[0..15]);
                tab=70+COLOR_D->color_len(tmp);
                msg+=sprintf("%"+tab+"s\n",tmp);
        }
        msg="\n\n"+HEADER+CHINESE_D->frame_chinese(msg, 70, HIG"┃","┃"NOR);
        msg+=TAIL;
        reader->start_more(msg);
        return 1;
}

void done_post_news(object poster, mapping note, string text)
{
        string file, file1;

        note["msg"] = text;
        if( !pointerp(news) || !sizeof(news) )
                news = ({ note });
        else
                news += ({ note });
        
        //同步changes以及主页changes
        if( !text ) return;
        seteuid(getuid());
        if( !stringp(file = read_file( "/doc/help/changes" )) )
                file    = "*******************************************************************\n"
                        + "                       ---最新改动---\n\n"
                        + "BTW：若要看以前的 change 请用 help changeold\n"
                        + "*******************************************************************\n";
        file1 = replace_string( file, "BTW：若要看以前的 change 请用 help changeold", 
               note["title"] + "\n" + text + "\n\t\t\t[" + capitalize(poster->query("id")) + " At " + ctime(time()) +
                "]\n\nBTW：若要看以前的 change 请用 help changeold");
        if( file1 == file )
                write_file( "/doc/help/changes", note["title"] + "\n" + text + "\n\t\t\t"
                        + capitalize(poster->query("id")) + " At " + ctime(time())
                        + "\n\nBTW：若要看以前的 change 请用 help changeold\n"
                        + "*******************************************************************\n");
        else
                write_file( "/doc/help/changes", file1, 1 );
        if( !stringp(file = read_file( "/web/files/changes" )) )
                                        file="最后的一次更新插入的地方\n";
                file1 = replace_string( file,"最后的一次更新插入的地方","最后的一次更新插入的地方\n[" + capitalize(poster->query("id")) + " At " + ctime(time()) + "]\n" + note["title"] + "\n" + text);
                if ( file1 == file )
                                write_file( "/web/files/changes","\n最后的一次更新插入的地方\n[" + capitalize(poster->query("id")) + " At " + ctime(time()) + "]\n" + note["title"] + "\n" +  text);
                else
                                write_file( "web/files/changes",file1,1);

        tell_object(poster, "新闻录入完成。changes已同步。\n");
		if (sizeof(news))
		postrealtimenews(sizeof(news)-1);
        save();
        return;
}

int post_news(object poster,string arg)
{
        mapping note;

        if(!wizardp(poster))
                return -3;//权限不够
        note = allocate_mapping(5);
        note["title"] = arg;
        note["author"] = poster->query("name");
        note["author_id"] = poster->query("id");
        note["time"] = time();
        poster->edit( (: done_post_news, poster, note :) );
        return 1;
}

int read_news(object reader,string arg)
{
        int num, tab;
        int last_read_time;
		string author="北侠巫师组", head, body;
        last_read_time = reader->query("news_last_read/xkxnews");
        if( arg=="new" || arg=="next" )
        {
                if( !last_read_time )
                        num = 1;
                else
                        for(num = 1; num<=sizeof(news); num++)
                                if( news[num-1]["time"] > last_read_time )
                                        break;

        }
        else if( !sscanf(arg, "%d", num) )
                return -1;// dunno number

        if( num < 1 || num > sizeof(news) )
                return -2;// there is really no this number
        num--;
		{
			if (wizardp(reader))
			author=news[num]["author"];
            tab=70+COLOR_D->color_len(NOR+author+HIG);
            head=sprintf("%-70s\n%"+tab+"s",sprintf("[%d][%s]",num + 1,news[num]["title"]),
					"--"+NOR+author+HIG+ "发布于"+ctime(news[num]["time"])[0..9]);
            head=CHINESE_D->frame_chinese(head, 70, HIG"┃","┃"NOR);
            body=CHINESE_D->frame_chinese(news[num]["msg"], 70, HIG"┃","┃"NOR);
			reader->start_more( "\n\n"+HEADER+HIG + head + LINE + body + TAIL);
		}
        if( !last_read_time )
                reader->set("news_last_read/xkxnews", news[num]["time"] );
        else
                if( undefinedp(last_read_time) || news[num]["time"] > last_read_time)
                        reader->set("news_last_read/xkxnews", news[num]["time"] );
        return 1;
}

int do_discard(object discarder,string arg)
{
        int num;

        if( !arg || sscanf(arg, "%d", num)!=1 )
                return -1; //错误的参数
        if( !arrayp(news) || num < 1 || num > sizeof(news) )
                return -2;//没有该编号的新闻
        num--;
        if( news[num]["author"] != (string) discarder->query("name")
        &&      (string)SECURITY_D->get_status(discarder) != "(admin)"
        &&      !wizardp(discarder))
                return -3;//权限不够

        if(num == 0)
                news = news[num+1..sizeof(news)-1];
        else
                news = news[0..num-1] + news[num+1..sizeof(news)-1];
        save();
        return 1;//成功
}

int query_new(object reader)
{
        int num,total=0;
        int last_read_time;
        last_read_time=reader->query("news_last_read/xkxnews");
        for(num = 0; num<sizeof(news); num++)
        {
                if( news[num]["time"] > last_read_time )
                        total++;
        }
        return total;
}


void pkumsg()
{
        CHANNEL_D->do_channel(this_object(), "jh", HBRED+msg[random(sizeof(msg))]+NOR, -1);
        remove_call_out("pkumsg");
        call_out("pkumsg",600);
        return;
}

