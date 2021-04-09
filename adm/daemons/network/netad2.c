//netad
//网际广告发送精灵
//Made by jason@indeed for vworld

#include <ansi.h>
#include <net/macros.h>
#include <net/dns.h>
#include <net/daemons.h>
#include <net/services.h>

#define AD_FILE "/adm/etc/ad.txt"

inherit F_DBASE;

int start_send(int);

void create()
{
	seteuid(ROOT_UID);
	set("channel_id",HIY"北大侠客行"NOR);
	start_send(0);
}

int start_send(int i)
{
	string ad,mudname;
	string file,*addr,add,port;
	if(!stringp(ad=read_file(AD_FILE,i,1)))
	{
		remove_call_out("start_send");
		call_out("start_send",5,0);
		return 1;
	}
	if(ad=="@END\n")
	{
		remove_call_out("start_send");
		call_out("start_send",5,0);
		return 1;
	}
	if(ad=="@BEGIN\n")
	{
		remove_call_out("start_send");
		call_out("start_send",5,++i);
		return 1;
	}
	//mudname=DNS_MASTER->query_mud_name();
	
	CHANNEL_D->do_channel(this_object(),"sys","sending ....\n");
	write(ad+"\n");
	if(!file=read_file("/adm/etc/udpaddr.txt"))
	{
		CHANNEL_D->do_channel(this_object(),"sys","Udp address read error!\n");
		return 1;
	}
	addr=explode(file,"\n");
	for(int ii=0;ii<sizeof(addr);ii++)
	{
		if(sscanf(addr[ii],"%s:%s",add,port)!=2) continue;
		DNS_MASTER->send_udp(add,port,
		"@@@" + DNS_GCHANNEL +
		"||NAME:" + INTERMUD_MUD_NAME +
		"||PORTUDP:" + "5563" +
		"||USRNAME:" + "Pkuxkx" +
		"||CNAME:" + "北大侠客行"  +
		"||MSG:" + ad  +
		"||CHANNEL:" +"es"+ "@@@\n");
	}
	remove_call_out("start_send");
	call_out("start_send",10,++i);
	return 1;
}
