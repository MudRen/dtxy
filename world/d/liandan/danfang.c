//������
//canoe 
#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_liandan();
int do_stop();

void create()
{
    set("short", "������");
    set("long", @LONG

������˸���¯��ʲôҲû�У�����������������һ�ֵ�ҩζ��

LONG );

set("exits", ([
         "up" : __DIR__"datang",
    ]));
    
set("objects", ([
                __DIR__"obj/daotong": 1,
                __DIR__"obj/danlu": 1,
                 ]) );
  set("no_magic", 1);
  set("no_fight", 1);
   
     setup();
}

int init()
{
        add_action("do_liandan","liandan"); 
        add_action("do_stop","stop");
        add_action("do_get","get");
}

int do_liandan()
{       int kar;
        string str;
        object me = this_player();
        
        // ����˵��:yxld==��������
        //          nlcs==��������
        //          ldcs==��������
        //          ldwp==������Ʒ����,Ŀǰ��2000 4000
        
        if(!me->query_temp("yxld"))
                    return notify_fail("��ԭ�϶�û����ͯ����ô����\n");
        if(me->is_busy()) 
                   return notify_fail("��������æ���أ�\n");
        if(me->query("kee")<200||me->query("sen")<200)
                   return notify_fail("�㻹������Ϣһ�°ɣ������ܺ���Ѫ�;����Ŷ��\n");
                
         kar = me->query("kar")*2;
        if (!me->query_temp("nlcs")) me->set_temp("nlcs",random(kar)/5);
                
        me->start_busy(3+random(10));
        message_vision(MAG"$N�Ķ����������Լ������ĵ��л���һ���������¯��\n"NOR, me);
       
        me->receive_damage("kee",random(100));
        me->receive_damage("sen",random(100));
       
          if (random(kar)>=0) // old is > 3
            {
            if( me->query_temp("ldcs")>=me->query_temp("nlcs"))
                {
		
		kar=random(7);// ��ʡ����, ���ᳫ���� :P
me->set_temp("ldcs",(int)me->query_temp("ldcs")/2);
		if(kar==0)
		    {
			message_vision(HIR"¯��Ļ��͵�һ����$N����������һ�����������Ǳ�ܵ���\n"NOR,me);
 	                message_vision(CYN"$Nϲ������,һ���������Ǳ�ܵ���\n"NOR,me);
kar=(int)me->query_temp("ldwp")/4+random(500)+(int)me->query_temp("ldcs")*40+(int)me->query_temp("nlcs")*20;
 	                tell_object(me,"������"+kar+"��Ǳ�ܣ�\n");
        	        str=me->query("name")+"�ɹ��������˿�Ǳ�ܵ�,�����"+kar+"��Ǳ�ܽ�����";
                	CHANNEL_D->do_channel(me,"rumor",str);
        	        kar=(int)me->query_temp("ldwp")+random(2000);
                	me->add("potential",kar);
                    }
    		else if(kar==1)
    		    {
    		        message_vision(HIR"¯��Ļ��͵�һ����$N����������һ�������������ѧ����\n"NOR,me);
 	                message_vision(CYN"$Nϲ������,һ�����������ѧ����\n"NOR,me);
kar=(int)me->query_temp("ldwp")+random(1000)+(int)me->query_temp("ldcs")*200+(int)me->query_temp("nlcs")*100;
        	        tell_object(me,"������"+kar+"����ѧ���飡\n");
        	        str=me->query("name")+"�ɹ��������˿���ѧ��,�����"+kar+"����ѧ������";
                	CHANNEL_D->do_channel(me,"rumor",str);
                	me->add("combat_exp",kar);
                   }
                else if(kar==2) 
                   {    
                        message_vision(HIR"¯��Ļ��͵�һ����$N����������һ����������ĵ��е���\n"NOR,me);
 	                message_vision(CYN"$Nϲ������,һ��������ŵ��е���\n"NOR,me);
kar=(int)me->query_temp("ldwp")+random(500)+(int)me->query_temp("ldcs")*400+(int)me->query_temp("nlcs")*400;
        	        tell_object(me,"������"+COMBAT_D->chinese_daoxing(kar)+"�ĵ��У�\n");
        	        str=me->query("name")+"�ɹ��������˿ŵ��е�,�����"+COMBAT_D->chinese_daoxing(kar)+"�ĵ��н�����";
                	CHANNEL_D->do_channel(me,"rumor",str);
                	me->add("daoxing",kar);
                   
                   }   
    		else 
    		   {   
                        message_vision(HIR"¯��Ļ��͵�һ�����������ľ�Ȼ�ǻƽ�!\n"NOR,me);
 	                message_vision(CYN"$Nϲ������,�Ͻ�����ЩǮ���������\n"NOR,me);
kar=(int)me->query_temp("ldwp")*20+random(50000)+(int)me->query_temp("ldcs")*8000+(int)me->query_temp("nlcs")*4000;
        	        tell_object(me,"������"+chinese_number(kar/10000)+"���ƽ�\n");
        	        str=me->query("name")+"�����ײ,��Ȼ������"+chinese_number(kar/10000)+"���ƽ�";
                	CHANNEL_D->do_channel(me,"rumor",str);
                	me->add("balance",kar);
                   }
    	        me->delete_temp("yxld");
		me->delete_temp("ldcs");
		me->delete_temp("nlcs");
		me->delete_temp("ldwp");
                      log_file("liandan",sprintf("%s(%s)(%s)\n",
				geteuid(me),str,ctime(time()) ) );
    	        return 1;
    	       }
    	    else {
    	        message_vision(HIR"ֻ��¯��Ļ�����ˡ�����\n"NOR,me);
    	        me->add_temp("ldcs",1);
    	        return 1;
    	         }
    	  }
        else 
           	{
                me->receive_wound("kee", random(100));  
                me->receive_wound("sen",random(50));
                message_vision(RED"$N�й�ʱͻȻ�߻���ħ��������Ѫ�Ե��ڵء�\n"NOR,me );
                me->add_temp("ldcs",1);
     		me->unconcious();
     		 return 1;
     		}
}

int do_stop()
{
object me=this_player();
if (!me->query_temp("yxld")) return notify_fail ("�㲢û����������������ֹ��\n");
me->delete_temp("yxld");
me->delete_temp("ldcs");
me->delete_temp("ldwp");
me->delete_temp("nlcs");
message_vision("$N˼ǰ���,��ֹ��������\n",me );
return 1;
}

int valid_leave(object me, string dir)
{       
        
        if (dir == "up" && me->query_temp("yxld") ) {
               
                return notify_fail("С��ͯ����˵�������굤���߰ɣ�\n");
        return ::valid_leave(me, dir);
        }
        return 1;
}

int do_get(string arg)
{
        string from;
        object me = this_player();
        object env;
        
        if( !arg ) return 0;
                
        if( sscanf(arg, "%s from %s", arg, from)==2 )
            {
                env = present(from, me);
                if(!env) env = present(from, environment(me));
                if(!env) return 0;
                if(env->is_character() && !living(env))
                      {  tell_object(me,"С��ͯ����ҡ��ҡͷ��\n");
                         return 1;
                      }
            }
        
        else {
                env = present(arg, environment(me));
 if(!env) return 0;
                if(env->is_character() && !living(env))
                      {  tell_object(me,"С��ͯ����ҡ��ҡͷ��\n");
                         return 1;
                      }
             }
                        
        return 0;
}               
