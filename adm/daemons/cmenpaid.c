
#include <ansi.h>

#define CML_DIR "/u/aiai/create_menpai/logfiles/"

int query_prestige(string name)
{
        string* buf;
        string  init_file;
        int prtg;
        
        if ( ! init_file = read_file(CML_DIR+name) )
                return -1;
        sscanf(init_file,"%d",prtg);
        return prtg;    
}
        
string query_taskinfile(string name)
{
        string* buf;
        string init_file, taskformat;
        int prtg;

        if ( ! init_file = read_file(CML_DIR+name) )
                return "error";
        sscanf(init_file,"%d\n%s\n",prtg, taskformat);
        return taskformat;
}

void add_prestige(string name, int num)
{
        string* buf;
        string  init_file, other;
        int prtg;
        
        if ( ! init_file = read_file(CML_DIR+name) )
                 return;
        sscanf(init_file,"%d%s",prtg,other);
        prtg += num;
        init_file = sprintf("%d%s",prtg,other);
        write_file(CM_DIR+name, init_file, 1);

}

int prentice_setback(object ob)
{
        tell_object(ob,"真的很不幸，你的授业恩师决定放弃自己的门派，你不得不重新回到从前的门派中了。\n");
        ob->delete("menpai");
        if ( ob->query("old_family") )
                ob->set("family",ob->query("old_family") );
        return 1;
}
        
int creator_setback(object ob)
{
        ob->add("betrayer", 1);
        if ( ob->query("family") )
        {
                tell_object(ob,"很不幸的告诉你，侠客岛主只收那些自成门派的玩家，看来，你也无缘再作龙亦凡的传人了。\n");
                ob->delete("family");
        }
        tell_object(ob,"你恍如做了一场大梦，梦醒后一切又恢复到了从前的样子。\n");
        if ( ob->query("old_family") )
                ob->set("family", ob->query("old_family") );
        ob->delete("menpai");
        ob->delete("rank_info/rank");
        return 1;
}

int delete_menpai(string name, string dir)
{
        string* buf;
        string  init_file;
      mixed err;
      object ob;
      int i;
      object* inv;
        
        rm(CM_DIR+name+"/armorroom.c");
        rm(CM_DIR+name+"/diningroom.c");
        rm(CM_DIR+name+"/fronthall.c");
        rm(CM_DIR+name+"/houyuan.c");
        rm(CM_DIR+name+"/huiketing.c");
        rm(CM_DIR+name+"/kefang.c");
        rm(CM_DIR+name+"/mainhall.c");
        rm(CM_DIR+name+"/masterroom.c");
        rm(CM_DIR+name+"/practiceroom.c");
        rm(CM_DIR+name+"/qianyuan.c");
        rm(CM_DIR+name+"/qianyuan2.c");
        rm(CM_DIR+name+"/secretroom.c");
        rm(CM_DIR+name+"/temproom1.c");
        rm(CM_DIR+name+"/temproom2.c");
        rm(CM_DIR+name+"/temproom3.c");
        rmdir(CM_DIR+name);
        
        buf = explode( read_file(dir+".c") , "//+" );
        buf[1] ="";
        write_file( dir+".c" ,implode(buf,""), 1);

      if (ob = find_object( dir+".c" ) ) {

          ob->reset();
      }
/*
       if( file_name(ob)==VOID_OB )
                        return notify_fail("不能重新编译 VOID_OB。\n");
                inv = all_inventory(ob);
                i = sizeof(inv);
                while(i--)
//                      if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
//                      else inv[i] = 0;
                        inv[i]->move(VOID_OB, 1);
                
                destruct(ob);
        }
        

        if (ob) 
                return notify_fail("无法清除旧程式码。\n");

        //write("重新编译 " + file + "：");
      err = catch( call_other( this_player()->query("menpai/place") , "???") );
        if (err)
                printf( "发生错误：\n%s\n", err );
        else {
        //      write("成功！\n");
             if( (i=sizeof(inv)) && (ob = find_object( dir+".c" ) )) {
                        while(i--)
//                              if( inv[i] && userp(inv[i]) ) inv[i]->move(obj, 1);
                                inv[i]->move(ob, 1);
                }
        }
        
*/
        init_file = read_file(CM_DIR"logfiles/profile.ini");
        init_file = replace_string(init_file, name+"\n", "");
        write_file(CM_DIR"logfiles/profile.ini",init_file, 1);
        
        init_file = read_file(CM_DIR"placelist");
         init_file = replace_string(init_file,dir+" 1",dir+" 0");
         write_file(CM_DIR"placelist",init_file,1);
        
        rm(CM_DIR"logfiles/"+name);
        
        
        return 1;
}
