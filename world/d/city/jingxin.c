inherit ROOM;

void create ()
{
        set ("short", "������");
        set ("long", @LONG

����һƬ���飬�·����������������������˼������������书��
�ָ���������׼���ٴν���(enter)�ȷ�Ѫ�������ս����
LONG);

       	set("no_pkmeet", 1);
       	set("no_fight", 1);
        set("no_magic", 1);
        set("alternative_die",1);
        setup();
	
}


void init()
{
    add_action("do_enter", "enter");
    add_action("do_likai", "likai");
    add_action("do_get", "get");
       
}

int do_enter()
{
	object me;
	me = this_player();
	
	if(!me->query_temp("mpwar_chance"))
	    {write("���Ѿ�������Σ������ٽ�������ս���ˣ����뿪(likai)���\n");
	     return 1;
	    }
	    
	if(me->is_busy())
	    {write("����æ���ء�\n");
	     return 1;
	    }    
	        
	if(random(2)) me->move("/d/zhanchang/zhanchang1");
	        else  me->move("/d/zhanchang/zhanchang2"); 
	    
        me->set("eff_kee",me->query("max_kee"));
        me->set("eff_sen",me->query("max_sen"));
        me->set("kee",me->query("max_kee"));
        me->set("sen",me->query("max_sen"));
        message_vision("$N�ٴν���������ս����\n",me);
	return 1;
	    
}	

int do_likai()
{
	object me = this_player();
	if(me->query_temp("mpwar_chance"))
	  {write("�㻹�л���Ϊ�Լ��������⣬��ô������뿪�ˣ�\n");
	   return 1;
	  } 
	me->move("/d/city/kezhan");
	me->remove_all_killer();
	me->clear_condition();
	return 1;
}

int do_get()
{
	write("ս���ڲ�����get��\n");
	   return 1;	  
}	   	   