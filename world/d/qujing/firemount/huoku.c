// writted by mind
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "���");
        set("long", @LONG
����ɽ������һ��ɽ�������涼�ǳ�����ʯ������С�����ľ�Ȼ��
�����ҽ���һ�ɹ��������˶��������Ͼͻ�Ҫ���˵��������Ǻں����
Ҳ����Ҫ���������ıڲ��������Ż��档
LONG
        );
        set("exits", ([ 
  "out" : "/d/qujing/firemount/shanbian",
]));
        set("objects", ([
                
       ]) );
        
        setup();
        
}

void init ()
{
  add_action ("do_around","around");
  add_action("do_yanjiu", "xiulian");
}

int do_around ()
{
  object me = this_player ();
  if( (string)me->query("family/family_name")!="����ɢ��" && !wizardp(me) )
                return notify_fail("����������쳣�����ȡ�\n");
  message_vision ("$N��ס���������Ĵ�תת��\n",me);  
  if(!me->query("m_success/���浶"))
  {
    message_vision ("$N�����ܵ����˶��̰�Χס��Խ��Խ͸����������\n",me);
    call_out("fainting",5,me);  
    return 1;
  }
  if(!me->query_skill("huoyan-hand", 1)){
  message_vision("$N���������ܵĻ���Ͷ��̣���չ������Ȼ�����һ��ȭ����\n",me);
  me->set_skill("huoyan-hand",1);}
  return 1;
}


void fainting (object me)
{
        message_vision("ͻȻһ���޴�Ļ�������$N��$N��ʱͷ�ؽ��ᡣ����\n", me);
        if(!me->query("m_success/���浶")) me->set("m_success/���浶",1);
        me->unconcious();
}

int do_yanjiu()
{       
        object me=this_player();
        int sen_cost, kee_cost, force_cost, gain;
	if( (string)me->query("family/family_name")!="����ɢ��" && !wizardp(me) )
                return notify_fail("����������쳣�����ȡ�\n");
        if( me->is_busy() )
                return notify_fail("��æ�ĺܣ����й���������\n");
        if( me->is_fighting() )
                return notify_fail("��ѧ�������������ˣ�\n");
        if( (int)me->query_skill("literate", 1) < 40)
                return notify_fail("���Ļ�̫�ͣ�\n");
        if( (int)me->query_skill("unarmed", 1) < 40)
                return notify_fail("�㻹����ѧ����ȭ�Ź���ɡ�\n");
        if( (int)me->query_skill("huoyan-hand", 1) >= 100)
                return notify_fail("��о�����Ѿ����ʺ������ˡ�\n");
        if( (int)me->query("max_force") < 400)
                return notify_fail("��������㣬�����ˡ�\n");
	if(!me->query("m_success/���浶"))
	{
		message_vision ("$N�����ܵ����˶��̰�Χס��Խ��Խ͸����������\n",me);
		call_out("fainting",5,me);  
		return 1;
	}
	if( me->query("icefire/fire") == 1 )
	{
		sen_cost = 45;
	        if( (int)me->query("sen") < sen_cost )
	                return notify_fail("������ͷ�����ͣ�����Ϣ��Ϣ�ˡ�\n");
	
	        kee_cost = 45;
	        if( (int)me->query("kee") < kee_cost )
	                return notify_fail("�����ڻ�������������Ϣ��Ϣ�ˡ�\n");
	
	        force_cost = 20;
	        if( (int)me->query("force") < force_cost )
	                return notify_fail("���������᲻�����ˣ�����Ϣ��Ϣ�ˡ�\n");
	
	        me->receive_damage("sen", sen_cost);
	        me->receive_damage("kee", kee_cost);
	        me->add("force", - force_cost);
	
	        gain = (int)me->query_int()/2 + (int)me->query_con()/2 + 1 + random(10);
	
	        me->improve_skill("butian-force", gain);
	        write("������Ż�����������ԡ������ķ��������˽⡣\n");
	        write("�����Ž�����ߵ��������������浶��\n");
	        me->start_busy(3);
	        if( random(me->query("kar")) < 14 )
	        {
			message_vision ("$N�����ܵ����˶��̰�Χס��Խ��Խ͸����������\n",me);
			call_out("fainting",2,me);  
			return 1;
		}
		if( random(me->query("kar")) > 24 )
		{
			message_vision (HIR"$N�Ķ�����������һ�ɻ�����������ȼ��\n"NOR,me);
			message_vision (HIR"$N������ת�����ķ������������������������γ��˻��浶��\n"NOR,me);
			if( me->query("icefire/ice") == 2 )//ice�Ѿ����
			{
				me->start_busy(15);
				me->delete("icefire");
				if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
					call_out("finish1",10,me);
				else
					call_out("finish2",10,me);
			}
			else
			{
				message_vision (HIR"$Nһ��������С������һ�ڶ��̣�\n"NOR,me);
				me->set("icefire/fire",2);
				call_out("fainting",2,me);  
			}
			return 1;
		}
	}
	else if( me->query("icefire/ice") == 3 )
	{
		sen_cost = 45;
	        if( (int)me->query("sen") < sen_cost )
	                return notify_fail("������ͷ�����ͣ�����Ϣ��Ϣ�ˡ�\n");
	
	        kee_cost = 45;
	        if( (int)me->query("kee") < kee_cost )
	                return notify_fail("�����ڻ�������������Ϣ��Ϣ�ˡ�\n");
	
	        force_cost = 20;
	        if( (int)me->query("force") < force_cost )
	                return notify_fail("���������᲻�����ˣ�����Ϣ��Ϣ�ˡ�\n");
	
	        me->receive_damage("sen", sen_cost);
	        me->receive_damage("kee", kee_cost);
	        me->add("force", - force_cost);
	
	        gain = (int)me->query_int()/2 + (int)me->query_con()/2 + 1 + random(10);
	
	        me->improve_skill("butian-force", gain);
	        write("�����𺮱��ķ��Կ��Ż�����������ԡ������ķ�������������ˡ�\n");
	        write("�������ڻ������������ǵ���\n");
	        me->start_busy(3);
	        if( random(me->query("kar")) < 16 )
	        {
			message_vision ("$N�����ܵ����˶��̰�Χס��Խ��Խ͸����������\n",me);
			call_out("fainting",2,me);  
			return 1;
		}
		if( random(me->query("kar")) > 25 )
		{
			message_vision (HIW"$N�Ķ��������������⽥�أ�\n"NOR,me);
			message_vision (HIW"$N������ת�����ķ�������ڵ��¶��������ͣ�����������$N�������ᣬ�����γ���һ�ѱ��ǵ���\n"NOR,me);
			if( me->query("icefire/fire") == 4 )//fire�Ѿ����
			{
				me->start_busy(15);
				me->delete("icefire");
				if( random(me->query("int")) > 30 - random( me->query("lunhui_zhuanshi") ) )
					call_out("finish1",10,me);
				else
					call_out("finish2",10,me);
			}
			else
			{
				message_vision (HIR"$Nһ��������С������һ�ڶ��̣�\n"NOR,me);
				me->set("icefire/ice",4);
				call_out("fainting",2,me);  
			}
			return 1;
		}
	}
	else
	{
	        sen_cost = 45 - (int)me->query_int();
		if (sen_cost<20) sen_cost=20;
	        if( (int)me->query("sen") < sen_cost )
	                return notify_fail("������ͷ�����ͣ�����Ϣ��Ϣ�ˡ�\n");
	
	        kee_cost = 45 - (int)me->query_con();
		if (kee_cost<0) kee_cost=20;
	        if( (int)me->query("kee") < kee_cost )
	                return notify_fail("�����ڻ�������������Ϣ��Ϣ�ˡ�\n");
	
	        force_cost = 20;
	        if( (int)me->query("force") < force_cost )
	                return notify_fail("���������᲻�����ˣ�����Ϣ��Ϣ�ˡ�\n");
	
	        me->receive_damage("sen", sen_cost);
	        me->receive_damage("kee", kee_cost);
	        me->add("force", - force_cost);
	
	        gain = (int)me->query("int")/2 + (int)me->query("con")/2 + 1 + random(10);
	
	        me->improve_skill("huoyan-hand", gain);
	        write("������Ż��涾�̣��ԡ����浶���������˽⡣\n");
	}
        tell_room( environment(me), me->name() + "�����飬�ֽŹ�����趯��\n", ({me}));

        return 1;
}

void finish1( object me )
{
	me->add("icefire_known",1);
	if( me->query("icefire_known") == 1 )
	{
		message_vision(HIR"$N���ָ����ǹ�Ծ���Ļ��棬���ĳ����ƽ����\n" NOR,me);
		message_vision(HIR"$N�������������ķ���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�´����ѻ�ߣ����������������ķ��������ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]��\n\n\n"NOR,users());
	}
	else
	{
		message_vision(HIW"$N���ָ������ǵ���������ǣ����ĳ����ƽ����\n" NOR,me);
		message_vision(HIW"$N�������𺮱��ķ���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�ٴ����ѻ�ߣ���ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]�����˼�����\n\n\n"NOR,users());
	}
	return ;
}
void finish2( object me )
{
	me->set("icefire_cant",1);
	if( !me->query("icefire_known") )
	{
		message_vision(HIC"$N���������������쳣���Ｋ������ͻȻһ�ɱ��������Ե����ڲ�ӿ����\n" NOR,me);
		message_vision(HIC"$N���ϻ��浶˲��Ϩ���ˣ�$N�ò����׽�����ƽϢ�����Ҳ�����ǰ�ĸо���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�´����ѻ�ߣ���ϧδ�����������ķ�������ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]��Ե��\n\n\n"NOR,users());
	}
	else
	{
		message_vision(HIC"$N�����������쳣���䣬�Ｋ������ͻȻһ�ɳ��������Ե����ڲ�ӿ����\n" NOR,me);
		message_vision(HIC"$N���ϱ��ǵ�˲���ڻ��ˣ�$N�ò����׽�����ƽϢ�����Ҳ�����ǰ�ĸо���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�ٴ����ѻ�ߣ���ϧδ�ܽ����������ķ��ڻ��ͨ���޷���ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]����������\n\n\n"NOR,users());
	}
	return ;
}