// writted by mind
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
��������Ů������һ���޴���ѣ�ԭ������Ϊ�ʼҴ������ʳ��ģ�
������Ȼ�Ѿ��ķϣ���������ı�����Ȼ�ѵ������ģ�����ǽ���Ѿ���
�˺��ı��������������Ŵ��۵Ĺ⣬��ô������ĵط��������Ѿ�͸
����ȥ�������վã��Ѿ����亮�䣬������°��ʱ���������ˡ�
LONG
        );
        set("exits", ([ 
  "out" : "/d/qujing/nuerguo/shanpo",
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
                return notify_fail("�����������쳣�ĺ��䡣\n");
  message_vision ("$N��������ţ�������Χ�ĺ�����\n",me);  
  if(!me->query("m_success/���ǵ�"))
  {
    message_vision ("$N���·��ƺ�Ҳ��ʼ�����\n",me);
    call_out("fainting",5,me);  
    return 1;
  }
  if(!me->query_skill("bingpo-hand", 1)){
  message_vision("$Nʹ���ٽ����֣���ͣ������Ϣ������������Ȼ�����һ��ȭ����\n",me);
  me->set_skill("bingpo-hand",1);}
  return 1;
}


void fainting (object me)
{
        message_vision("ͻȻ$N�촽���෢�ϣ���ɫ�԰ף�һ�����ĵ��ڵ��ϡ�����\n", me);
        me->set("m_success/���ǵ�",1);
        me->unconcious();
}

int do_yanjiu()
{       
        object me=this_player();
        int sen_cost, kee_cost, force_cost, gain;
	if( (string)me->query("family/family_name")!="����ɢ��" && !wizardp(me) )
                return notify_fail("�����������쳣�ĺ��䡣\n");
        if( me->is_busy() )
                return notify_fail("��æ�ĺܣ����й���������\n");
        if( me->is_fighting() )
                return notify_fail("��ѧ�������������ˣ�\n");
        if( (int)me->query_skill("literate", 1) < 40)
                return notify_fail("���Ļ�̫�ͣ�\n");
        if( (int)me->query_skill("unarmed", 1) < 40)
                return notify_fail("�㻹����ѧ����ȭ�Ź���ɡ�\n");
        if( (int)me->query_skill("bingpo-hand", 1) >= 100)
                return notify_fail("��о������Ѿ����ʺ������ˡ�\n");
        if( (int)me->query("max_force") < 400)
                return notify_fail("��������㣬�����ˡ�\n");
	if(!me->query("m_success/���ǵ�"))
	{
		message_vision ("$N���·��ƺ�Ҳ��ʼ�����\n",me);
		call_out("fainting",5,me);  
		return 1;
	}
	if( me->query("icefire/ice") == 1 )
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
	        write("������ź������������ԡ������ķ��������˽⡣\n");
	        write("�����Ž������ѵ�������������ǵ���\n");
	        me->start_busy(3);
	        if( random(me->query("kar")) < 14 )
	        {
			message_vision ("$N���·��ƺ�Ҳ��ʼ�����\n",me);
			call_out("fainting",2,me);  
			return 1;
		}
		if( random(me->query("kar")) > 24 )
		{
			message_vision (HIW"$N�Ķ������������Ͽ�ʼ���ϸС�ı��裡\n"NOR,me);
			message_vision (HIW"$N������ת�����ķ��������γ��˱��ǵ���\n"NOR,me);
			if( me->query("icefire/fire") == 2 )//fire�Ѿ����
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
				message_vision (HIW"$Nһ��������С�Ŀ����˱����ϣ�\n"NOR,me);
				me->set("icefire/ice",2);
				call_out("fainting",2,me);  
			}
			return 1;
		}
	}
	else if( me->query("icefire/fire") == 3 )
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
	        write("�����������ķ��Կ��ź������������ԡ������ķ�������������ˡ�\n");
	        write("�������ڱ��������������浶��\n");
	        me->start_busy(3);
	        if( random(me->query("kar")) < 16 )
	        {
			message_vision ("$N���·��ƺ�Ҳ��ʼ�����\n",me);
			call_out("fainting",2,me);  
			return 1;
		}
		if( random(me->query("kar")) > 30 - random( me->query("lunhui_zhuanshi") ) )
		{
			message_vision (HIR"$N�Ķ����������������������ȣ�\n"NOR,me);
			message_vision (HIR"$N������ת�����ķ��������ڵ��¶��������ߣ����鿪ʼ�ڻ������Ļ��浶��������ȼ��\n"NOR,me);
			if( me->query("icefire/ice") == 4 )//ice�Ѿ����
			{
				me->start_busy(15);
				me->delete("icefire");
				if( random(me->query("int")) > 25 )
					call_out("finish1",10,me);
				else
					call_out("finish2",10,me);
			}
			else
			{
				message_vision (HIW"$Nһ��������С�Ŀ����˱����ϣ�\n"NOR,me);
				me->set("icefire/fire",4);
				call_out("fainting",2,me);  
			}
			return 1;
		}
	}
	else
	{
	        sen_cost = 45 - (int)me->query_int();
		if (sen_cost<0) sen_cost=20;
	        if( (int)me->query("sen") < sen_cost )
	                return notify_fail("������ͷ�����ͣ�����Ϣ��Ϣ�ˡ�\n");
	
	        kee_cost = 45 - (int)me->query_con();
		if (kee_cost<20) kee_cost=20;
	        if( (int)me->query("kee") < kee_cost )
	                return notify_fail("�����ڻ�������������Ϣ��Ϣ�ˡ�\n");
	
	        force_cost = 20;
	        if( (int)me->query("force") < force_cost )
	                return notify_fail("���������᲻�����ˣ�����Ϣ��Ϣ�ˡ�\n");
	
	        me->receive_damage("sen", sen_cost);
	        me->receive_damage("kee", kee_cost);
	        me->add("force", - force_cost);
	
	        gain = (int)me->query("int")/2 + (int)me->query("con")/2 + 1 + random(10);
	
	        me->improve_skill("bingpo-hand", gain);
	
	        write("��ʩչȭ�ţ��߶���Ϣ���ԡ����ǵ����������˽⡣\n");
	}

        tell_room( environment(me), me->name() + "�����飬�ֽŹ�����趯��\n", ({me}));

        return 1;
}

void finish1( object me )
{
	me->add("icefire_known",1);
	if( me->query("icefire_known") == 1 )
	{
		message_vision(HIW"$N���ָ������ǵ���������ǣ����ĳ����ƽ����\n" NOR,me);
		message_vision(HIW"$N�������𺮱��ķ���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�´����ѻ�ߣ����������������ķ��������ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]��\n\n\n"NOR,users());
	}
	else
	{
		message_vision(HIR"$N���ָ����ǹ�Ծ���Ļ��棬���ĳ����ƽ����\n" NOR,me);
		message_vision(HIR"$N�������������ķ���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�ٴ����ѻ�ߣ���ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]�����˼�����\n\n\n"NOR,users());
	}
	return ;
}

void finish2( object me )
{
	me->set("icefire_cant",1);
	if( !me->query("icefire_known") )
	{
		message_vision(HIC"$N�����������쳣���䣬�Ｋ������ͻȻһ�ɳ��������Ե����ڲ�ӿ����\n" NOR,me);
		message_vision(HIC"$N���ϱ��ǵ�˲���ڻ��ˣ�$N�ò����׽�����ƽϢ�����Ҳ�����ǰ�ĸо���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�´����ѻ�ߣ���ϧδ�����򺮱��ķ�������ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]��Ե��\n\n\n"NOR,users());
	}
	else
	{
		message_vision(HIC"$N���������������쳣���Ｋ������ͻȻһ�ɱ��������Ե����ڲ�ӿ����\n" NOR,me);
		message_vision(HIC"$N���ϻ��浶˲��Ϩ���ˣ�$N�ò����׽�����ƽϢ�����Ҳ�����ǰ�ĸо���\n" NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�������(gui guzi)��" + me->name() + "�ٴ����ѻ�ߣ���ϧδ�ܽ����������ķ��ڻ��ͨ���޷���ɢ�ɾ�ѧ["+HIW"��"+HIR"��"+HIY+"��"+HIC"]����������\n\n\n"NOR,users());
	}
	return ;
}