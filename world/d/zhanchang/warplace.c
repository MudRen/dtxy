// create by yesi


inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "ս��");
  set ("long", @LONG

����ս���ĳ���

LONG);

  setup();
}

void init()
{
    object room,king,me;
    object* member;
    int i;
    string me_menpai;
        
    room = this_object();
    me = this_player();
    king = find_living("tang taizong");
    me_menpai = me->query("family/family_name");
    
    if( king->query_temp("mpwarbegin") && !wizardp(me))
    {
    	member = all_inventory(room);
        for (i=0;i<sizeof(member);i++)
          {if(member[i]->query("family/family_name") == me_menpai) continue;
           if(wizardp(member[i])) continue;
           else {member[i]->kill_ob(me);
                 me->kill_ob(member[i]);
                }
          }
    }      
     
    add_action("do_kill", "kill");
    add_action("do_quit", "quit");
    add_action("do_cast", "cast");
    add_action("do_ji", "ji");
    add_action("do_get", "get");     
    
}

int do_kill()
{
	write("���ﲻ��Ҫ��������\n");
	return 1;
}
	
int do_quit()
{
	write("��ս���ڲ����˳���Ϸ��\n");
	return 1;
}


int do_cast(string spell)
{
	if(spell=="shuidun" || spell=="tudun" || spell=="huodun"
	   || spell=="escape" || spell=="miwu")
	  {write("�㲻�������������\n");
	   return 1;
	  }
	  
	 return 0;
}	 
	  
int do_ji()
{
	write("ս���ڲ�����ji��\n");
	   return 1;	  
}
	   
int valid_leave(object me, string dir)
{
	if(time()-me->query_temp("warmove")<3)
	   return notify_fail("�����ڲ����ƶ���\n");
	
	if(me->is_fighting())
	   {me->set_temp("warmove",time());
	    return ::valid_leave(me, dir);
	   }
	
	return ::valid_leave(me, dir);   
}

int do_get()
{
	write("ս���ڲ�����get��\n");
	   return 1;	  
}	   	   